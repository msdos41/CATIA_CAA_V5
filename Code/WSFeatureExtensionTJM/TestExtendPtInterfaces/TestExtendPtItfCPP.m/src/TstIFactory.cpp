#include "TstIFactory.h"

#ifndef LOCAL_DEFINITION_FOR_IID
IID IID_TstIFactory = { 0x61d376a9, 0x599b, 0x445c, { 0x82, 0x66, 0xfe, 0xa8, 0xe3, 0x28, 0xdc, 0x4d} };
#endif

CATImplementInterface(TstIFactory, CATBaseUnknown);
CATImplementHandler(TstIFactory,CATBaseUnknown);
