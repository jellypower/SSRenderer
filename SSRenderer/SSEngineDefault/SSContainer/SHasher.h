#pragma once
#include "SSEngineDefault/SSEngineInlineSettings.h"
#include "SSEngineDefault/SSEngineDefault.h"

namespace SS {
	class SHashA;

	class SHashPoolNode
	{
		friend class SHashA;
	private:
		char* _str = nullptr;
		uint32 _strLen = 0;
		SHashPoolNode* _next = nullptr;

	public:
		SHashPoolNode();
		SHashPoolNode(const char* str, uint32 inStrLen);
	};
}

namespace SS {

	// String Hasher -> 미리 해싱된 String값을 비교하여 스트링 비교 효율을 높혀주는 클래스
	class SHashA
	{
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
		static void InitHashPool(uint32 hashPoolSize = SHASHER_DEFAULT_POOL_SIZE); // TODO: InithHashPool 구현하기
		static void ClearHashPool();



	public:
		SHashA(const char* str);

		bool operator==(SHashA rhs) const;
		const char* c_str() const;


	};

};