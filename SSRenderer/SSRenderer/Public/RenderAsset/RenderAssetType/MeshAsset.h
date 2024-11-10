#pragma once
#include "SSAssetBase.h"

class MeshAsset : public SSAssetBase 
{
private:
	bool _isUsableOnCPU = false;
	bool _isUsableOnGPU = false;

public:
	MeshAsset(SS::SHasherW InAssetName, SS::SHasherW InAssetPath);
};

