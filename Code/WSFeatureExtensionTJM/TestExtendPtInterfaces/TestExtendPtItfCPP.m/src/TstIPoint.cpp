#include "TstIPoint.h"

#ifndef LOCAL_DEFINITION_FOR_IID
IID IID_TstIPoint = { 0xba543e09, 0x6b80, 0x41a8, { 0x80, 0x13, 0xa9, 0xca, 0x6d, 0x82, 0xb1, 0x46} };
#endif

CATImplementInterface(TstIPoint, CATBaseUnknown);
CATImplementHandler(TstIPoint,CATBaseUnknown);
