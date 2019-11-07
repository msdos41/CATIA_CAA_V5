#ifdef  _WINDOWS_SOURCE
#ifdef  __TestDrwDimensionMod
#define ExportedByTestDrwDimensionMod     __declspec(dllexport)
#else
#define ExportedByTestDrwDimensionMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestDrwDimensionMod
#endif
