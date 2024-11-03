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
	1. CreateRenderWorld -> �𸮾��� FScene������ ����� (������ CreatePhysicsWorld���� ������)
		-> RenderPool�� ���� �ν��Ͻ����� �̻������� �ʴ� �Ϸ��� Pool�� ������ ������ �������
	2. ���� DX12Renderer�� �ִ� ��ü���� GlobalRenderDeviceBase ��� Ŭ������ ����Ͽ� �־��ָ� ������ ����. �Ļ� Ŭ�����δ� GlobalRenderDeviceDX11, GlobalRenderDeviceDX12 ���...
		- CreateGlobalRenderDevice��� �Լ��� ���������.
		- ������ �ڵ�, �̺�Ʈ ��ü�� ���� �༮���� ���� �ش� ��ü�� �־�����.

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

