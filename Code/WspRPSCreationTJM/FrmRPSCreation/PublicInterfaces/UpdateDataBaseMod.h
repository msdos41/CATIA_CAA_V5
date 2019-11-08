#ifdef  _WINDOWS_SOURCE
#ifdef  __UpdateDataBaseMod
#define ExportedByUpdateDataBaseMod     __declspec(dllexport)
#else
#define ExportedByUpdateDataBaseMod     __declspec(dllimport)
#endif
#else
#define ExportedByUpdateDataBaseMod
#endif
