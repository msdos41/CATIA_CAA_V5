// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestProgressBarDlg.h
// The dialog : TestProgressBarDlg
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
#ifndef TestProgressBarDlg_H
#define TestProgressBarDlg_H

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
class TestProgressBarDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestProgressBarDlg, CATDlgDialog )

  public:

  TestProgressBarDlg();
  virtual ~TestProgressBarDlg();

  void Build ();
  CATDlgProgress *GetProgressBar();

  protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgProgress*      _Progress001;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
