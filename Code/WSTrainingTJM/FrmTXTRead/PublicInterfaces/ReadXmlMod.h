#ifdef  _WINDOWS_SOURCE
#ifdef  __ReadXmlMod
#define ExportedByReadXmlMod     __declspec(dllexport)
#else
#define ExportedByReadXmlMod     __declspec(dllimport)
#endif
#else
#define ExportedByReadXmlMod
#endif
