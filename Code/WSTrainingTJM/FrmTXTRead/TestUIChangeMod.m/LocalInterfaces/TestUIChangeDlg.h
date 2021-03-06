// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestUIChangeDlg.h
// The dialog : TestUIChangeDlg
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
//  Jan 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestUIChangeDlg_H
#define TestUIChangeDlg_H

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
class TestUIChangeDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestUIChangeDlg, CATDlgDialog )

  public:

  TestUIChangeDlg();
  virtual ~TestUIChangeDlg();

  void Build ();
  void OnPushButtonMorePushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);
  void CloseWindow(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);
  protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
//END CAA2 WIZARD WIDGET DECLARATION SECTION

	  CATBoolean             _IsMoreWindowOpen;
	  CATDlgFrame     *      _pFrameRightMore;
	  CATUnicodeString       _MoreMsg ;
	  CATUnicodeString       _LessMsg ;
};

//----------------------------------------------------------------------

#endif
