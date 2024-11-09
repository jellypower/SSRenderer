#pragma once

#include "SSEngineDefault/SSEngineDefault.h"

#define FBXSDK_SHARED
#include <fbxsdk.h>

#include "AssetType/SSAssetBase.h"
#include "SSEngineDefault/SSContainer/SSUtilityContainer.h"
#include "SSEngineDefault/SSContainer/SSString/FixedStringA.h"


// TODO: 2024/11/03 FbxImporter 리팩토링하기

class SSGeometryAsset;
class SSMaterialAssetManager;
class SSModelAssetManager;
class SSModelAsset;
class SSPlaceableAsset;

class SSFBXImporter {
public:
	static bool g_exportSSMaterial;

private:
	FbxManager* _FBXManager = nullptr;
	FbxImporter* _FBXImporter = nullptr;
	FbxScene* _currentScene = nullptr;
	SS::FixedStringA<ASSET_NAME_LEN_MAX> _fileName;
	SS::FixedStringA<PATH_LEN_MAX> _filePath;

public:
	SSFBXImporter();
	~SSFBXImporter();

	HRESULT LoadModelAssetFromFBXFile(const char* filePath);
	void ClearFBXModelAsset();

	void StoreCurrentFBXModelAssetToAssetManager();


private:

	void ImportCurrentSceneToMaterialAsset();
	void ImportCurrentSceneToModelAsset();
	void ImportCurrentSceneToSkeletonAsset();
	void ImportCurrentSceneToSkeletonAnimAsset();
	void TraverseNodesRecursion(::FbxNode* node, SSPlaceableAsset* parentAsset);


	SSGeometryAsset* GenerateGeometryFromFbxMesh(::FbxMesh* fbxMesh);
	SSGeometryAsset* GenerateSkinnedGeometryFromFbxMesh(::FbxMesh* fbxMesh);
};