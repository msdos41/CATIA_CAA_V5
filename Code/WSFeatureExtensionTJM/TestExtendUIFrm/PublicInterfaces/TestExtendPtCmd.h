// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestExtendPtCmd.h
// The state chart based command: TestExtendPtCmd
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
//  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestExtendPtCmd_H
#define TestExtendPtCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

#include "TstIPoint.h"
#include "TstIFactory.h"
#include "TestExtendPtDlg.h"

#include "CATIProduct.h"
#include "CATIGSMProceduralView.h"
#include "CATILinkableObject.h"
#include "CATIContainerOfDocument.h"
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"
#include "CATIPartRequest.h"
#include "CATDocument.h"
#include "CATIMechanicalRootFactory.h"
#include "CATIAlias.h"
#include "CATFrmEditor.h"
#include "CATIDocRoots.h"
#include "CATInit.h"

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
class TestExtendPtCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestExtendPtCmd, CATStateCommand )

  public:

  //TestExtendPtCmd();
  TestExtendPtCmd(TstIPoint *ipiTstIPoint);	//���Ĺ��캯����Ĭ��ָ��գ��������ǿ�ʱ��˵���Ǵ������ǿ�ʱ˵���Ǹ��ġ��������ʱ�����Ҫ
  virtual ~TestExtendPtCmd();

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
  HRESULT CreatePoint();
  HRESULT EditPoint();
  HRESULT CreateNewGeoSet(CATIProduct_var ispiProd,CATUnicodeString istrName,CATISpecObject_var &ospiSpecGeoSet);
  HRESULT GetRootProduct( CATIProduct_var &ospiRootProduct );
  TstIFactory *GetTstFactory(CATIProduct_var ispiProd);
private:

	  TestExtendPtDlg			*_pDlg;

	  TstIPoint					*_pTstIPoint;

};

//----------------------------------------------------------------------

#endif