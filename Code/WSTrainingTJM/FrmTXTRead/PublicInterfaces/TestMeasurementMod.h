#ifdef  _WINDOWS_SOURCE
#ifdef  __TestMeasurementMod
#define ExportedByTestMeasurementMod     __declspec(dllexport)
#else
#define ExportedByTestMeasurementMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestMeasurementMod
#endif
