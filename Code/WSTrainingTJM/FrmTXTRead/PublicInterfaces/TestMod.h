#ifdef  _WINDOWS_SOURCE
#ifdef  __TestMod
#define ExportedByTestMod     __declspec(dllexport)
#else
#define ExportedByTestMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestMod
#endif
