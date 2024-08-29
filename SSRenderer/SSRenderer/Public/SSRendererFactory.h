#pragma once
#include <Windows.h>


class ISSRenderer;


ISSRenderer* CreateRenderer(HINSTANCE InhInst, HWND InhWnd);
