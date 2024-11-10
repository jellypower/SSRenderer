#pragma once
#include "SSEngineDefault/SSEngineInlineSettings.h"
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineMain/SSEngine.h"


namespace SS {
	class SHasherW;

	class SHashPoolNode
	{
		friend class SHasherW;
	private:
		utf16* _str = nullptr;
		uint32 _strLen = 0;
		SHashPoolNode* _next = nullptr;

	public:
		SHashPoolNode();
		SHashPoolNode(const utf16* str, uint32 inStrLen);
	};
}

namespace SS {

	// String Hasher -> 미리 해싱된 String값을 비교하여 스트링 비교 효율을 높혀주는 클래스
	class SHasherW
	{
		friend void ::EngineEndFrame();
	public:
		static SHasherW Empty;
	private:
		static SHashPoolNode* g_SHasherPool;
		static uint32 g_sHasherPoolCnt;

	private:

		union {
			struct {
				uint32 _hashH; // 해쉬 상위 32비트
				uint32 _hashL; // 해쉬 하위 32비트
			};
			uint64 _hashX; // 해쉬 64비트 전체값
		};


	public:
		SHasherW(const utf16* str);

		bool operator==(SHasherW rhs) const;
		const utf16* C_Str(uint32* const outStrLen = nullptr) const;
		uint64 GetDirectValue() const { return _hashX; }

	private:
		static void InitHashPool(uint32 hashPoolSize = SHASHER_DEFAULT_POOL_SIZE);
		static void ClearHashPool();

	};

};