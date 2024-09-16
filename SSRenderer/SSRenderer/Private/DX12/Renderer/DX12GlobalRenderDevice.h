#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSRenderer/Public/RenderBase/GlobalRenderDeviceBase.h"
#include <d3d12.h>

class ISSRenderer;


class DX12GlobalRenderDevice : public GlobalRenderDeviceBase
{
	friend ISSRenderer* CreateRenderer(HINSTANCE InhInst, HWND InhWnd, GlobalRenderDeviceBase** OutGlobalRenderDevice);
public:
	DX12GlobalRenderDevice();
	virtual ~DX12GlobalRenderDevice() override;

	ID3D12Device5* GetD3DDevice() { return g_D3DDevice; }

private:
	ID3D12Device5* g_D3DDevice = nullptr;


};

