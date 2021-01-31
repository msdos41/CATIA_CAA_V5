#ifdef  _WINDOWS_SOURCE
#ifdef  __TestPictureMod
#define ExportedByTestPictureMod     __declspec(dllexport)
#else
#define ExportedByTestPictureMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestPictureMod
#endif
