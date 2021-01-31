#ifdef  _WINDOWS_SOURCE
#ifdef  __TJMWheelHouseDraftUIM
#define ExportedByTJMWheelHouseDraftUIM     __declspec(dllexport)
#else
#define ExportedByTJMWheelHouseDraftUIM     __declspec(dllimport)
#endif
#else
#define ExportedByTJMWheelHouseDraftUIM
#endif
