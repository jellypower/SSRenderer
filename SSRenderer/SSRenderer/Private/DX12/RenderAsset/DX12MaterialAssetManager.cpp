#include "DX12MaterialAssetManager.h"
#include "RenderAssetType/DX12MaterialAsset.h"

void DX12MaterialAssetManager::Initialize()
{

}

MaterialAsset* DX12MaterialAssetManager::CreateTempMaterialAsset()
{
    DX12MaterialAsset* newAsset = DBG_NEW DX12MaterialAsset("TempMaterial", "NoPath");

    return newAsset;
}
