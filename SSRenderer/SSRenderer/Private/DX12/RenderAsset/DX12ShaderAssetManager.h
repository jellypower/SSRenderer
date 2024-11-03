#pragma once
#include "SSRenderer/Public/RenderAsset/ShaderAssetManager.h"

class DX12ShaderAssetManager : public ShaderAssetManager
{
public:
	virtual ~DX12ShaderAssetManager() override;
	virtual void Initialize() override;

	virtual ShaderAsset* CreateTempVertexShader() override;
	virtual ShaderAsset* CreateTempPixelShader() override;
};

