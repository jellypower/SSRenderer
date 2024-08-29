#pragma once
#ifdef _WINDOWS

typedef long long int			int64;
typedef int						int32;
typedef short					int16;
typedef char					int8;

typedef unsigned long long		uint64;
typedef unsigned int			uint32;
typedef unsigned short			uint16;
typedef unsigned char			uint8;

typedef unsigned char			byte;

typedef wchar_t					utf16;
typedef char					utf8;

constexpr uint32 SS_UINT32_MAX = 0xffffffff;

#define FORCEINLINE __forceinline
#define PATH_LEN_MAX 260
#define ASSET_NAME_LEN_MAX 128

#endif


#define SS_DECLARE_AS_SINGLETON(CLASS_NAME)				\
private:												\
	static CLASS_NAME* g_instance;						\
public:													\
	static FORCEINLINE CLASS_NAME* Get() {				\
		assert(g_instance != nullptr);					\
		return g_instance;								\
	}													\
	static FORCEINLINE void Release() {					\
		delete g_instance;								\
		g_instance = nullptr;							\
	}													\
private:



#define SS_DECLARE_ASSET_MANAGER(CLASS_NAME)																							\
	friend class SSFBXImporter;																											\
	SS_DECLARE_AS_SINGLETON(CLASS_NAME)																									\
	static FORCEINLINE void Instantiate(uint32 poolCapacity, uint32 hashCapacity, uint32 hashCollisionLimit, uint64 hashSeed) {			\
		if (g_instance != nullptr) {																									\
			assert(false);																												\
			return;																														\
		}																																\
		g_instance = DBG_NEW CLASS_NAME(poolCapacity, hashCapacity, hashCollisionLimit, hashSeed);										\
	}																																	\
	static FORCEINLINE AssetType* FindAssetWithName(const char* name) { return g_instance->_assetContainer.FindAssetWithName(name); }	\
	static FORCEINLINE AssetType* GetAsset(uint32 idx) { return g_instance->_assetContainer.GetAssetWithIdx(idx); }						\
	CLASS_NAME(uint32 poolCapacity, uint32 hashCapacity, uint32 hashCollisionLimit, uint64 hashSeed);									
