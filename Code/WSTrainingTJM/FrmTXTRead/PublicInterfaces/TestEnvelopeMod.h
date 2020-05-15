#ifdef  _WINDOWS_SOURCE
#ifdef  __TestEnvelopeMod
#define ExportedByTestEnvelopeMod     __declspec(dllexport)
#else
#define ExportedByTestEnvelopeMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestEnvelopeMod
#endif
