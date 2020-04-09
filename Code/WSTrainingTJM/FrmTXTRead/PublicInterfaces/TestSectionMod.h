#ifdef  _WINDOWS_SOURCE
#ifdef  __TestSectionMod
#define ExportedByTestSectionMod     __declspec(dllexport)
#else
#define ExportedByTestSectionMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestSectionMod
#endif
