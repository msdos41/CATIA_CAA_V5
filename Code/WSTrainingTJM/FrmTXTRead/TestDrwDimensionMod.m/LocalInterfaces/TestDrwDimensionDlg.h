// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestDrwDimensionDlg.h
// The dialog : TestDrwDimensionDlg
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
//  Oct 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestDrwDimensionDlg_H
#define TestDrwDimensionDlg_H

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
class TestDrwDimensionDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestDrwDimensionDlg, CATDlgDialog )

  public:

  TestDrwDimensionDlg();
  virtual ~TestDrwDimensionDlg();

  void Build ();

  CATDlgSelectorList* GetSelectorListLine();
  CATDlgPushButton* GetPushButtonClear();
  protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgLabel*      _Label001;
 CATDlgSelectorList*      _SelectorListLine;
 CATDlgFrame*      _Frame002;
 CATDlgPushButton*      _PushButtonClear;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
