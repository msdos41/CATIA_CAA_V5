#ifdef  _WINDOWS_SOURCE
#ifdef  __GeneralClsM
#define ExportedByGeneralClsM     __declspec(dllexport)
#else
#define ExportedByGeneralClsM     __declspec(dllimport)
#endif
#else
#define ExportedByGeneralClsM
#endif
