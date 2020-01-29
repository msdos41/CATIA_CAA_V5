#ifdef  _WINDOWS_SOURCE
#ifdef  __TestProgressBarMod
#define ExportedByTestProgressBarMod     __declspec(dllexport)
#else
#define ExportedByTestProgressBarMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestProgressBarMod
#endif
