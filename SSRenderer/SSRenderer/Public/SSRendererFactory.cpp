#include "SSRendererFactory.h"

#include "SSEngineDefault/SSEngineDefault.h"
#include "SSRenderer/Private/DX12/Renderer/SSDX12Renderer.h"
#include "SSRenderer/Private/DX12/RenderAsset/DX12MeshAssetManager.h"
#include "SSRenderer/Private/DX12/Renderer/DX12GlobalRenderDevice.h"


#include <dxgi.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <dxgidebug.h>

ISSRenderer* CreateRenderer(HINSTANCE InhInst, HWND InhWnd, GlobalRenderDeviceBase** OutGlobalRenderDevice)
{
	SSDX12Renderer* newRenderer = DBG_NEW SSDX12Renderer();
	DX12GlobalRenderDevice* newGRD = DBG_NEW DX12GlobalRenderDevice();

	newRenderer->hInst = InhInst;
	newRenderer->hWnd = InhWnd;

	BOOL	Result = FALSE;

	HRESULT hr = S_OK;
	ID3D12Debug* DebugController = nullptr;
	IDXGIFactory4* Factory = nullptr;
	IDXGIAdapter1* Adapter = nullptr;
	DXGI_ADAPTER_DESC1 AdapterDesc = {};

	DWORD CreateFlags = 0;
	DWORD CreateFactoryFlags = 0;


	if (ENABLE_DEBUG_LAYER)
	{
		// Enable the D3D12 debug layer.
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController))))
		{
			DebugController->EnableDebugLayer();
		}
		CreateFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
		if (ENABLE_GPU_BASE_VALIDATIION)
		{
			ID3D12Debug5* DebugController5 = nullptr;
			if (S_OK == DebugController->QueryInterface(IID_PPV_ARGS(&DebugController5)))
			{
				DebugController5->SetEnableGPUBasedValidation(TRUE);
				DebugController5->SetEnableAutoName(TRUE);
				DebugController5->Release();
			}
		}
	}

	CreateDXGIFactory2(CreateFactoryFlags, IID_PPV_ARGS(&Factory));

	D3D_FEATURE_LEVEL	featureLevels[] =
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	DWORD	FeatureLevelNum = _countof(featureLevels);

	for (DWORD featerLevelIndex = 0; featerLevelIndex < FeatureLevelNum; featerLevelIndex++)
	{
		UINT adapterIndex = 0;
		while (DXGI_ERROR_NOT_FOUND != Factory->EnumAdapters1(adapterIndex, &Adapter))
		{
			Adapter->GetDesc1(&AdapterDesc);

			if (SUCCEEDED(D3D12CreateDevice(Adapter, featureLevels[featerLevelIndex], IID_PPV_ARGS(&newGRD->g_D3DDevice))))
			{
				goto lb_exit;
			}
			Adapter->Release();
			Adapter = nullptr;
			adapterIndex++;
		}
	}
lb_exit:

	if (newGRD->g_D3DDevice == nullptr)
	{
		DEBUG_BREAK();
		return nullptr;
	}
	ID3D12Device5* D3DDevice = newGRD->g_D3DDevice;

	if (DebugController != nullptr)
	{
		ID3D12InfoQueue* InfoQueue = nullptr;
		D3DDevice->QueryInterface(IID_PPV_ARGS(&InfoQueue));
		if (InfoQueue != nullptr)
		{
			InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
			InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);

			D3D12_MESSAGE_ID hide[] =
			{
				D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,
				D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,
				// Workarounds for debug layer issues on hybrid-graphics systems
				D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_WRONGSWAPCHAINBUFFERREFERENCE,
				D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
			};
			D3D12_INFO_QUEUE_FILTER filter = {};
			filter.DenyList.NumIDs = (UINT)_countof(hide);
			filter.DenyList.pIDList = hide;
			InfoQueue->AddStorageFilterEntries(&filter);

			InfoQueue->Release();
			InfoQueue = nullptr;
		}
		else
		{
			DEBUG_BREAK();
		}
	}


	// Create Command Queue
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		hr = D3DDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&newRenderer->_D3DCommandQueue));
		if (FAILED(hr))
		{
			DEBUG_BREAK();
			return nullptr;
		}
	}


	// Create Descriptor Heap
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = SWAP_CHAIN_FRAME_COUNT;	// SwapChain Buffer 0	| SwapChain Buffer 1
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if (FAILED(D3DDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&newRenderer->_RTVDescHeap))))
		{
			DEBUG_BREAK();
			return nullptr;
		}

		newRenderer->_RTVDescriptorSize = D3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	RECT	rect;
	::GetClientRect(InhWnd, &rect);
	uint32 WndWidth = rect.right - rect.left;
	uint32 WndHeight = rect.bottom - rect.top;
	uint32 BackBufferWidth = WndWidth;
	uint32 BackBufferHeight = WndHeight;


	// Describe and create the swap chain.
	IDXGISwapChain3* localSwapChain;
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = BackBufferWidth;
		swapChainDesc.Height = BackBufferHeight;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = SWAP_CHAIN_FRAME_COUNT;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Scaling = DXGI_SCALING_NONE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
		swapChainDesc.Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;


		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		IDXGISwapChain1* SwapChain1 = nullptr;
		if (FAILED(Factory->CreateSwapChainForHwnd(newRenderer->_D3DCommandQueue, InhWnd, &swapChainDesc, &fsSwapChainDesc, nullptr, &SwapChain1)))
		{
			DEBUG_BREAK();
			return nullptr;
		}
		SwapChain1->QueryInterface(IID_PPV_ARGS(&newRenderer->_swapChain));
		if (newRenderer->_swapChain == nullptr)
		{
			DEBUG_BREAK();
			return nullptr;
		}

		localSwapChain = newRenderer->_swapChain;

		newRenderer->_renderTargetIdx = localSwapChain->GetCurrentBackBufferIndex();
		SwapChain1->Release();
		SwapChain1 = nullptr;
	}

	newRenderer->_viewportSize.Width = WndWidth;
	newRenderer->_viewportSize.Height = WndHeight;
	newRenderer->_viewportSize.MinDepth = 0.f;
	newRenderer->_viewportSize.MaxDepth = 1.f;

	newRenderer->_scissorRectSize.left = 0;
	newRenderer->_scissorRectSize.top = 0;
	newRenderer->_scissorRectSize.right = WndWidth;
	newRenderer->_scissorRectSize.bottom = WndHeight;


	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(newRenderer->_RTVDescHeap->GetCPUDescriptorHandleForHeapStart());

		for (uint32 i = 0; i < SWAP_CHAIN_FRAME_COUNT; i++)
		{
			ID3D12Resource* Buffer;
			localSwapChain->GetBuffer(i, IID_PPV_ARGS(&Buffer));
			newRenderer->_renderTargets[i] = Buffer;
			D3DDevice->CreateRenderTargetView(newRenderer->_renderTargets[i], nullptr, rtvHandle);
			rtvHandle.ptr += newRenderer->_RTVDescriptorSize;
		}
	}

	if (DebugController)
	{
		DebugController->Release();
		DebugController = nullptr;
	}
	if (Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}
	if (Factory)
	{
		Factory->Release();
		Factory = nullptr;
	}
	
	if (OutGlobalRenderDevice == nullptr)
	{
		DEBUG_BREAK();
		return nullptr;
	}
	*OutGlobalRenderDevice = newGRD;
	
	return newRenderer;
}

MeshAssetManager* CreateMeshAssetManager()
{
	DX12MeshAssetManager* MeshAssetManager = DBG_NEW DX12MeshAssetManager();

	return MeshAssetManager;
}
