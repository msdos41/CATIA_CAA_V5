#ifdef  _WINDOWS_SOURCE
#ifdef  __TrainingTempM
#define ExportedByTrainingTempM     __declspec(dllexport)
#else
#define ExportedByTrainingTempM     __declspec(dllimport)
#endif
#else
#define ExportedByTrainingTempM
#endif
