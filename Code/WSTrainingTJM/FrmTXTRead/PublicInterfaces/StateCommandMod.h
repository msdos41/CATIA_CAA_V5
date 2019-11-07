#ifdef  _WINDOWS_SOURCE
#ifdef  __StateCommandMod
#define ExportedByStateCommandMod     __declspec(dllexport)
#else
#define ExportedByStateCommandMod     __declspec(dllimport)
#endif
#else
#define ExportedByStateCommandMod
#endif
