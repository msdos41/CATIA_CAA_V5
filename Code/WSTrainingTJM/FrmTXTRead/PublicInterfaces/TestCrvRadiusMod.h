#ifdef  _WINDOWS_SOURCE
#ifdef  __TestCrvRadiusMod
#define ExportedByTestCrvRadiusMod     __declspec(dllexport)
#else
#define ExportedByTestCrvRadiusMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestCrvRadiusMod
#endif
