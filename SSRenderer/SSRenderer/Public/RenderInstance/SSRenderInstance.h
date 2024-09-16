#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSContainer/SHasher.h"

/**
* RenderWorld�� ���ԵǴ� ���� ������ �� ��ü
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

