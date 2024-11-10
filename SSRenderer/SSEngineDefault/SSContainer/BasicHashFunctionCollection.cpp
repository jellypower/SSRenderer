#include "BasicHashFunctionCollection.h"

int32 HashValue(int32 inValue)
{
	return inValue;
}

int32 HashValue(int64 inValue)
{
	return static_cast<int32>(inValue);
}

int32 HashValue(const SS::SHasherW& inValue)
{
	return static_cast<int32>(inValue.GetDirectValue());
}
