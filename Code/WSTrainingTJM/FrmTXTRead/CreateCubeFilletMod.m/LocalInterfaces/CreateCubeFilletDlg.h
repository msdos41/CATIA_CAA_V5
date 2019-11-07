// COPYRIGHT Dassault Systemes 2018
//===================================================================
//
// CreateCubeFilletDlg.h
// The dialog : CreateCubeFilletDlg
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
#ifndef CreateCubeFilletDlg_H
#define CreateCubeFilletDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"
#include "iostream.h"

//----------------------------------------------------------------------

/**
 * Describe the purpose of your panel here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog framework.
 * (consult base class description).
 */
class CreateCubeFilletDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( CreateCubeFilletDlg, CATDlgDialog )

  public:

  CreateCubeFilletDlg();
  virtual ~CreateCubeFilletDlg();

  void Build ();

  CATDlgSpinner* GetSpinnerFirstLimit();

  CATDlgSpinner* GetSpinnerSecondLimit();

  CATDlgSpinner* GetSpinnerRadius();

protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgLabel*      _LabelFirstLimit;
 CATDlgContainer*      _Container002;
 CATDlgLabel*      _LabelSecondLimit;
 CATDlgContainer*      _Container004;
 CATDlgSpinner*      _SpinnerFirstLimit;
 CATDlgSpinner*      _SpinnerSecondLimit;
 CATDlgContainer*      _Container007;
 CATDlgLabel*      _LabelRadius;
 CATDlgSpinner*      _SpinnerRadius;
 CATDlgLabel*      _Label010;
 CATDlgLabel*      _Label011;
 CATDlgLabel*      _Label012;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
