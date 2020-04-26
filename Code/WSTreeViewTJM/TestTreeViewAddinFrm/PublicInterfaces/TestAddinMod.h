#ifdef  _WINDOWS_SOURCE
#ifdef  __TestAddinMod
#define ExportedByTestAddinMod     __declspec(dllexport)
#else
#define ExportedByTestAddinMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestAddinMod
#endif
