#include "SSDX12Renderer.h"

SSDX12Renderer::~SSDX12Renderer()
{
	hInst = NULL;
	hWnd = NULL;

	_RTVDescHeap->Release();
	

	for (uint32 i = 0; i < SWAP_CHAIN_FRAME_COUNT; i++)
	{
		_renderTargets[i]->Release();
	}
	_renderTargetIdx = 0;

	_swapChain->Release();
	_D3DCommandQueue->Release();
	_D3DDevice->Release();
}

SSRenderInstance* SSDX12Renderer::CreateTempRenderInstance()
{
	return nullptr;
}