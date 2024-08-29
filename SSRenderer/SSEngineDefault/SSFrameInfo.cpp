#include "SSFrameInfo.h"


SSFrameInfo* SSFrameInfo::_instance = nullptr;


constexpr double FRAME_LOW_LIMIT = 1 / 1000.0;

uint64 SSFrameInfo::GetTickCountSS()
{
	LARGE_INTEGER newTickLI;
	QueryPerformanceCounter(&newTickLI);
	return newTickLI.QuadPart;
}


void SSFrameInfo::BeginFrame()
{
	LARGE_INTEGER freqLI;
	QueryPerformanceFrequency(&freqLI);
	_perfFrequency = freqLI.QuadPart;

	_currentTick = GetTickCountSS();
	_lastFPSCheckTick = _currentTick;
}

void SSFrameInfo::PerFrame()
{
	_frameCount++;
	_frameCntDuringInFPSCheckterval++;

	_previousTick = _currentTick;
	_currentTick = GetTickCountSS();

	uint64 tickDiff = _currentTick - _previousTick;

	if (tickDiff == 0)
	{
		_deltaTime = FRAME_LOW_LIMIT;
		__debugbreak();
	}
	else
	{
		_deltaTime = (double)tickDiff / (double)_perfFrequency;
	}

	_FPSCheckStopWatch += _deltaTime;
	if (_FPSCheckStopWatch > 1)
	{
		_FPS = _frameCntDuringInFPSCheckterval;
		_FPSCheckStopWatch = 0;
		_frameCntDuringInFPSCheckterval = 0;
	}

	_elapsedTime += _deltaTime;
}

void SSFrameInfo::ProcessWindowResizeEventInternal(uint32 width, uint32 height)
{
	_windowSize.X = width;
	_windowSize.Y = height;
}
