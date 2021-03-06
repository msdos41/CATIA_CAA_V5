// COPYRIGHT Dassault Systemes 2021
//===================================================================
//
// TestSoftAssembleCmd.h
// The state chart based command: TestSoftAssembleCmd
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
//  Apr 2021  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestSoftAssembleCmd_H
#define TestSoftAssembleCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

#include "TestSoftAssembleDlg.h"
#include "GeneralClass.h"

#include "CATIBlockMovable.h"

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
class TestSoftAssembleCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestSoftAssembleCmd, CATStateCommand )

  public:

  TestSoftAssembleCmd();
  virtual ~TestSoftAssembleCmd();

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
  CATBoolean ExitCmd(void * data);
  CATBoolean ActionOK(void * data);
  CATBoolean CheckSelectedProduct(void * data);
  void selectProductFunc(void * data);
  void TransToProductSel(void * data);
  void SetProductPosition(CATIProduct_var ispiProd,CATIProduct_var ispiProdContext,CATMathTransformation iTrans);
  void InitialDlg();
private:

	  TestSoftAssembleDlg				*_pDlg;

	  CATHSO							* _pHSO;

	  CATFrmEditor						* _pEditor;

	  CATIProduct_var					_spiProdRoot;

	  CATPathElementAgent				*_pProductAgent;

	  CATDialogAgent					*_pProductFieldAgent;

	  CATIProduct_var					_spiProdSel;

	  CATBaseUnknown_var				_spBUSel;

	  int								_intSelType;

	  GeneralClass						*_pGeneralCls;

};

//----------------------------------------------------------------------

#endif
