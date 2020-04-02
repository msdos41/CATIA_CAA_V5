#ifdef  _WINDOWS_SOURCE
#ifdef  __TestTessellationMod
#define ExportedByTestTessellationMod     __declspec(dllexport)
#else
#define ExportedByTestTessellationMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestTessellationMod
#endif
