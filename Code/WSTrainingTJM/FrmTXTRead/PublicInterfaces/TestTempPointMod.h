#ifdef  _WINDOWS_SOURCE
#ifdef  __TestTempPointMod
#define ExportedByTestTempPointMod     __declspec(dllexport)
#else
#define ExportedByTestTempPointMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestTempPointMod
#endif
