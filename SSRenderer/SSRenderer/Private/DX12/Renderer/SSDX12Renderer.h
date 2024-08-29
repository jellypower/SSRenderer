#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSRenderer/Public/RenderInterface/ISSRenderer.h"
#include "SSRenderer/Public/RenderCommon/SSRendererInlineSettings.h"

#include <d3d12.h>
#include <dxgidebug.h>
#include <dxgi1_4.h>


class SSRenderInstance;

class SSDX12Renderer : public ISSRenderer
{
	friend ISSRenderer* CreateRenderer(HINSTANCE InhInst, HWND InhWnd);

public:
	virtual ~SSDX12Renderer() override;


public:
	// TODO:
	/**
	1. CreateRenderWorld -> 언리얼의 FScene같은거 만들기 (물리는 CreatePhysicsWorld같이 만들자)
		-> RenderWorld는 링크드 리스트로 연결된 트리 형태로 렌더 리스트를 담고있음
			-> RenderInstance를 포함하는 RenderNode라는 객체를 통해 렌더 인스턴스를 담아둠
			-> RenderNode는 Prev, Next, Child를 가지고 있음
		-> RenderPool은 렌더 인스턴스들을 이빨빠지지 않는 일련의 Pool에 랜덤한 순서로 담고있음
		-> RenderMap은 RenderInstance의 SHaser값을 해쉬값으로 사용하는 해쉬맵을 통해 RenderPool의 인덱스를 찾을 수 있게 만들어놓음
	2. CreateRenderInstance -> Material과 Mesh 에셋을 넣어주면 렌더 인스턴스 만들어주기
		-> RenderInstance는 SkinnedMesh, StaticMesh, BlankMesh(단순 위치 표현용 메쉬) 등의 타입을 가지고 있음
		-> RenderInstance는 실제 렌더 가능한 SkinnesMeshDX12, StaticMeshDX12와 같은 객체를 포함하고 있음
	3. 현재 DX12Renderer에 있는 객체들을 GlobalRenderDeviceBase 라는 클래스를 상속하여 넣어주면 좋을거 같음. 파생 클래스로는 GlobalRenderDeviceDX11, GlobalRenderDeviceDX12 등등...
		- CreateGlobalRenderDevice라는 함수를 만들어주자.

	*/

	// TODO: CreateRenderWorld
	SSRenderInstance* CreateTempRenderInstance();

private:


private:
	HINSTANCE hInst = NULL;
	HWND hWnd = NULL;

	ID3D12Device5* _D3DDevice = nullptr;
	ID3D12CommandQueue* _D3DCommandQueue = nullptr;

	IDXGISwapChain3* _swapChain = nullptr;
	uint32 _renderTargetIdx = 0;
	D3D12_VIEWPORT _viewportSize;
	D3D12_RECT _scissorRectSize;

	ID3D12Resource* _renderTargets[SWAP_CHAIN_FRAME_COUNT] = {};

	ID3D12DescriptorHeap* _RTVDescHeap = nullptr;
	uint32 _RTVDescriptorSize = 0;
};

