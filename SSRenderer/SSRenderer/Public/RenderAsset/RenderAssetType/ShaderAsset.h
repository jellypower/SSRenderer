#pragma once
#include "SSAssetBase.h"
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSContainer/SSString/SSStringContainerUtilsCollection.h"


enum class EShaderAssetInstanceState 
{
	JustCreated = 0, // �ܼ� ������ ��
	Compiled = 1, // �������� �Ϸ��
	Instantiated // GPU���� ��� ������
};

enum class EShaderType
{
	Undefined,

	VertexShader,
	PixelShader,
};

class ShaderAsset : public SSAssetBase
{
public:
	ShaderAsset(SS::SHashA InAssetName, SS::SHashA InAssetPath, const char* entryPoint, EShaderType InShaderType);

	virtual bool CompileShader() = 0;


protected:
	SS::FixedStringA<256> _entryPointName;
	EShaderType _shaderType;
	EShaderAssetInstanceState InstanceState = EShaderAssetInstanceState::JustCreated;
};

