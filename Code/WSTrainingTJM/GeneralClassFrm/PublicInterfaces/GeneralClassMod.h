#ifdef  _WINDOWS_SOURCE
#ifdef  __GeneralClassMod
#define ExportedByGeneralClassMod     __declspec(dllexport)
#else
#define ExportedByGeneralClassMod     __declspec(dllimport)
#endif
#else
#define ExportedByGeneralClassMod
#endif
