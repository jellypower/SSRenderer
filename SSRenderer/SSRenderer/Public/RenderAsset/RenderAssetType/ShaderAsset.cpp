#include "ShaderAsset.h"


ShaderAsset::ShaderAsset(SS::SHasherA InAssetName, SS::SHasherA InAssetPath, const char* entryPoint, EShaderType InShaderType):
	SSAssetBase(InAssetName, InAssetPath)
{
	_entryPointName = entryPoint;
	_shaderType = InShaderType;
}
