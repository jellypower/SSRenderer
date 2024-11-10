#pragma once
#include <d3dx12.h>
#include <d3d12.h>
#include "SSRenderer/Public/RenderAsset/RenderAssetType/MaterialAsset.h"

class DX12MaterialAsset : public MaterialAsset
{
public:
	DX12MaterialAsset(SS::SHasherW InAssetName, SS::SHasherW InAssetPath);

	virtual bool InitGPUInstance() override;
	virtual void ReleaseGPUInstance() override;

	// Optional하게 root signature를 바인드 할 수 있도록 기능을 만들어주자.

private:
	ID3D12PipelineState* _PipelineState = nullptr;
};

