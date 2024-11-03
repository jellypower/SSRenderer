#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "CityHash.h"



int32 HashValue(int32 inValue);
int32 HashValue(int64 inValue);

int32 HashValue(const SS::SHashA& inValue);