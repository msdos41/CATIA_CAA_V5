#include "DumITempFace.h"

#ifndef LOCAL_DEFINITION_FOR_IID
IID IID_DumITempFace = { 0xf2d7cba2, 0x70b4, 0x45fc, { 0x9d, 0x10, 0x8a, 0xd1, 0x04, 0x14, 0xe1, 0x34} };
#endif

CATImplementInterface(DumITempFace, CATBaseUnknown);
CATImplementHandler(DumITempFace, CATBaseUnknown);
