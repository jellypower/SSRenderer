#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSRenderer/Public/RenderBase/ISSRenderer.h"
#include "SSRenderer/Public/RenderCommon/SSRendererInlineSettings.h"

#include <d3d12.h>
#include <dxgidebug.h>
#include <dxgi1_4.h>


class SSRenderInstance;
class GlobalRenderDeviceBase;

class SSDX12Renderer : public ISSRenderer
{
	friend ISSRenderer* CreateRenderer(HINSTANCE InhInst, HWND InhWnd, GlobalRenderDeviceBase** OutGlobalRenderDevice);

public:
	virtual ~SSDX12Renderer();


public:
	// TODO:
	/**
	1. CreateRenderWorld -> 언리얼의 FScene같은거 만들기 (물리는 CreatePhysicsWorld같이 만들자)
		-> RenderPool은 렌더 인스턴스들을 이빨빠지지 않는 일련의 Pool에 랜덤한 순서로 담고있음
	2. 현재 DX12Renderer에 있는 객체들을 GlobalRenderDeviceBase 라는 클래스를 상속하여 넣어주면 좋을거 같음. 파생 클래스로는 GlobalRenderDeviceDX11, GlobalRenderDeviceDX12 등등...
		- CreateGlobalRenderDevice라는 함수를 만들어주자.
		- 스레드 핸들, 이벤트 객체와 같은 녀석들을 전부 해당 객체에 넣어주자.

	*/

	// TODO: CreateRenderWorld
	SSRenderInstance* CreateTempRenderInstance();

private:
	HINSTANCE hInst = NULL;
	HWND hWnd = NULL;


	ID3D12CommandQueue* _D3DCommandQueue = nullptr;

	IDXGISwapChain3* _swapChain = nullptr;
	uint32 _renderTargetIdx = 0;
	D3D12_VIEWPORT _viewportSize;
	D3D12_RECT _scissorRectSize;

	ID3D12Resource* _renderTargets[SWAP_CHAIN_FRAME_COUNT] = {};

	ID3D12DescriptorHeap* _RTVDescHeap = nullptr;
	uint32 _RTVDescriptorSize = 0;
};

