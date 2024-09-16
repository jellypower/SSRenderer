#include "DX12MeshAssetManager.h"
#include "RenderAssetType/DX12MeshAsset.h"


void DX12MeshAssetManager::InitializeMeshAssetPool()
{
}

MeshAsset* DX12MeshAssetManager::CreateTempMeshAsset()
{
	DX12MeshAsset* newMeshAsset = DBG_NEW DX12MeshAsset("TempMesh", "NoPath");


	return nullptr;
}

DX12MeshAssetManager::~DX12MeshAssetManager()
{
	
}
