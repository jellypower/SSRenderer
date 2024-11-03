#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSNonCopyable.h"

class ShaderAsset;

class ShaderAssetManager : public SSNoncopyable
{
public:
	virtual ~ShaderAssetManager();

	virtual void Initialize() = 0;

	// TODO: ���ֱ�
	virtual ShaderAsset* CreateTempVertexShader() = 0;
	virtual ShaderAsset* CreateTempPixelShader() = 0;

public:
	ShaderAsset* _tempVertexShaderAsset = nullptr;
	ShaderAsset* _tempPixelShaderAsset = nullptr;
};

