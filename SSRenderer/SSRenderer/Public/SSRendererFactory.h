#pragma once
#include <Windows.h>


class ISSRenderer;
class GlobalRenderDeviceBase;
class MeshAssetManager;

ISSRenderer* CreateRenderer(HINSTANCE InhInst, HWND InhWnd, GlobalRenderDeviceBase** OutGlobalRenderDevice);
MeshAssetManager* CreateMeshAssetManager();