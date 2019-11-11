// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestCrvRadiusDlg.h
// The dialog : TestCrvRadiusDlg
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
//  Nov 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestCrvRadiusDlg_H
#define TestCrvRadiusDlg_H

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
class TestCrvRadiusDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestCrvRadiusDlg, CATDlgDialog )

  public:

  TestCrvRadiusDlg();
  virtual ~TestCrvRadiusDlg();

  void Build ();
  CATDlgSelectorList* GetSelectorListSurface();
  CATDlgEditor* GetEditorResult();
  protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgLabel*      _LabelSurface;
 CATDlgSelectorList*      _SelectorListSurface;
 CATDlgContainer*      _Container003;
 CATDlgEditor*      _EditorResult;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
