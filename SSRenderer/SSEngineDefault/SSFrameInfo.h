#pragma once
#include <Windows.h>

#include "SSEngineDefault/SSVector.h"
#include "SSDebugLogger.h"
#include "SSNativeKeywords.h"


class SSFrameInfo
{
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	friend int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow);

	static SSFrameInfo* _instance;

private:

	uint64 _perfFrequency = 0;

	uint64 _frameCount = 0;
	double _deltaTime = 0;
	double _elapsedTime = 0;
	uint64 _previousTick = 0;
	uint64 _currentTick = 0;

	double _FPSCheckStopWatch = 0;
	uint64 _frameCntDuringInFPSCheckterval = 0;
	uint64 _FPS = 0;

	uint64 _FPSCheckCnt = 0;
	uint64 _lastFPSCheckTick = 0;

	Vector2ui32 _screenSize;
	Vector2ui32 _windowSize;

public:
	FORCEINLINE static SSFrameInfo* Get()
	{
		if (_instance == nullptr)
			_instance = DBG_NEW SSFrameInfo();
		return _instance;
	}

	/**
	* return DeltaTime in ms
	*/
	FORCEINLINE static double GetDeltaTime() { return _instance->_deltaTime; }
	FORCEINLINE static double GetFPS() { return _instance->_FPS; }
	FORCEINLINE static double GetElapsedTime() { return _instance->_elapsedTime; }
	FORCEINLINE static Vector2ui32 GetWindowSize() { return _instance->_windowSize; }


private:

	FORCEINLINE static void Release()
	{
		delete _instance;
		_instance = nullptr;
	}


	void BeginFrame();
	void PerFrame();
	void ProcessWindowResizeEventInternal(uint32 width, uint32 height);

	uint64 GetTickCountSS();
};

