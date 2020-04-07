#ifdef  _WINDOWS_SOURCE
#ifdef  __TestInterfaceMod
#define ExportedByTestInterfaceMod     __declspec(dllexport)
#else
#define ExportedByTestInterfaceMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestInterfaceMod
#endif
