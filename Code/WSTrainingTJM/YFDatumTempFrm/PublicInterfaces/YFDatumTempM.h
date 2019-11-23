#ifdef  _WINDOWS_SOURCE
#ifdef  __YFDatumTempM
#define ExportedByYFDatumTempM     __declspec(dllexport)
#else
#define ExportedByYFDatumTempM     __declspec(dllimport)
#endif
#else
#define ExportedByYFDatumTempM
#endif
