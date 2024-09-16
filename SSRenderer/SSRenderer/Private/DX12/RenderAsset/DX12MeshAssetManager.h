#pragma once
#include "SSRenderer/Public/RenderAsset/MeshAssetManager.h"

class DX12MeshAssetManager : public MeshAssetManager
{
public:
	virtual ~DX12MeshAssetManager() override;

	virtual void InitializeMeshAssetPool() override;
	virtual MeshAsset* CreateTempMeshAsset() override;
};