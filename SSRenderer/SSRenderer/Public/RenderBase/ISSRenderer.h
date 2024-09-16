#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSNonCopyable.h"

class ISSRenderer : public SSNoncopyable
{
public:
	virtual ~ISSRenderer();
};

