#ifdef  _WINDOWS_SOURCE
#ifdef  __GridView2DMod
#define ExportedByGridView2DMod     __declspec(dllexport)
#else
#define ExportedByGridView2DMod     __declspec(dllimport)
#endif
#else
#define ExportedByGridView2DMod
#endif
