#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSAssetBase.h"


struct PipelineParameterSet
{
	SS::SHashA VSName;
	SS::SHashA PSName;

};

class PipelineAsset : public SSAssetBase
{
	PipelineAsset(SS::SHashA InName);

protected:

};

