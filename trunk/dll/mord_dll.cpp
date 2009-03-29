// mord_dll_2005.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "mord_dll.h"
#include <stdio.h>


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

    return TRUE;
}

DLL_API void test(void)
{
	printf("1");
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

