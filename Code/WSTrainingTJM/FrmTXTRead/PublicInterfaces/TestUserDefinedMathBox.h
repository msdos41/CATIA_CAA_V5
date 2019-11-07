#ifdef  _WINDOWS_SOURCE
#ifdef  __TestUserDefinedMathBox
#define ExportedByTestUserDefinedMathBox     __declspec(dllexport)
#else
#define ExportedByTestUserDefinedMathBox     __declspec(dllimport)
#endif
#else
#define ExportedByTestUserDefinedMathBox
#endif
