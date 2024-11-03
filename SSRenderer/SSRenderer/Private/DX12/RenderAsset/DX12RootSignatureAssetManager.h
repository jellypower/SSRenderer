#pragma once
#include "SSEngineDefault/SSEngineDefault.h"

class DX12RootSignatureAsset;

// rootsignature�� �ܺη� ������� �ʴ� �������̽��̴�.
class DX12RootSignatureAssetManager
{
public:
	void Initialize();
	
	DX12RootSignatureAsset* CreateTempRootSignature();

public:
	DX12RootSignatureAsset* _tempRootSignatureAsset;
};

