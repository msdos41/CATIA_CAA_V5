#ifdef  _WINDOWS_SOURCE
#ifdef  __CreatePadMod
#define ExportedByCreatePadMod     __declspec(dllexport)
#else
#define ExportedByCreatePadMod     __declspec(dllimport)
#endif
#else
#define ExportedByCreatePadMod
#endif
