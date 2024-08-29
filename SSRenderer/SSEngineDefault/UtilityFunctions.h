#pragma once
#include "SSNativeKeywords.h"


namespace SS
{

	// return: written string length
	uint32 CharStrToUTF16Str(const char* charStr, uint32 charLen, utf16* outUtf16Str, uint32 utf16StrBufferSize);

	// return: written bytes num
	uint32 UTF16StrToUtf8Str(const utf16* utf16Str, uint32 utf16StrLen, utf8* outUtf8Str, uint32 utf8BufferSize);
};