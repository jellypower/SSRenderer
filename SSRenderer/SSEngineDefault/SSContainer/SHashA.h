#pragma once
#include "SSEngineDefault/SSEngineInlineSettings.h"
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineMain/SSEngine.h"

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

	// String Hasher -> �̸� �ؽ̵� String���� ���Ͽ� ��Ʈ�� �� ȿ���� �����ִ� Ŭ����
	class SHashA
	{
		friend void ::EngineEndFrame();
	private:
		static SHashPoolNode* g_SHasherPool;
		static uint32 g_sHasherPoolCnt;

	private:

		union {
			struct {
				uint32 _hashH; // �ؽ� ���� 32��Ʈ
				uint32 _hashL; // �ؽ� ���� 32��Ʈ
			};
			uint64 _hashX; // �ؽ� 64��Ʈ ��ü��
		};


	public:
		SHashA(const char* str);

		bool operator==(SHashA rhs) const;
		const char* c_str(uint32* const outStrLen = nullptr) const;
		uint64 GetDirectValue() const { return _hashX; }

	private:
		static void InitHashPool(uint32 hashPoolSize = SHASHER_DEFAULT_POOL_SIZE);
		static void ClearHashPool();

	};

};