#include "DX12ShaderAssetManager.h"
#include "SSRenderer/Private/DX12/RenderAsset/RenderAssetType/DX12ShaderAsset.h"

DX12ShaderAssetManager::~DX12ShaderAssetManager()
{
}

void DX12ShaderAssetManager::Initialize()
{

}

ShaderAsset* DX12ShaderAssetManager::CreateTempVertexShader()
{
	DX12ShaderAsset* newShaderAsset = DBG_NEW DX12ShaderAsset("TempVertexShader", "Resource/Shader/tempShader.hlsl", "VSMain", EShaderType::VertexShader);
	return newShaderAsset;
}

ShaderAsset* DX12ShaderAssetManager::CreateTempPixelShader()
{
	DX12ShaderAsset* newShaderAsset = DBG_NEW DX12ShaderAsset("TempPixelShader", "Resource/Shader/tempShader.hlsl", "PSMain", EShaderType::PixelShader);
	return newShaderAsset;
}
