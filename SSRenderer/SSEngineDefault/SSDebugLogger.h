#pragma once
#include<assert.h>

#ifdef _DEBUG

#ifdef _WINDOWS

#include<tchar.h>
#include<intrin.h>
#include<dxgidebug.h>

#endif


#include<stdio.h>
#include<typeinfo>
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

#define SS_LOG(...) printf_s(__VA_ARGS__) 
#define WSS_LOG(...) wprintf(__VA_ARGS__)

#define __CLASS__ (typeid(*this).name())

#define SS_LOG_CLASS_FUNC_LINE() printf_s("%s::%s, Line: %d:", __CLASS__, __func__, __LINE__)

#define SS_CLASS_ERR_LOG(...) SS_LOG_CLASS_FUNC_LINE(), \
    printf_s(", ERROR) " __VA_ARGS__), __debugbreak()

#define WSS_CLASS_ERR_LOG(...) SS_LOG_CLASS_FUNC_LINE(), \
    printf_s(", WARNING) " __VA_ARGS__), __debugbreak()

#define SS_CLASS_WARNING_LOG(...) SS_LOG_CLASS_FUNC_LINE(), \
    printf_s(", WARNING) " __VA_ARGS__), __debugbreak()


#define SS_ASSERT(EXPRESSION, ...) (void)(				\
			(!!(EXPRESSION)) ||									\
			(SS_CLASS_ERR_LOG(__VA_ARGS__), 0))

#define WASSERT_WITH_MESSAGE(EXPRESSION, MESSAGE) (void)(										\
            (!!(EXPRESSION)) ||                                                                 \
            (_wassert((L##MESSAGE), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0))

#define ASSERT_WITH_MESSAGE(EXPRESSION, MESSAGE) (void)(										\
            (!!(EXPRESSION)) ||                                                                 \
            (assert(MESSAGE), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0)

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define DBG_NEW new (_NORMAL_BLOCK , __FILE__ , __LINE__)
#define DBG_MALLOC(s) _malloc_dbg(s,_NORMAL_BLOCK,__FILE__,__LINE__)
#include <stdlib.h>

#define DEBUG_BREAK() __debugbreak()
#define SS_INTEERUPT() __debugbreak()

// ======================================================================================
#else
#include <new>

#define SS_LOG(...) 
#define WSS_LOG(...)
#define __CLASS__ 
#define SS_CLASS_ERR_LOG(...)
#define SS_CLASS_WARNING_LOG(...)

#define SS_ASSERT_WITH_MESSAGE(...)
#define WASSERT_WITH_MESSAGE(...)
#define ASSERT_WITH_MESSAGE(...)
#define SS_ASSERT(...)

#define WSS_CLASS_ERR_LOG(...)

#define DBG_NEW new
#define DBG_MALLOC(s) malloc(s)

#define DEBUG_BREAK()
#define INTEERUPT() __debugbreak()

#endif