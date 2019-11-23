#include "DumITempPoint.h"

#ifndef LOCAL_DEFINITION_FOR_IID
IID IID_DumITempPoint = { 0x63316325, 0x0b33, 0x4a4c, { 0x90, 0xa5, 0x79, 0x19, 0xd2, 0x7e, 0x25, 0x36} };
#endif

CATImplementInterface(DumITempPoint, CATBaseUnknown);
CATImplementHandler(DumITempPoint, CATBaseUnknown);