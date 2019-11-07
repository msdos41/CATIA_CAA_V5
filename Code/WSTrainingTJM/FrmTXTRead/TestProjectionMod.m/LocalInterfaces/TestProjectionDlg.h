// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestProjectionDlg.h
// The dialog : TestProjectionDlg
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
//  Mar 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestProjectionDlg_H
#define TestProjectionDlg_H

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
class TestProjectionDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestProjectionDlg, CATDlgDialog )

  public:

  TestProjectionDlg();
  virtual ~TestProjectionDlg();

  void Build ();
  CATDlgSelectorList* GetSelectorListPoint();
  CATDlgSelectorList* GetSelectorListSolid();
  protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgLabel*      _Label001;
 CATDlgContainer*      _Container002;
 CATDlgSelectorList*      _SelectorListPoint;
 CATDlgContainer*      _Container004;
 CATDlgLabel*      _Label005;
 CATDlgSelectorList*      _SelectorListSolid;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
