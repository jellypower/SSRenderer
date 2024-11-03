#pragma once
#include <string.h>

#include "SSEngineDefault/UtilityFunctions.h"
#include "SSEngineDefault/SSDebugLogger.h"
#include "SSEngineDefault/SSNativeKeywords.h"


namespace SS {
	template<uint32 STR_LEN_MAX>
	class FixedStringA {
	private:
		char _dataPool[STR_LEN_MAX];
		uint32 _len;

	public:
		FixedStringA();
		FixedStringA(const char* data);
		FixedStringA(const FixedStringA& rhs);

		const char* C_Str() const { return _dataPool; }
		FORCEINLINE constexpr uint32 GetCapacity() const { return STR_LEN_MAX; }
		FORCEINLINE uint32 GetLen() const { return _len; }

		void Assign(const char* data);
		void Assign(const char* data, uint32 len);

		void Append(const char* data);
		void Append(const char* data, uint32 len);

		void CutOut(uint32 newStrlen);

		FixedStringA& operator+=(const char* data);
		FORCEINLINE operator const char* () const { return _dataPool; }

		void Clear();

	};
#pragma region FixedStringA implementation
	template<uint32 STR_LEN_MAX>
	FixedStringA<STR_LEN_MAX>::FixedStringA()
	{
		_dataPool[0] = '\0';
		_len = 0;
	}

	template<uint32 STR_LEN_MAX>
	FixedStringA<STR_LEN_MAX>::FixedStringA(const char* data)
	{
		_len = strlen(data);
		strcpy_s(_dataPool, data);
	}

	template<uint32 STR_LEN_MAX>
	FixedStringA<STR_LEN_MAX>::FixedStringA(const FixedStringA& rhs)
	{
		_len = rhs._len;
		strcpy_s(_dataPool, rhs._dataPool);
	}

	template<uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Assign(const char* data)
	{
		uint32 len = strlen(data);
		assert(len < STR_LEN_MAX);
		_len = len;
		strcpy_s(_dataPool, data);
	}

	template<uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Assign(const char* data, uint32 len)
	{
		assert(len < STR_LEN_MAX);
		_len = len;
		strcpy_s(_dataPool, data, len);
		_dataPool[len] = '\0';
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Append(const char* data)
	{
		uint32 len = strlen(data);
		assert(_len + len < STR_LEN_MAX);
		strcpy_s(_dataPool + _len, data);
		_len += len;
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Append(const char* data, uint32 len)
	{
		assert(_len + len < STR_LEN_MAX);
		strncpy_s(_dataPool + _len, data, len);
		_len += len;
		_dataPool[_len] = '\0';
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::CutOut(uint32 newStrlen)
	{
		assert(newStrlen < _len);
		_len = newStrlen;
		_dataPool[_len] = '\0';
	}

	template <uint32 STR_LEN_MAX>
	FixedStringA<STR_LEN_MAX>& FixedStringA<STR_LEN_MAX>::operator+=(const char* data)
	{
		Append(data);
		return *this;
	}

	template<uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Clear()
	{
		_dataPool[0] = '\0';
		_len = 0;
	}
#pragma endregion
}