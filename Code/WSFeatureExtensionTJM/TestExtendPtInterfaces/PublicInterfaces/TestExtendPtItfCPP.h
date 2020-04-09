#ifdef  _WINDOWS_SOURCE
#ifdef  __TestExtendPtItfCPP
#define ExportedByTestExtendPtItfCPP     __declspec(dllexport)
#else
#define ExportedByTestExtendPtItfCPP     __declspec(dllimport)
#endif
#else
#define ExportedByTestExtendPtItfCPP
#endif
