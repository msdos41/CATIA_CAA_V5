#ifdef  _WINDOWS_SOURCE
#ifdef  __RPSInsertMod
#define ExportedByRPSInsertMod     __declspec(dllexport)
#else
#define ExportedByRPSInsertMod     __declspec(dllimport)
#endif
#else
#define ExportedByRPSInsertMod
#endif
