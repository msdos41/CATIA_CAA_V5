// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestPictureDlg.h
// The dialog : TestPictureDlg
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
//  Sep 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestPictureDlg_H
#define TestPictureDlg_H

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
class TestPictureDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestPictureDlg, CATDlgDialog )

  public:

  TestPictureDlg();
  virtual ~TestPictureDlg();

  void Build ();


  protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgLabel*      _Label001;
 CATDlgLabel*      _Label002;
 CATDlgLabel*      _Label003;
 CATDlgLabel*      _Label004;
 CATDlgEditor*      _Editor005;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif