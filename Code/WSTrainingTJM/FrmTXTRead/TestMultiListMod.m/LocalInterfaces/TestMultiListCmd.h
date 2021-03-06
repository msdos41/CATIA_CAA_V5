// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestMultiListCmd.h
// The state chart based command: TestMultiListCmd
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
//  Nov 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestMultiListCmd_H
#define TestMultiListCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "GeneralClass.h"
#include "TestMultiListDlg.h"

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
class TestMultiListCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestMultiListCmd, CATStateCommand )

  public:

  TestMultiListCmd();
  virtual ~TestMultiListCmd();

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
  CATBoolean DecideSurfaceSelect();
  CATBoolean DecideCurveSelect();
  void ActionSelectSurface();
  void ActionSelectCurve();
  void TransToCurve();
  void TransToSurface();
  CATBoolean ActionShowMoreUI(void * data);
private:

	  TestMultiListDlg		*_pDlg;

	  GeneralClass			*_pGeneralCls;

	  CATHSO				* _pHSO;

	  CATFrmEditor			* _pEditor;

	  CATFeatureImportAgent	*_pSurfaceAgent;

	  CATDialogAgent		*_pSurfaceFieldAgent;

	  CATFeatureImportAgent	*_pCurveAgent;

	  CATDialogAgent		*_pCurveFieldAgent;

	  CATLISTV(CATBaseUnknown_var)		_lstBUSurface;

	  CATLISTV(CATBaseUnknown_var)		_lstBUCurve;

	  CATListOfCATUnicodeString			_lstAliasSurface;

	  CATListOfCATUnicodeString			_lstAliasCurve;

};

//----------------------------------------------------------------------

#endif
