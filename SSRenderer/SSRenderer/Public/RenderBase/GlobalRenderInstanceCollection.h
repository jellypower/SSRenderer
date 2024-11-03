#pragma once
#include "SSRenderer/Public/RenderBase/GlobalRenderDeviceBase.h"
#include "SSRenderer/Public/RenderBase/ISSRenderer.h"
#include "SSRenderer/Public/RenderAsset/MeshAssetManager.h"
#include "SSRenderer/Public/RenderAsset/MaterialAssetManager.h"
#include "SSRenderer/Public/RenderAsset/ShaderAssetManager.h"

class GlobalRenderDeviceBase;
class ISSRenderer;
class MeshAssetManager;
class MaterialAssetManager;
class ShaderAssetManager;


extern GlobalRenderDeviceBase* g_RenderDevice;
extern ISSRenderer* g_Renderer;
extern MeshAssetManager* g_MeshAssetManager;
extern MaterialAssetManager* g_MaterialAssetManager;
extern ShaderAssetManager* g_ShaderAssetManager;