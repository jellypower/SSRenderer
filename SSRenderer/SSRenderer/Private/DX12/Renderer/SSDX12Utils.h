#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include <d3dx12.h>
#include <d3d12.h>

namespace SS {
	static inline constexpr D3D12_STATIC_SAMPLER_DESC GetDefaultSamplerDesc(uint32 RegisterIdx)
	{
		D3D12_STATIC_SAMPLER_DESC sampler = {};

		sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		sampler.MipLODBias = 0.0f;
		sampler.MaxAnisotropy = 16;
		sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		sampler.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
		sampler.MinLOD = -FLT_MAX;
		sampler.MaxLOD = D3D12_FLOAT32_MAX;
		sampler.ShaderRegister = RegisterIdx;
		sampler.RegisterSpace = 0;
		sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

		return sampler;
	}

};