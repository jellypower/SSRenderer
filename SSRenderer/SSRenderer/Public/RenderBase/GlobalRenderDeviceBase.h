#pragma once
#include "SSEngineDefault/SSEngineDefault.h"


enum class ERenderDevicePlatnform : uint32
{
	DX12Raster,
};


class GlobalRenderDeviceBase
{
protected:
	ERenderDevicePlatnform RenderDevicePlatform;

public:
	virtual ~GlobalRenderDeviceBase();

	ERenderDevicePlatnform GetRenderDevicePlatform() const { return RenderDevicePlatform; }
};