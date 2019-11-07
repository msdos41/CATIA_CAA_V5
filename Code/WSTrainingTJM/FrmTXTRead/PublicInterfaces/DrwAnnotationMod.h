#ifdef  _WINDOWS_SOURCE
#ifdef  __DrwAnnotationMod
#define ExportedByDrwAnnotationMod     __declspec(dllexport)
#else
#define ExportedByDrwAnnotationMod     __declspec(dllimport)
#endif
#else
#define ExportedByDrwAnnotationMod
#endif
