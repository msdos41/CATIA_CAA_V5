#ifdef  _WINDOWS_SOURCE
#ifdef  __DrwSetColorMod
#define ExportedByDrwSetColorMod     __declspec(dllexport)
#else
#define ExportedByDrwSetColorMod     __declspec(dllimport)
#endif
#else
#define ExportedByDrwSetColorMod
#endif
