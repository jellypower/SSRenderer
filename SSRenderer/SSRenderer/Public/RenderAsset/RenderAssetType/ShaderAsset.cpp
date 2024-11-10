#include "ShaderAsset.h"


ShaderAsset::ShaderAsset(SS::SHasherW InAssetName, SS::SHasherW InAssetPath, const char* entryPoint, EShaderType InShaderType):
	SSAssetBase(InAssetName, InAssetPath)
{
	_entryPointName = entryPoint;
	_shaderType = InShaderType;
}
