#ifdef  _WINDOWS_SOURCE
#ifdef  __TrainingXMLM
#define ExportedByTrainingXMLM     __declspec(dllexport)
#else
#define ExportedByTrainingXMLM     __declspec(dllimport)
#endif
#else
#define ExportedByTrainingXMLM
#endif
