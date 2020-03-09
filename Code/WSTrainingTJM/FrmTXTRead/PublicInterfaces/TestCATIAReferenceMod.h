#ifdef  _WINDOWS_SOURCE
#ifdef  __TestCATIAReferenceMod
#define ExportedByTestCATIAReferenceMod     __declspec(dllexport)
#else
#define ExportedByTestCATIAReferenceMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestCATIAReferenceMod
#endif
