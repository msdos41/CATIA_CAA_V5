// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestUserDefinedMathBoxCmd.h
// The state chart based command: TestUserDefinedMathBoxCmd
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
//  Aug 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestUserDefinedMathBoxCmd_H
#define TestUserDefinedMathBoxCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "GeneralClass.h"
#include "CAACommonModule.h"

#include "CATI2DAxis.h"

class CATIndicationAgent;

//----------------------------------------------------------------------

struct UserDefinedCircle 
{
	CATMathPoint2D ptCenter;
	double dRadius;
};

/**
 * Describe your command here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog engine framework.
 * (consult base class description).
 */
class TestUserDefinedMathBoxCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestUserDefinedMathBoxCmd, CATStateCommand )

  public:

  TestUserDefinedMathBoxCmd();
  virtual ~TestUserDefinedMathBoxCmd();

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

  void GetPlaneFromScreen();
  CATBoolean AddHSO(CATBaseUnknown_var ispSpecSelect);
  HRESULT GetAllPointsFromView(CATIView_var ispiView,vector<CATMathPoint2D> &ovecPt);
  HRESULT GetAllPointsFromView(CATIView_var ispiView,CATMathPoint2D iPtLL,CATMathPoint2D iPtRH,vector<CATMathPoint2D> &ovecPt);
  CATBoolean IsOccurInList(CATMathPoint2D iPt2D,vector<CATMathPoint2D> ivecPt2D);
  HRESULT GetMinOuterCircle(vector<CATMathPoint2D> ivecPt2D,UserDefinedCircle &oOuterCircle);
  HRESULT MinOuterCircleWithOnePoint(vector<CATMathPoint2D> ivecPt2D,CATMathPoint2D iPt,UserDefinedCircle &oOuterCircle);
  HRESULT MinOuterCircleWithTwoPoints(vector<CATMathPoint2D> ivecPt2D,CATMathPoint2D iPt1,CATMathPoint2D iPt2,UserDefinedCircle &oOuterCircle);
  CATBoolean IsIncludedInCircle(CATMathPoint2D iPt,UserDefinedCircle iCircle);
  void GetCenterAndRadius(CATMathPoint iPTA,CATMathPoint iPTB,CATMathPoint iPTC,CATMathPoint &oPT,double &oRadius);
  CATBoolean IsPointInsideBox(CATMathPoint2D iPtLL,CATMathPoint2D iPtRH,CATMathPoint2D iPt);
  void GetPointsInsideBox(CATMathPoint2D iPtLL,CATMathPoint2D iPtRH,vector<CATMathPoint2D> &iovecPtFiltered);
  HRESULT GetConvexHull(vector<CATMathPoint2D> ivecPt2D, vector<CATMathPoint2D> &ovecPtConvexHull);
  CATBoolean IsOnRightSide(CATMathPoint2D iPtBase,CATMathPoint2D iPtJudge1,CATMathPoint2D iPtJudge2);
  void SetLineFormat(CATISpecObject_var ispiSpecLine);
private:

  CATIndicationAgent	* _Indication;

  GeneralClass			* _pGeneralCls;
};

//----------------------------------------------------------------------

#endif
