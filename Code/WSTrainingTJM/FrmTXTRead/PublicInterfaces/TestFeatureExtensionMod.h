#ifdef  _WINDOWS_SOURCE
#ifdef  __TestFeatureExtensionMod
#define ExportedByTestFeatureExtensionMod     __declspec(dllexport)
#else
#define ExportedByTestFeatureExtensionMod     __declspec(dllimport)
#endif
#else
#define ExportedByTestFeatureExtensionMod
#endif
