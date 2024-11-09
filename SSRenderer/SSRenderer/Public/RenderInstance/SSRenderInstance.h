#pragma once
#include "SSEngineDefault/SSEngineDefault.h"

/**
* RenderWorld에 포함되는 실제 렌더링 될 객체
*/
class SSRenderInstance
{
public:
	SS::SHasherA GetName() { return _name; }
	Transform GetTransform() { return _relativeTransform; }


private:
	SS::SHasherA _name;
	Transform _relativeTransform;
};

