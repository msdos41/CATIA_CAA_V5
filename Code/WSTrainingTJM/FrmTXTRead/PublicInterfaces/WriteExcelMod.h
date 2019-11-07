#ifdef  _WINDOWS_SOURCE
#ifdef  __WriteExcelMod
#define ExportedByWriteExcelMod     __declspec(dllexport)
#else
#define ExportedByWriteExcelMod     __declspec(dllimport)
#endif
#else
#define ExportedByWriteExcelMod
#endif
