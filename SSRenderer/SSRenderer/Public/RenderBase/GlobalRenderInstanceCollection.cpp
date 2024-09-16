#include "GlobalRenderInstanceCollection.h"

#include "ISSRenderer.h"
#include "GlobalRenderDeviceBase.h"
#include "SSRenderer/Public/RenderAsset/MeshAssetManager.h"

extern GlobalRenderDeviceBase* g_RenderDevice = nullptr;
extern ISSRenderer* g_Renderer = nullptr;
extern MeshAssetManager* g_MeshAssetManager = nullptr;