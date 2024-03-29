// COPYRIGHT Dassault Systemes 2018
//===================================================================
//
// RPSCreationCmd.h
// The state chart based command: RPSCreationCmd
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
//  Dec 2018  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef RPSCreationCmd_H
#define RPSCreationCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

#include "RPSCreationDlg.h"

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

#include "CATListOfCATUnicodeString.h"

#include "CATListPtrCATIProduct.h"

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
class RPSCreationCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( RPSCreationCmd, CATStateCommand )

  public:

  RPSCreationCmd();
  virtual ~RPSCreationCmd();

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

  void ExitCmd();

  void ShowRPSList();

  HRESULT GetRootProduct(CATIProduct *&opiRootProduct);

  //void GetAllSubParts(CATIProduct *ipiRootProduct, CATListValCATUnicodeString &lstPartNumber);

  void GetAllSubParts(CATIProduct *ipiRootProduct, CATListPtrCATIProduct *&lstSubParts);

  CATBoolean IsProduct(CATIProduct_var ispiPrd);

  private:

  CATIndicationAgent	* _Indication;

  RPSCreationDlg * _pDlg;


};

//----------------------------------------------------------------------

#endif
