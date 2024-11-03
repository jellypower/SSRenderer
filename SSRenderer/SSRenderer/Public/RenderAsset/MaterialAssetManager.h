#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
class MaterialAsset;


class MaterialAssetManager
{
public:
	virtual ~MaterialAssetManager();

	virtual void Initialize() = 0;


	// TODO: 없애기
	virtual MaterialAsset* CreateTempMaterialAsset() = 0;

public:
	// TODO: 없애기
	MaterialAsset* _tempMaterialAsset = nullptr;
};

