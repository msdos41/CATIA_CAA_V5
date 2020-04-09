#ifdef  _WINDOWS_SOURCE
#ifdef  __TestExtentPtImplMod
#define ExportedByTestExtentPtImplMod     __declspec(dllexport)
#else
#define ExportedByTestExtentPtImplMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestExtentPtImplMod
#endif
