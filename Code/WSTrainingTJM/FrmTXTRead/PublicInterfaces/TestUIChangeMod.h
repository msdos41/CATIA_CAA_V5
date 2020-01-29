#ifdef  _WINDOWS_SOURCE
#ifdef  __TestUIChangeMod
#define ExportedByTestUIChangeMod     __declspec(dllexport)
#else
#define ExportedByTestUIChangeMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestUIChangeMod
#endif
