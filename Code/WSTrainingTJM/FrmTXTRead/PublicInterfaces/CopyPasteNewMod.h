#ifdef  _WINDOWS_SOURCE
#ifdef  __CopyPasteNewMod
#define ExportedByCopyPasteNewMod     __declspec(dllexport)
#else
#define ExportedByCopyPasteNewMod     __declspec(dllimport)
#endif
#else
#define ExportedByCopyPasteNewMod
#endif
