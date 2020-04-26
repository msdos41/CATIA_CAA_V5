#ifdef  _WINDOWS_SOURCE
#ifdef  __TestTreeViewMod
#define ExportedByTestTreeViewMod     __declspec(dllexport)
#else
#define ExportedByTestTreeViewMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestTreeViewMod
#endif
