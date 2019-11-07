// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestDlg.h
// The dialog : TestDlg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   DIALOG
//End CAA2 Wizard Generation Report
//
//  Jan 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestDlg_H
#define TestDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"

//----------------------------------------------------------------------

/**
 * Describe the purpose of your panel here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog framework.
 * (consult base class description).
 */
class TestDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestDlg, CATDlgDialog )

  public:

  TestDlg();
  virtual ~TestDlg();

  void Build ();

  CATDlgSelectorList* GetSelectListLine();
  CATDlgPushButton* GetPushButtonCOUT();
  CATDlgSelectorList* GetSelectListFace();
  CATDlgPushButton* GetPushButtonMidPtOnSurf();
  CATDlgPushButton* GetPushButtonProjection();
  CATDlgPushButton* GetPushButtonStartOtherCmd();
  CATDlgPushButton* GetPushButtonCompassTest();
  CATDlgPushButton* GetPushButtonReadTxt();
  CATDlgPushButton* GetPushButton3DView();
protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgLabel*      _LabelLine;
 CATDlgContainer*      _Container002;
 CATDlgSelectorList*      _SelectorListLine;
 CATDlgContainer*      _Container003;
 CATDlgPushButton*      _PushButtonCOUT;
 CATDlgContainer*      _Container004;
 CATDlgLabel*      _LabelAxis;
 CATDlgSelectorList*      _SelectorListFace;
 CATDlgPushButton*      _PushButtonMidPtOnSurf;
 CATDlgPushButton*      _PushButtonProjection;
 CATDlgPushButton*      _PushButtonStartOtherCmd;
 CATDlgPushButton*      _PushButtonCompass;
 CATDlgPushButton*      _PushButtonReadTxt;
 CATDlgPushButton*      _PushButton3DView;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
