#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSNonCopyable.h"

class SSAssetBase : public SSNoncopyable
{
private:
	SS::SHashA _assetName;
	SS::SHashA _assetPath;

public:
	SSAssetBase(SS::SHashA InAsetName, SS::SHashA InAssetPath);
	virtual ~SSAssetBase();

	SS::SHashA GetAssetName() const { return _assetName; }
	SS::SHashA GetAssetPath() const { return _assetPath; }
};

