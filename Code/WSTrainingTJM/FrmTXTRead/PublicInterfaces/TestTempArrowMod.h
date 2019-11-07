#ifdef  _WINDOWS_SOURCE
#ifdef  __TestTempArrowMod
#define ExportedByTestTempArrowMod     __declspec(dllexport)
#else
#define ExportedByTestTempArrowMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestTempArrowMod
#endif
