#ifdef  _WINDOWS_SOURCE
#ifdef  __TestMechanismMod
#define ExportedByTestMechanismMod     __declspec(dllexport)
#else
#define ExportedByTestMechanismMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestMechanismMod
#endif
