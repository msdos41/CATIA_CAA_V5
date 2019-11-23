#ifdef  _WINDOWS_SOURCE
#ifdef  __TestMultiListMod
#define ExportedByTestMultiListMod     __declspec(dllexport)
#else
#define ExportedByTestMultiListMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestMultiListMod
#endif
