#pragma once
#include "SSRenderer/Public/RenderAsset/MaterialAssetManager.h"

class DX12MaterialAssetManager : public MaterialAssetManager
{
	virtual void Initialize() override;

	// TODO: ���ֱ�
	virtual MaterialAsset* CreateTempMaterialAsset() override;
};

