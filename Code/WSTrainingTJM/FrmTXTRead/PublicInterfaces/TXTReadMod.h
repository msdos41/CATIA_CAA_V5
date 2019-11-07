#ifdef  _WINDOWS_SOURCE
#ifdef  __TXTReadMod
#define ExportedByTXTReadMod     __declspec(dllexport)
#else
#define ExportedByTXTReadMod     __declspec(dllimport)
#endif
#else
#define ExportedByTXTReadMod
#endif
