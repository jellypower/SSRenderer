#pragma once
#pragma warning(disable: 4996)


#include <string.h>


#include "SSEngineDefault/UtilityFunctions.h"
#include "SSEngineDefault/SSDebugLogger.h"
#include "SSEngineDefault/SSNativeKeywords.h"


namespace SS {

	template<typename T1, typename T2>
	class pair
	{
	public:
		T1 first;
		T2 second;
		pair(T1 InFirst, T2 InSecond) : first(InFirst), second(InSecond) { }
	};


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
		FORCEINLINE const uint32 GetLen() const { return _len; }

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
		strcpy(_dataPool, data);
	}

	template<uint32 STR_LEN_MAX>
	FixedStringA<STR_LEN_MAX>::FixedStringA(const FixedStringA& rhs)
	{
		_len = rhs._len;
		strcpy(_dataPool, rhs._dataPool);
	}

	template<uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Assign(const char* data)
	{
		uint32 len = strlen(data);
		assert(len < STR_LEN_MAX);
		_len = len;
		strcpy(_dataPool, data);
	}

	template<uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Assign(const char* data, uint32 len)
	{
		assert(len < STR_LEN_MAX);
		_len = len;
		strncpy(_dataPool, data, len);
		_dataPool[len] = '\0';
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Append(const char* data)
	{
		uint32 len = strlen(data);
		assert(_len + len < STR_LEN_MAX);
		strcpy(_dataPool + _len, data);
		_len += len;
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringA<STR_LEN_MAX>::Append(const char* data, uint32 len)
	{
		assert(_len + len < STR_LEN_MAX);
		strncpy(_dataPool + _len, data, len);
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


	template<uint32 STR_LEN_MAX>
	class FixedStringW {
	private:
		utf16 _dataPool[STR_LEN_MAX];
		uint32 _len;

	public:
		FixedStringW();
		FixedStringW(const char* data);
		FixedStringW(const utf16* data);
		FixedStringW(const FixedStringW& rhs);

		const utf16* C_Str() const { return _dataPool; }
		FORCEINLINE constexpr uint32 GetCapacity() const { return STR_LEN_MAX; }
		FORCEINLINE const uint32 GetLen() const { return _len; }

		void Assign(const utf16* data);
		void Assign(const utf16* data, uint32 len);

		void Append(const utf16* data);
		void Append(const utf16* data, uint32 len);

		void CutOut(uint32 newStrlen);

		FixedStringW& operator+=(const utf16* data);
		FORCEINLINE operator const utf16* () const { return C_Str(); }

		void Clear();
	};

#pragma region FixedStringA implementation
	template <uint32 STR_LEN_MAX>
	FixedStringW<STR_LEN_MAX>::FixedStringW()
	{
		_dataPool[0] = L'\0';
		_len = 0;
	}

	template <uint32 STR_LEN_MAX>
	FixedStringW<STR_LEN_MAX>::FixedStringW(const char* data)
	{
		uint32 dataLen = strlen(data);
		uint32 resultLen = CharStrToUTF16Str(data, dataLen, _dataPool, GetCapacity());
		assert(resultLen != 0);
		_len = resultLen;
	}

	template <uint32 STR_LEN_MAX>
	FixedStringW<STR_LEN_MAX>::FixedStringW(const utf16* data)
	{
		_len = wcslen(data);
		wcscpy(_dataPool, data);
	}

	template <uint32 STR_LEN_MAX>
	FixedStringW<STR_LEN_MAX>::FixedStringW(const FixedStringW& rhs)
	{
		_len = rhs.GetLen();
		wcscpy(_dataPool, rhs.C_Str());
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringW<STR_LEN_MAX>::Assign(const utf16* data)
	{
		uint32 len = wcslen(data);
		assert(len < STR_LEN_MAX);
		_len = len;
		wcscpy(_dataPool, data);
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringW<STR_LEN_MAX>::Assign(const utf16* data, uint32 len)
	{
		assert(len < STR_LEN_MAX);
		_len = len;
		wcsncpy(_dataPool, data, len);
		_dataPool[len] = L'\0';
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringW<STR_LEN_MAX>::Append(const utf16* data)
	{
		uint32 len = wcslen(data);
		assert(_len + len < STR_LEN_MAX);
		wcscpy(_dataPool + _len, data);
		_len += len;
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringW<STR_LEN_MAX>::Append(const utf16* data, uint32 len)
	{
		assert(_len + len < STR_LEN_MAX);
		wcsncpy(_dataPool + _len, data, len);
		_len += len;
		_dataPool[_len] = L'\0';
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringW<STR_LEN_MAX>::CutOut(uint32 newStrlen)
	{
		assert(newStrlen < _len);
		_len = newStrlen;
		_dataPool[_len] = L'\0';
	}

	template <uint32 STR_LEN_MAX>
	FixedStringW<STR_LEN_MAX>& FixedStringW<STR_LEN_MAX>::operator+=(const utf16* data)
	{
		Append(data);
		return *this;
	}

	template <uint32 STR_LEN_MAX>
	void FixedStringW<STR_LEN_MAX>::Clear()
	{
		_dataPool[0] = L'\0';
		_len = 0;
	}
#pragma endregion

#pragma region move, forward implementation

	template <class T>
		struct remove_reference_struct {
		using type = T;
	};

	template <class T>
	struct remove_reference_struct<T&> {
		using type = T;
	};

	template <class T>
	struct remove_reference_struct<T&&> {
		using type = T;
	};

	template <class T>
	using remove_reference = typename remove_reference_struct<T>::type;

	template <class T>
	constexpr remove_reference<T>&& move(T&& arg) noexcept {
		return static_cast<remove_reference<T>&&>(arg);
	}

	template <class T>
	constexpr T&& forward(remove_reference<T>& arg) noexcept {
		return static_cast<T&&>(arg);
	}

#pragma endregion

};