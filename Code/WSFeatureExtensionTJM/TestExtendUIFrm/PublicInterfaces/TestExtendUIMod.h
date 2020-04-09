#ifdef  _WINDOWS_SOURCE
#ifdef  __TestExtendUIMod
#define ExportedByTestExtendUIMod     __declspec(dllexport)
#else
#define ExportedByTestExtendUIMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestExtendUIMod
#endif
