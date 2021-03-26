#ifdef  _WINDOWS_SOURCE
#ifdef  __TestM
#define ExportedByTestM     __declspec(dllexport)
#else
#define ExportedByTestM     __declspec(dllimport)
#endif
#else
#define ExportedByTestM
#endif
