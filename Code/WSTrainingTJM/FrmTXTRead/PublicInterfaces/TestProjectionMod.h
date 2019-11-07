#ifdef  _WINDOWS_SOURCE
#ifdef  __TestProjectionMod
#define ExportedByTestProjectionMod     __declspec(dllexport)
#else
#define ExportedByTestProjectionMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestProjectionMod
#endif
