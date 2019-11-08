// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// UpdateDataBaseCmd.h
// The state chart based command: UpdateDataBaseCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   STATECOMMAND
//End CAA2 Wizard Generation Report
//
//  Jan 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef UpdateDataBaseCmd_H
#define UpdateDataBaseCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

#include "UpdateDataBaseDlg.h"

#include "iostream.h"

#include "CATFrmEditor.h"
#include "CATDocument.h"
#include "CATIDocRoots.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATIProduct.h"
#include "CATIDocId.h"

#include "CATIContainerOfDocument.h"
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"
#include "CATIDescendants.h"
#include "CATIPartRequest.h"

#include "CATListOfCATUnicodeString.h"

#include "CATListPtrCATIProduct.h"

#include "CATBody.h"
#include "CATGeometry.h"
#include "CATIBodyRequest.h"
#include "CATIGeometricalElement.h"
#include "CATPoint.h"
#include "CATCell.h"
#include "CATGetEnvValue.h"

#include "ClsOfExcelOperation.h"

#include "CATPoint.h"

class CATIndicationAgent;

//----------------------------------------------------------------------

/**
 * Describe your command here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog engine framework.
 * (consult base class description).
 */
class UpdateDataBaseCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( UpdateDataBaseCmd, CATStateCommand )

  public:

  UpdateDataBaseCmd();
  virtual ~UpdateDataBaseCmd();

    /**
     * Defines the command automata.
     * <br>
     * <i>(states, transitions and agents)</i>
     */
  virtual void     BuildGraph();

    /**
     * Action associated to state transitions.
     */
  virtual CATBoolean  ActionOne(void * data);

  void ExitCmd(void * data);

  void RefreshPartList(void * data);

  //HRESULT FilterPartList(CATLISTP(CATIProduct) &olstSubParts, CATUnicodeString istrKeyWord);
  //HRESULT FilterPartList(CATLISTP(CATIProduct) &olstSubParts, CATLISTV(CATBaseUnknown_var) &olstRPSGeomSet,CATUnicodeString istrKeyWord);
  HRESULT FilterPartList(CATUnicodeString istrKeyWord, CATLISTP(CATIProduct) &olstSubParts);

  HRESULT GetRootProduct(CATIProduct *&opiRootProduct);

  CATBoolean IsProduct(CATIProduct_var ispiPrd);

  //HRESULT GetRPSCoord(CATBaseUnknown_var ispRPSGeomSet, CATListValCATUnicodeString &lstRPSName, CATListValCATUnicodeString &lstXCoord, CATListValCATUnicodeString &lstYCoord, CATListValCATUnicodeString &lstZCoord);
  HRESULT GetRPSCoord(CATIProduct_var ispProduct, CATUnicodeString istrGSName, CATListValCATUnicodeString &lstRPSName, CATListValCATUnicodeString &lstXCoord, CATListValCATUnicodeString &lstYCoord, CATListValCATUnicodeString &lstZCoord);

  void ChangeStatus(void * data);

  HRESULT GetPartListFromMultiList(CATLISTP(CATIProduct) ilstProduct,CATLISTP(CATIProduct) &olstProductSelected);

  void WriteExcel(void * data);

  HRESULT GetResourseFile(CATUnicodeString &CATEnvPath,CATUnicodeString FileFullName,CATUnicodeString folderName);

  private:

  CATIndicationAgent	* _Indication;

  UpdateDataBaseDlg * _pDlg;

  CATLISTP(CATIProduct) _lstSubParts;

  CATUnicodeString _strDBPath;
};

//----------------------------------------------------------------------

#endif
