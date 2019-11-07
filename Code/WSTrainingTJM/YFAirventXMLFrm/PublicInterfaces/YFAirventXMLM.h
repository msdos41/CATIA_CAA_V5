#ifdef  _WINDOWS_SOURCE
#ifdef  __YFAirventXMLM
#define ExportedByYFAirventXMLM     __declspec(dllexport)
#else
#define ExportedByYFAirventXMLM     __declspec(dllimport)
#endif
#else
#define ExportedByYFAirventXMLM
#endif
