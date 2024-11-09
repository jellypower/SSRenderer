#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSNonCopyable.h"

class SSAssetBase : public SSNoncopyable
{
private:
	SS::SHasherA _assetName;
	SS::SHasherA _assetPath;

public:
	SSAssetBase(SS::SHasherA InAssetName, SS::SHasherA InAssetPath);
	SSAssetBase();
	virtual ~SSAssetBase();

	SS::SHasherA GetAssetName() const { return _assetName; }
	SS::SHasherA GetAssetPath() const { return _assetPath; }
};

