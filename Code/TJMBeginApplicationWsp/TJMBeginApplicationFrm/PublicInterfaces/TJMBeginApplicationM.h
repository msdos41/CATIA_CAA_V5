#ifdef  _WINDOWS_SOURCE
#ifdef  __TJMBeginApplicationM
#define ExportedByTJMBeginApplicationM     __declspec(dllexport)
#else
#define ExportedByTJMBeginApplicationM     __declspec(dllimport)
#endif
#else
#define ExportedByTJMBeginApplicationM
#endif
