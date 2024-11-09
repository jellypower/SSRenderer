#pragma once
#include "SSRenderer/Public/RenderAsset/RenderAssetType/ShaderAsset.h"
#include <d3d12.h>

class DX12ShaderAsset : public ShaderAsset
{
public:
	DX12ShaderAsset(SS::SHasherA InAssetName, SS::SHasherA InAssetPath, const char* entryPoint, EShaderType InShaderType);
	virtual ~DX12ShaderAsset();

	ID3DBlob* GetCompiledShader() const { return _compiledShader; }
	virtual bool CompileShader() override;

private:
	ID3DBlob* _compiledShader = nullptr;
};

