#include "DX12GlobalRenderDevice.h"

#include <dxgi.h>
#include <dxgi1_4.h>

DX12GlobalRenderDevice::DX12GlobalRenderDevice()
{
	RenderDevicePlatform = ERenderDevicePlatnform::DX12Raster;
}

DX12GlobalRenderDevice::~DX12GlobalRenderDevice()
{
	ULONG refCnt = g_D3DDevice->Release();
	if (refCnt != 0)
	{
		IDXGIDebug1* Debug = nullptr;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&Debug))))
		{
			Debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY);
			Debug->Release();
		}
		__debugbreak();
	}
}
