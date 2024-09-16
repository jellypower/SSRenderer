#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSContainer/SHasher.h"

/**
* RenderWorld에 포함되는 실제 렌더링 될 객체
*/
class SSRenderInstance
{
public:
	SS::SHashA GetName() { return _name; }
	Transform GetTransform() { return _relativeTransform; }


private:
	SS::SHashA _name;
	Transform _relativeTransform;
};

