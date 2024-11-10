#pragma once
#include "SSAssetBase.h"

class MaterialAsset : public SSAssetBase
{
public:
	MaterialAsset(SS::SHasherW InAssetName, SS::SHasherW InAssetPath);

	virtual bool InitGPUInstance() = 0;
	virtual void ReleaseGPUInstance() = 0;

protected:
	bool _isUsableOnCPU = false;
	bool _isUsableOnGPU = false;
};

