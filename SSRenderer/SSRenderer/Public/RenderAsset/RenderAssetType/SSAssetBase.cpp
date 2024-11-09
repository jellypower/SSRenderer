#include "SSAssetBase.h"


SSAssetBase::SSAssetBase(SS::SHasherA InAssetName, SS::SHasherA  InAssetPath)
	: _assetName(InAssetName), _assetPath(InAssetPath)
{
}

SSAssetBase::SSAssetBase()
	: _assetName(SS::SHasherA::Empty), _assetPath(SS::SHasherA::Empty)
{
}

SSAssetBase::~SSAssetBase()
{
}
