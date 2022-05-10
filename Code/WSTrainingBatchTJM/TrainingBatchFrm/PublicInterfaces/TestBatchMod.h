#ifdef  _WINDOWS_SOURCE
#ifdef  __TestBatchMod
#define ExportedByTestBatchMod     __declspec(dllexport)
#else
#define ExportedByTestBatchMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestBatchMod
#endif
