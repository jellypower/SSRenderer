#include "SSAssetBase.h"


SSAssetBase::SSAssetBase(SS::SHasherW InAssetName, SS::SHasherW  InAssetPath)
	: _assetName(InAssetName), _assetPath(InAssetPath)
{
}

SSAssetBase::SSAssetBase()
	: _assetName(SS::SHasherW::Empty), _assetPath(SS::SHasherW::Empty)
{
}

SSAssetBase::~SSAssetBase()
{
}
