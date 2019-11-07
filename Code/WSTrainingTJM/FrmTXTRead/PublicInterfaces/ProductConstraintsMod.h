#ifdef  _WINDOWS_SOURCE
#ifdef  __ProductConstraintsMod
#define ExportedByProductConstraintsMod     __declspec(dllexport)
#else
#define ExportedByProductConstraintsMod     __declspec(dllimport)
#endif
#else
#define ExportedByProductConstraintsMod
#endif
