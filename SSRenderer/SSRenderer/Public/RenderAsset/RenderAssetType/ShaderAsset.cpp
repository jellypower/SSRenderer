#include "ShaderAsset.h"


ShaderAsset::ShaderAsset(SS::SHashA InAssetName, SS::SHashA InAssetPath, const char* entryPoint, EShaderType InShaderType):
	SSAssetBase(InAssetName, InAssetPath)
{
	_entryPointName = entryPoint;
	_shaderType = InShaderType;
}
