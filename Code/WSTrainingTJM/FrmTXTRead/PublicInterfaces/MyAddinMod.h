#ifdef  _WINDOWS_SOURCE
#ifdef  __MyAddinMod
#define ExportedByMyAddinMod     __declspec(dllexport)
#else
#define ExportedByMyAddinMod     __declspec(dllimport)
#endif
#else
#define ExportedByMyAddinMod
#endif
