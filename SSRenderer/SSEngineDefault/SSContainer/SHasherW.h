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

	// String Hasher -> �̸� �ؽ̵� String���� ���Ͽ� ��Ʈ�� �� ȿ���� �����ִ� Ŭ����
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
				uint32 _hashH; // �ؽ� ���� 32��Ʈ
				uint32 _hashL; // �ؽ� ���� 32��Ʈ
			};
			uint64 _hashX; // �ؽ� 64��Ʈ ��ü��
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