#ifdef MORD_DLL_EXPORTS
#define DLL_API extern "C"  __declspec(dllexport)
#else
#define DLL_API extern "C"  __declspec(dllimport)
#pragma comment(lib, "mord_dll.lib")
#endif

DLL_API void test(void);