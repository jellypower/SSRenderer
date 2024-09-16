#pragma once
#include "SSAssetBase.h"

class MeshAsset : public SSAssetBase 
{
public:
	MeshAsset(SS::SHashA InAsetName, SS::SHashA InAssetPath);

private:
	bool _isDataOnCPU = false;
	bool _isDataOnGPU = false;
};

