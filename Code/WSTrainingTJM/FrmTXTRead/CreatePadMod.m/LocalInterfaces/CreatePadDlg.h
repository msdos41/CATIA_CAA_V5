// COPYRIGHT Dassault Systemes 2018
//===================================================================
//
// CreatePadDlg.h
// The dialog : CreatePadDlg
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
//  Dec 2018  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef CreatePadDlg_H
#define CreatePadDlg_H

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
class CreatePadDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( CreatePadDlg, CATDlgDialog )

  public:

  CreatePadDlg();
  virtual ~CreatePadDlg();

  void Build ();


  protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
