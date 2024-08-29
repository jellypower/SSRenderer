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
	1. CreateRenderWorld -> �𸮾��� FScene������ ����� (������ CreatePhysicsWorld���� ������)
		-> RenderWorld�� ��ũ�� ����Ʈ�� ����� Ʈ�� ���·� ���� ����Ʈ�� �������
			-> RenderInstance�� �����ϴ� RenderNode��� ��ü�� ���� ���� �ν��Ͻ��� ��Ƶ�
			-> RenderNode�� Prev, Next, Child�� ������ ����
		-> RenderPool�� ���� �ν��Ͻ����� �̻������� �ʴ� �Ϸ��� Pool�� ������ ������ �������
		-> RenderMap�� RenderInstance�� SHaser���� �ؽ������� ����ϴ� �ؽ����� ���� RenderPool�� �ε����� ã�� �� �ְ� ��������
	2. CreateRenderInstance -> Material�� Mesh ������ �־��ָ� ���� �ν��Ͻ� ������ֱ�
		-> RenderInstance�� SkinnedMesh, StaticMesh, BlankMesh(�ܼ� ��ġ ǥ���� �޽�) ���� Ÿ���� ������ ����
		-> RenderInstance�� ���� ���� ������ SkinnesMeshDX12, StaticMeshDX12�� ���� ��ü�� �����ϰ� ����
	3. ���� DX12Renderer�� �ִ� ��ü���� GlobalRenderDeviceBase ��� Ŭ������ ����Ͽ� �־��ָ� ������ ����. �Ļ� Ŭ�����δ� GlobalRenderDeviceDX11, GlobalRenderDeviceDX12 ���...
		- CreateGlobalRenderDevice��� �Լ��� ���������.

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

