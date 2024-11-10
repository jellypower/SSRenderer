#include "DX12RootSignatureAsset.h"

#include "SSRenderer/Private/DX12/Renderer/DX12GlobalRenderDevice.h"
#include "SSRenderer/Public/RenderBase/GlobalRenderInstanceCollection.h"

#include <d3d12.h>

DX12RootSignatureAsset::DX12RootSignatureAsset(SS::SHasherW rootSignaterName) :
	SSAssetBase(rootSignaterName, L"NoPath")
{

}

DX12RootSignatureAsset::~DX12RootSignatureAsset()
{
	if (IsUsableOnGPU())
	{
		SS_CLASS_ERR_LOG("GPUInstance must be deleted on deletion of asset.");
		_D3DRootSignature->Release();
		_D3DRootSignature = nullptr;
	}
}

bool DX12RootSignatureAsset::InitGPUInstance(CD3DX12_ROOT_SIGNATURE_DESC params)
{
	if (g_RenderDevice == nullptr)
	{
		SS_CLASS_ERR_LOG("Render device is not initialized.");
		return false;
	}
	DX12GlobalRenderDevice* RenderDevice = (DX12GlobalRenderDevice*)g_RenderDevice;

	ID3D12Device5* D3DDevice = RenderDevice->GetD3DDevice();
	if (D3DDevice == nullptr)
	{
		SS_CLASS_ERR_LOG("Render device is not initialized.");
		return false;
	}

	ID3DBlob* Signature = nullptr;
	ID3DBlob* Error = nullptr;

	if (FAILED(D3D12SerializeRootSignature(&params, D3D_ROOT_SIGNATURE_VERSION_1, &Signature, &Error)))
	{
		SS_CLASS_ERR_LOG("%s", (char*)Error->GetBufferPointer());
		return false;
	}

	if (FAILED(D3DDevice->CreateRootSignature(0, Signature->GetBufferPointer(), Signature->GetBufferSize(), IID_PPV_ARGS(&_D3DRootSignature))))
	{
		SS_CLASS_ERR_LOG("CreateRootSignature failed.");
		return false;
	}
	if (Signature)
	{
		Signature->Release();
		Signature = nullptr;
	}
	if (Error)
	{
		Error->Release();
		Error = nullptr;
	}

	_D3DRootSignature->SetName(L"SSRootSignatureAsset");
	return true;
}

void DX12RootSignatureAsset::ReleaseGPUInstance()
{
	_D3DRootSignature->Release();
	_D3DRootSignature = nullptr;
}
