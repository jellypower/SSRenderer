#include "SSEngine.h"
#include "SSEngineDefault/SSEngineDefault.h"

#include "SSRenderer/Public/RenderAsset/MeshAssetManager.h"
#include "SSRenderer/Public/RenderBase/GlobalRenderInstanceCollection.h"


void EngineBeginFrame()
{
	g_MeshAssetManager->TempMeshAsset = g_MeshAssetManager->CreateTempMeshAsset();
}

void EnginePerFrame()
{
	
}

void EngineEndFrame()
{
}
