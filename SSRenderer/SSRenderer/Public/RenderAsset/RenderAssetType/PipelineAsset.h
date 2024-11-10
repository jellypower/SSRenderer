#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSAssetBase.h"


struct PipelineParameterSet
{
	SS::SHasherW VSName;
	SS::SHasherW PSName;

};

class PipelineAsset : public SSAssetBase
{
	PipelineAsset(SS::SHasherW InName);

protected:

};

