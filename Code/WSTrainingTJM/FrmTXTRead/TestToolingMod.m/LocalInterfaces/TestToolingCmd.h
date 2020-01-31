// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestToolingCmd.h
// The state chart based command: TestToolingCmd
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
//  Jan 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestToolingCmd_H
#define TestToolingCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "TestToolingDlg.h"
#include "GeneralClass.h"

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
class TestToolingCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestToolingCmd, CATStateCommand )

  public:

  TestToolingCmd();
  virtual ~TestToolingCmd();

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
  void selectCurveFunc(void * data);
  void selectSurfaceFunc(void * data);
  void TransToSelectA(void * data);
  void TransToSelectB(void * data);
  CATBoolean ActionExit(void * data);
  CATBoolean ActionOK(void * data);
private:

	  TestToolingDlg		*_pDlg;

	  CATFrmEditor			*_pEditor;

	  CATHSO				*_pHSO;

	  GeneralClass			*_pGeneralCls;

	  CATFeatureImportAgent * _pSelAAgent;

	  CATFeatureImportAgent * _pSelBAgent;

	  CATDialogAgent		* _pSelAFieldAgent;

	  CATDialogAgent		* _pSelBFieldAgent;

	  CATBaseUnknown_var	_spBUSelectA;

	  CATBaseUnknown_var	_spBUSelectB;

	  CATIProduct_var		_spiProdSelA;

};

//----------------------------------------------------------------------

#endif
