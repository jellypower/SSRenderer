#pragma once
#include <Windows.h>


class ISSRenderer;
class GlobalRenderDeviceBase;
class MeshAssetManager;
class MaterialAssetManager;
class ShaderAssetManager;

ISSRenderer* CreateRenderer(HINSTANCE InhInst, HWND InhWnd, GlobalRenderDeviceBase** OutGlobalRenderDevice);
MeshAssetManager* CreateMeshAssetManager();
MaterialAssetManager* CreateMaterialAssetManager();
ShaderAssetManager* CreateShaderAssetManager();