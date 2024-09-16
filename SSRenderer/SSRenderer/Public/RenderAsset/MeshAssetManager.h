#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSNonCopyable.h"

class MeshAsset;

class MeshAssetManager : public SSNoncopyable
{
public:
	virtual ~MeshAssetManager();

	virtual void InitializeMeshAssetPool() = 0;

	// TODO: 없애기
	virtual MeshAsset* CreateTempMeshAsset() = 0;


public:
	// TODO: 없애기
	MeshAsset* TempMeshAsset = nullptr;
};

