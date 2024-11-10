#include "SHasherW.h"

#include "CityHash.h"
#include "SSEngineDefault/UtilityFunctions.h"
using namespace SS;


SS::SHashPoolNode::SHashPoolNode()
{
}

SHashPoolNode::SHashPoolNode(const utf16* inStr, uint32 inStrLen)
{
	_strLen = inStrLen;
	_str = DBG_NEW utf16[_strLen + 1];
	memcpy(_str, inStr, (inStrLen + 1) * sizeof(utf16));
}



SHashPoolNode* SHasherW::g_SHasherPool = nullptr;
uint32 SHasherW::g_sHasherPoolCnt = 0;
SHasherW SHasherW::Empty = SHasherW(L"EMPTY");


void SHasherW::ClearHashPool()
{
	for (uint32 i = 0; i < g_sHasherPoolCnt; i++)
	{
		if (g_SHasherPool[i]._str != nullptr)
		{
			SHashPoolNode* curNode = &g_SHasherPool[i];
			delete curNode->_str;

			curNode = curNode->_next;
			while (curNode != nullptr)
			{
				SHashPoolNode* nextNode = curNode->_next;
				delete curNode->_str;
				delete curNode;
				curNode = nextNode;
			}
		}
	}

	delete g_SHasherPool;
	g_SHasherPool = nullptr;
}

void SS::SHasherW::InitHashPool(uint32 hashPoolSize)
{
	g_SHasherPool = DBG_NEW SHashPoolNode[hashPoolSize];
	g_sHasherPoolCnt = hashPoolSize;
}

SHasherW::SHasherW(const utf16* inStr)
	: _hashX(0)
{
	if (g_SHasherPool == nullptr)
	{
		InitHashPool();
	}

	const int64 inStrlen = wcslen(inStr);
	if(inStrlen > SHASHER_STRLEN_MAX)
	{
		_hashX = SHasherW::Empty._hashX;
		return;
	}

	utf16 loweredStr[SHASHER_STRLEN_MAX + 1];

	
	SS::LowerStr(inStr, loweredStr);


	const uint32 strHashValue = CityHash32(reinterpret_cast<const char*>(loweredStr), inStrlen * (sizeof(utf16) / sizeof(char) )) % g_sHasherPoolCnt;

	SHashPoolNode* curHashPoolNode = &g_SHasherPool[strHashValue];
	uint32 sameHashValueCnt = 0;

	if (curHashPoolNode->_str == nullptr) // 처음에 해당 해쉬 어레이가 메모리 풀만 할당되고 아무 값도 들어있지 않은 경우
	{
		new(curHashPoolNode) SHashPoolNode(inStr, inStrlen);
		_hashH = strHashValue;
		_hashL = sameHashValueCnt;
		return;
	}

	while (true)
	{
		if (wcscmp(curHashPoolNode->_str, loweredStr) == 0)
		{
			_hashH = strHashValue;
			_hashL = sameHashValueCnt;
			return;
		}

		if (curHashPoolNode->_next == nullptr)
		{
			break;
		}
		else
		{
			sameHashValueCnt++;
			curHashPoolNode = curHashPoolNode->_next;
		}
	}

	sameHashValueCnt++;
	curHashPoolNode->_next = DBG_NEW SHashPoolNode(inStr, inStrlen);

	_hashH = strHashValue;
	_hashL = sameHashValueCnt;
}

bool SHasherW::operator==(SHasherW rhs) const
{
	if (this->_hashX == SHasherW::Empty._hashX ||
		rhs._hashX == SHasherW::Empty._hashX) return false;
	return this->_hashX == rhs._hashX;
}

const utf16* SHasherW::C_Str(uint32* const outStrLen) const
{
	SHashPoolNode* curHashPoolNode = &g_SHasherPool[_hashH];

	for (uint32 i = 0; i < _hashL; i++)
	{
		curHashPoolNode = curHashPoolNode->_next;
	}

	if (outStrLen != nullptr)
	{
		*outStrLen = curHashPoolNode->_strLen;
	}

	return curHashPoolNode->_str;
}