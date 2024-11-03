#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
class MaterialAsset;


class MaterialAssetManager
{
public:
	virtual ~MaterialAssetManager();

	virtual void Initialize() = 0;


	// TODO: ���ֱ�
	virtual MaterialAsset* CreateTempMaterialAsset() = 0;

public:
	// TODO: ���ֱ�
	MaterialAsset* _tempMaterialAsset = nullptr;
};

