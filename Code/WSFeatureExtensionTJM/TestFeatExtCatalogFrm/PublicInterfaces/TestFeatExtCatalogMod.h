#ifdef  _WINDOWS_SOURCE
#ifdef  __TestFeatExtCatalogMod
#define ExportedByTestFeatExtCatalogMod     __declspec(dllexport)
#else
#define ExportedByTestFeatExtCatalogMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestFeatExtCatalogMod
#endif
