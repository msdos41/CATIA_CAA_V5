#ifdef  _WINDOWS_SOURCE
#ifdef  __TestToolingMod
#define ExportedByTestToolingMod     __declspec(dllexport)
#else
#define ExportedByTestToolingMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestToolingMod
#endif
