#include "SSDX12RenderFactory.h"
#include "SSRenderer/Private/DX12/RenderAsset/DX12RootSignatureAssetManager.h"
#include "SSRenderer/Private/DX12/Renderer/DX12RGlobalenderInstanceCollection.h"

DX12RootSignatureAssetManager* CreateRootSignatureAssetManager()
{
	g_RootSignatureAssetManager = DBG_NEW DX12RootSignatureAssetManager();
	return g_RootSignatureAssetManager;
}
