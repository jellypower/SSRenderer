#pragma once
#include "SSEngineDefault/SSEngineDefault.h"

/**
* RenderWorld�� ���ԵǴ� ���� ������ �� ��ü
*/
class SSRenderInstance
{
public:
	SS::SHasherW GetName() { return _name; }
	Transform GetTransform() { return _relativeTransform; }


private:
	SS::SHasherW _name;
	Transform _relativeTransform;
};

