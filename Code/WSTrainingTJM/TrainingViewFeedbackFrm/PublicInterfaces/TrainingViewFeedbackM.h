#ifdef  _WINDOWS_SOURCE
#ifdef  __TrainingViewFeedbackM
#define ExportedByTrainingViewFeedbackM     __declspec(dllexport)
#else
#define ExportedByTrainingViewFeedbackM     __declspec(dllimport)
#endif
#else
#define ExportedByTrainingViewFeedbackM
#endif
