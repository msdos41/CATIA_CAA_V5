#ifdef  _WINDOWS_SOURCE
#ifdef  __TestBatchCreatePointMod
#define ExportedByTestBatchCreatePointMod     __declspec(dllexport)
#else
#define ExportedByTestBatchCreatePointMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestBatchCreatePointMod
#endif
