#include "DX12ShaderAsset.h"
#include "SSEngineDefault/SSEngineDefault.h"

#include <d3dcompiler.h>

DX12ShaderAsset::DX12ShaderAsset(SS::SHashA InAssetName, SS::SHashA InAssetPath, const char* entryPoint, EShaderType InShaderType) :
	ShaderAsset(InAssetName, InAssetPath, entryPoint, InShaderType)
{
}

DX12ShaderAsset::~DX12ShaderAsset()
{
	if (_compiledShader != nullptr)
	{
		_compiledShader->Release();
		_compiledShader = nullptr;
	}
}

bool DX12ShaderAsset::CompileShader()
{
#ifdef _DEBUG
	// Enable better shader debugging with the graphics debugging tools.
	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	UINT compileFlags = 0;
#endif

	ID3DBlob* errorBlob = nullptr;

	uint32 strLen = 0;
	const char* AssetPathA = GetAssetPath().c_str(&strLen);

	utf16 shaderPath[256];
	SS::CharStrToUTF16Str(AssetPathA, strLen, shaderPath, 256);


	const char* shaderTargetName = nullptr;
	switch (_shaderType)
	{
	case EShaderType::Undefined:
		SS_CLASS_ERR_LOG("Invalid shader type.");
		return false;
	case EShaderType::VertexShader:
		shaderTargetName = "vs_5_0";
		break;
	case EShaderType::PixelShader:
		shaderTargetName = "ps_5_0";
		break;
	}

	if (FAILED(D3DCompileFromFile(shaderPath, nullptr, nullptr, _entryPointName.C_Str(), shaderTargetName, compileFlags, 0, &_compiledShader, &errorBlob)))
	{
		const char* errorStr = nullptr;
		if (errorBlob != nullptr)
		{
			errorStr = (char*)errorBlob->GetBufferPointer();
		}
		SS_CLASS_ERR_LOG("%s\n", errorStr);
		return false;
	}
	return true;
}