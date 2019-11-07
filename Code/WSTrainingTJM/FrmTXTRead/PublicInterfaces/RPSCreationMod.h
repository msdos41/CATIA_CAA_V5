#ifdef  _WINDOWS_SOURCE
#ifdef  __RPSCreationMod
#define ExportedByRPSCreationMod     __declspec(dllexport)
#else
#define ExportedByRPSCreationMod     __declspec(dllimport)
#endif
#else
#define ExportedByRPSCreationMod
#endif
