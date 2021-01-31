#ifdef  _WINDOWS_SOURCE
#ifdef  __TJMWheelHouseDraftAddinM
#define ExportedByTJMWheelHouseDraftAddinM     __declspec(dllexport)
#else
#define ExportedByTJMWheelHouseDraftAddinM     __declspec(dllimport)
#endif
#else
#define ExportedByTJMWheelHouseDraftAddinM
#endif
