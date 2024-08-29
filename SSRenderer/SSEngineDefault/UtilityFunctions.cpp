#include "UtilityFunctions.h"
#include "SSDebugLogger.h"
#include "Windows.h"

uint32 SS::CharStrToUTF16Str(const char* charStr, uint32 charLen, utf16* outUtf16Str, uint32 utf16StrBufferSize)
{
	uint32 multibyteLen = MultiByteToWideChar(CP_ACP, 0, charStr, charLen, nullptr, 0);
	assert(multibyteLen < utf16StrBufferSize);
	multibyteLen = MultiByteToWideChar(CP_ACP, 0, charStr, charLen, outUtf16Str, utf16StrBufferSize);
	outUtf16Str[multibyteLen] = L'\0';
	return multibyteLen;
}

uint32 SS::UTF16StrToUtf8Str(const utf16* utf16Str, uint32 utf16StrLen, utf8* outUtf8Str, uint32 utf8BufferSize)
{
	int32 writtenBytes = WideCharToMultiByte(CP_UTF8, 0, utf16Str, utf16StrLen, NULL, 0, NULL, NULL);
	assert(writtenBytes < utf8BufferSize);
	writtenBytes = WideCharToMultiByte(CP_UTF8, 0, utf16Str, utf16StrLen, outUtf8Str, writtenBytes, NULL, NULL);
	outUtf8Str[writtenBytes] = '\0';
	return writtenBytes;
}
