#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSAssetBase.h"


struct PipelineParameterSet
{
	SS::SHasherA VSName;
	SS::SHasherA PSName;

};

class PipelineAsset : public SSAssetBase
{
	PipelineAsset(SS::SHasherA InName);

protected:

};

