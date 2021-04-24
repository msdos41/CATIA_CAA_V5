#ifdef  _WINDOWS_SOURCE
#ifdef  __TestSoftAssembleMod
#define ExportedByTestSoftAssembleMod     __declspec(dllexport)
#else
#define ExportedByTestSoftAssembleMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestSoftAssembleMod
#endif
