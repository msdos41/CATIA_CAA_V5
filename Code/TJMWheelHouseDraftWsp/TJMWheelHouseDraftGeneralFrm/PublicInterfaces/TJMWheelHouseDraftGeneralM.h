#ifdef  _WINDOWS_SOURCE
#ifdef  __TJMWheelHouseDraftGeneralM
#define ExportedByTJMWheelHouseDraftGeneralM     __declspec(dllexport)
#else
#define ExportedByTJMWheelHouseDraftGeneralM     __declspec(dllimport)
#endif
#else
#define ExportedByTJMWheelHouseDraftGeneralM
#endif
