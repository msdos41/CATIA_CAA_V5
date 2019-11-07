#ifdef  _WINDOWS_SOURCE
#ifdef  __CopyPastMod
#define ExportedByCopyPastMod     __declspec(dllexport)
#else
#define ExportedByCopyPastMod     __declspec(dllimport)
#endif
#else
#define ExportedByCopyPastMod
#endif
