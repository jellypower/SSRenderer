#include "SSEngine.h"

#include <vector>

#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSFrameInfo.h"
#include "SSEngineDefault/SSContainer/HashMap.h"

#include "SSRenderer/Public/RenderAsset/MeshAssetManager.h"
#include "SSRenderer/Public/RenderAsset/MaterialAssetManager.h"
#include "SSRenderer/Public/RenderAsset/ShaderAssetManager.h"
#include "SSRenderer/Public/RenderBase/GlobalRenderInstanceCollection.h"

#include "SSRenderer/Public/RenderAsset/RenderAssetType/MaterialAsset.h"
#include "SSRenderer/Public/RenderAsset/RenderAssetType/ShaderAsset.h"

#include "SSRenderer/Public/RenderAsset/RenderAssetType/MeshAsset.h"

void EngineBeginFrame()
{
	g_MeshAssetManager->_tempMeshAsset = g_MeshAssetManager->CreateTempMeshAsset();

	g_ShaderAssetManager->_tempVertexShaderAsset = g_ShaderAssetManager->CreateTempVertexShader();
	g_ShaderAssetManager->_tempVertexShaderAsset->CompileShader();
	g_ShaderAssetManager->_tempPixelShaderAsset = g_ShaderAssetManager->CreateTempPixelShader();
	g_ShaderAssetManager->_tempPixelShaderAsset->CompileShader();

	g_MaterialAssetManager->_tempMaterialAsset = g_MaterialAssetManager->CreateTempMaterialAsset();
	g_MaterialAssetManager->_tempMaterialAsset->InitGPUInstance();
}


SS::HashMap<SS::SHasherA, SS::FixedStringA<PATH_LEN_MAX>, 200> HashMap;

void EnginePerFrame()
{
	SS::SHasherA A = "AA";
	SS::SHasherA a = "aa";
}

void EngineEndFrame()
{
	SS::SHasherA::ClearHashPool();
	g_MaterialAssetManager->_tempMaterialAsset->ReleaseGPUInstance();
	delete g_MaterialAssetManager->_tempMaterialAsset;
	delete g_ShaderAssetManager->_tempPixelShaderAsset;
	delete g_ShaderAssetManager->_tempVertexShaderAsset;
	delete g_MeshAssetManager->_tempMeshAsset;
}
