#pragma once
#include "SSEngineDefault/SSEngineDefault.h"


// Common Params
constexpr uint32 SUBGEOM_COUNT_MAX = 8;
constexpr uint32 SWAP_CHAIN_FRAME_COUNT = 2;



#ifdef _DEBUG
constexpr bool ENABLE_DEBUG_LAYER = true;
constexpr bool ENABLE_GPU_BASE_VALIDATIION = true;


#else
constexpr bool ENABLE_DEBUG_LAYER = false;
constexpr bool ENABLE_GPU_BASE_VALIDATIION = false;

#endif
