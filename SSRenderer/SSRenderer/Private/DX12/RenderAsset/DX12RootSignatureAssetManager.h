#pragma once
#include "SSEngineDefault/SSEngineDefault.h"

class DX12RootSignatureAsset;

// rootsignature는 외부로 노출되지 않는 인터페이스이다.
class DX12RootSignatureAssetManager
{
public:
	void Initialize();
	
	DX12RootSignatureAsset* CreateTempRootSignature();

public:
	DX12RootSignatureAsset* _tempRootSignatureAsset;
};

