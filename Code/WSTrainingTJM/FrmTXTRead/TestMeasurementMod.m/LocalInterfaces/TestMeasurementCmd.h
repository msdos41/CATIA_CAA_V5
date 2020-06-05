// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestMeasurementCmd.h
// The state chart based command: TestMeasurementCmd
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
//  May 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestMeasurementCmd_H
#define TestMeasurementCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

#include "TestMeasurementDlg.h"
#include "GeneralClass.h"

#include "CATIMeasurableInContext.h"

#include "CATIClashFactory.h"
#include "CATIClashResult.h"
#include "CATIClash.h"
#include "CATIConflict.h"

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
class TestMeasurementCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestMeasurementCmd, CATStateCommand )

  public:

  TestMeasurementCmd();
  virtual ~TestMeasurementCmd();

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
  CATBoolean ActionExit(void * data);
  void selectObjAFunc(void * data);
  void selectObjBFunc(void * data);
  CATBoolean ActionOK(void * data);
  void TransToSelectA(void * data);
  void TransToSelectB(void * data);
  HRESULT GetMinDistanceByMeasure(CATISpecObject_var ispiSpec1,CATIProduct_var ispiProd1,CATISpecObject_var ispiSpec2,CATIProduct_var ispiProd2,CATMathPoint &omathPt1,CATMathPoint &omathPt2,double &oDistance);
  CATMathTransformation GetMatrixTransformation( CATISpecObject_var spSpecOne, CATISpecObject_var spSpecTwo );
  CATMathTransformation GetAbsTransformation( CATISpecObject_var ispSpecOne );
  HRESULT CheckClash(CATIProduct_var ispiPrd1,CATIProduct_var ispiPrd2);
  CATBoolean ActionOK2(void * data);
private:

	  TestMeasurementDlg		*_pDlg;

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

	  CATIProduct_var		_spiProdSelB;

};

//----------------------------------------------------------------------

#endif
