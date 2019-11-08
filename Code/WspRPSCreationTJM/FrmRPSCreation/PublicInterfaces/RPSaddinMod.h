#ifdef  _WINDOWS_SOURCE
#ifdef  __RPSaddinMod
#define ExportedByRPSaddinMod     __declspec(dllexport)
#else
#define ExportedByRPSaddinMod     __declspec(dllimport)
#endif
#else
#define ExportedByRPSaddinMod
#endif
