#pragma once
#include "SSEngineDefault/SSEngineDefault.h"

/**
* RenderWorld�� ���ԵǴ� ���� ������ �� ��ü
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

