#ifdef  _WINDOWS_SOURCE
#ifdef  __TestCrossDocMod
#define ExportedByTestCrossDocMod     __declspec(dllexport)
#else
#define ExportedByTestCrossDocMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestCrossDocMod
#endif
