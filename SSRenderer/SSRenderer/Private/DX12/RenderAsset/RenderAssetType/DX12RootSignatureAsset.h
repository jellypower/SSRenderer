#pragma once
#include <d3dx12.h>

#include "SSEngineDefault/SSEngineDefault.h"
#include "SSRenderer/Public/RenderAsset/RenderAssetType/SSAssetBase.h"

class DX12RootSignatureAsset : public SSAssetBase
{
	friend class DX12RootSignatureAssetManager;
public:
	DX12RootSignatureAsset(SS::SHashA rootSignaterName);
	virtual ~DX12RootSignatureAsset();

	bool InitGPUInstance(CD3DX12_ROOT_SIGNATURE_DESC params);
	void ReleaseGPUInstance();

	bool IsUsableOnGPU() const { return _D3DRootSignature != nullptr; }
	ID3D12RootSignature* GetRootSignature() const { return _D3DRootSignature; }

private:
	ID3D12RootSignature* _D3DRootSignature = nullptr;
};

