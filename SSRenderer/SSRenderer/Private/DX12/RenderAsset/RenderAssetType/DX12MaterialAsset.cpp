#include "DX12MaterialAsset.h"

#include <d3d12.h>
#include <d3dcompiler.h>
#include <d3dx12.h>

#include "SSEngineDefault/SSEngineDefault.h"
#include "SSRenderer/Public/RenderAsset/ShaderAssetManager.h"
#include "SSRenderer/Public/RenderBase/GlobalRenderInstanceCollection.h"

#include "SSRenderer/Private/DX12/Renderer/DX12RGlobalenderInstanceCollection.h"
#include "SSRenderer/Private/DX12/Renderer/DX12GlobalRenderDevice.h"
#include "SSRenderer/Private/DX12/RenderAsset/RenderAssetType/DX12ShaderAsset.h"
#include "SSRenderer/Private/DX12/RenderAsset/RenderAssetType/DX12RootSignatureAsset.h"
#include "SSRenderer/Private/DX12/RenderAsset/DX12RootSignatureAssetManager.h"


DX12MaterialAsset::DX12MaterialAsset(SS::SHasherA InAssetName, SS::SHasherA InAssetPath) :
	MaterialAsset(InAssetName, InAssetPath)
{

}

bool DX12MaterialAsset::InitGPUInstance()
{
	if (g_RenderDevice == nullptr)
	{
		SS_CLASS_ERR_LOG("RenderDevice is not initialized yet.");
		return false;
	}
	DX12GlobalRenderDevice* RenderDevice = (DX12GlobalRenderDevice*)g_RenderDevice;

	ID3D12Device5* D3DDeivce = RenderDevice->GetD3DDevice();
	if (D3DDeivce == nullptr)
	{
		SS_CLASS_ERR_LOG("D3DDevice is not initialized yet.");
		return false;
	}

	if (g_RootSignatureAssetManager == nullptr)
	{
		SS_CLASS_ERR_LOG("RootSignatureAssetManager is not initialized yet.");
		return false;
	}

	DX12RootSignatureAsset* tempRootSignatureAsset = g_RootSignatureAssetManager->_tempRootSignatureAsset;
	if (tempRootSignatureAsset == nullptr)
	{
		SS_CLASS_ERR_LOG("tempRootSignatureAsset is not initialized yet.");
		return false;
	}

	if (tempRootSignatureAsset->IsUsableOnGPU() == false)
	{
		SS_CLASS_ERR_LOG("tempRootSignatureAsset is not initialized yet.");
		return false;
	}

	const DX12ShaderAsset* VS = (DX12ShaderAsset*)g_ShaderAssetManager->_tempVertexShaderAsset;
	const DX12ShaderAsset* PS = (DX12ShaderAsset*)g_ShaderAssetManager->_tempPixelShaderAsset;
	
	ID3DBlob* VSBlob = VS->GetCompiledShader();
	ID3DBlob* PSBlob = PS->GetCompiledShader();


	// Define the vertex input layout.
	D3D12_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	0, 28,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};


	// Describe and create the graphics pipeline state object (PSO).
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.InputLayout = { inputElementDesc, _countof(inputElementDesc) };
	psoDesc.pRootSignature = tempRootSignatureAsset->GetRootSignature();
	psoDesc.VS = CD3DX12_SHADER_BYTECODE(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize());
	psoDesc.PS = CD3DX12_SHADER_BYTECODE(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize());
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState.DepthEnable = FALSE;
	psoDesc.DepthStencilState.StencilEnable = FALSE;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;

	// TODO: pipeline 만드는 기능을 PipelineAsset쪽으로 옮기기
	HRESULT result = D3DDeivce->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&_PipelineState));
	if (FAILED(result))
	{
		SS_CLASS_ERR_LOG("CreatePipeline Failed.");
		return false;
	}

	_isUsableOnGPU = true;
	return true;
	
}

void DX12MaterialAsset::ReleaseGPUInstance()
{
	_PipelineState->Release();
	_PipelineState = nullptr;
	_isUsableOnGPU = false;
}
