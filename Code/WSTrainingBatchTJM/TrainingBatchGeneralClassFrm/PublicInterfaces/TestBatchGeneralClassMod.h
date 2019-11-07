#ifdef  _WINDOWS_SOURCE
#ifdef  __TestBatchGeneralClassMod
#define ExportedByTestBatchGeneralClassMod     __declspec(dllexport)
#else
#define ExportedByTestBatchGeneralClassMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestBatchGeneralClassMod
#endif
