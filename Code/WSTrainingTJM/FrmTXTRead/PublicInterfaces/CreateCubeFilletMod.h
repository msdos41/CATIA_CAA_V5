#ifdef  _WINDOWS_SOURCE
#ifdef  __CreateCubeFilletMod
#define ExportedByCreateCubeFilletMod     __declspec(dllexport)
#else
#define ExportedByCreateCubeFilletMod     __declspec(dllimport)
#endif
#else
#define ExportedByCreateCubeFilletMod
#endif
