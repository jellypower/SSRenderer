#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSNonCopyable.h"

class SSAssetBase : public SSNoncopyable
{
private:
	SS::SHasherW _assetName;
	SS::SHasherW _assetPath;

public:
	SSAssetBase(SS::SHasherW InAssetName, SS::SHasherW InAssetPath);
	SSAssetBase();
	virtual ~SSAssetBase();

	SS::SHasherW GetAssetName() const { return _assetName; }
	SS::SHasherW GetAssetPath() const { return _assetPath; }
};

