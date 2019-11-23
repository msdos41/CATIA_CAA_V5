#ifdef  _WINDOWS_SOURCE
#ifdef  __YFAirventViewFeedbackM
#define ExportedByYFAirventViewFeedbackM     __declspec(dllexport)
#else
#define ExportedByYFAirventViewFeedbackM     __declspec(dllimport)
#endif
#else
#define ExportedByYFAirventViewFeedbackM
#endif
