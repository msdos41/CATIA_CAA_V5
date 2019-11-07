#ifdef  _WINDOWS_SOURCE
#ifdef  __ModPubExcel
#define ExportedByModPubExcel     __declspec(dllexport)
#else
#define ExportedByModPubExcel     __declspec(dllimport)
#endif
#else
#define ExportedByModPubExcel
#endif
