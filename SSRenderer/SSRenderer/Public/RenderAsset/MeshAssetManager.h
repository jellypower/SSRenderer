#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSNonCopyable.h"

class MeshAsset;

class MeshAssetManager : public SSNoncopyable
{
public:
	virtual ~MeshAssetManager();

	virtual void InitializeMeshAssetPool() = 0;

	// TODO: ���ֱ�
	virtual MeshAsset* CreateTempMeshAsset() = 0;


public:
	// TODO: ���ֱ�
	MeshAsset* TempMeshAsset = nullptr;
};

