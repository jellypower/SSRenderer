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

	// Optional�ϰ� root signature�� ���ε� �� �� �ֵ��� ����� ���������.

private:
	ID3D12PipelineState* _PipelineState = nullptr;
};

