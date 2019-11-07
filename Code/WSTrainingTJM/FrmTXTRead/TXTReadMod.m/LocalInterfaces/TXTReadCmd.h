// COPYRIGHT Dassault Systemes 2018
//===================================================================
//
// TXTReadCmd.h
// The dialog : TXTReadCmd
// It is a command.
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
//  Nov 2018  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TXTReadCmd_H
#define TXTReadCmd_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"

#include "CATICkeParmFactory.h"
#include "CATIDesignTable.h"
#include "CATICkeSheet.h"

#include "CATILinkableObject.h"
#include "CATDocument.h"
#include "CATIContainerOfDocument.h"
#include "CATIContainer.h"

#include <fstream>
#include <string>
#include "iostream.h"
using namespace std;

#include "CATBSTR.h"

//----------------------------------------------------------------------

/**
 * Describe the purpose of your panel here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog framework.
 * (consult base class description).
 */
class TXTReadCmd: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TXTReadCmd, CATDlgDialog )

  public:

  TXTReadCmd();
  virtual ~TXTReadCmd();

  void Build ();

  CATDlgFile	*	_pSelectFile;

/**
 * Overload this method: when your command gains focus
 * <p>
 * Activates a command.
 * @param iFromClient
 *   The command that requests to activate the current one.
 * @param iEvtDat
 *   The notification sent.
 */
   virtual CATStatusChangeRC Activate(
                            CATCommand * iFromClient,
                            CATNotification * iEvtDat);

/**
 *  Overload this method: when your command loses focus
 * <p>
 * Deactivates a command.
 * @param iFromClient
 *   The command that takes the current active place.
 * @param iEvtDat
 *   The notification sent.
 */
   virtual CATStatusChangeRC Desactivate(
                            CATCommand * iFromClient,
                            CATNotification * iEvtDat);

/**
 *  Overload this method: when your command is canceled
 * <p>
 * Cancels a command.
 * @param iFromClient
 *   The command that takes the current active place.
 * @param iEvtDat
 *   The notification sent.
 */
   virtual CATStatusChangeRC Cancel(
                            CATCommand * iFromClient,
                            CATNotification * iEvtDat);

  protected:
  /**
  * Callback on PushBActivate of _PushButtonReadTXT
  *
  * <br><b>Role</b>: This method handles the PushBActivate event and does
  *   a check on ...
  *
  * @param Command [in]
  *   Pointer to the publisher of the event.
  * @param Notification [in]
  *   Pointer to the notification representing the event.
  * @param data [in]
  *   Possible useful data transmitted to the command OnPushButtonReadTXTPushBActivateNotification
  *
  *
  */
  virtual void OnPushButtonReadTXTPushBActivateNotification (CATCommand *, CATNotification* , CATCommandClientData data);
  /**
  * Callback on PushBActivate of _PushButtonSelectFile
  *
  * <br><b>Role</b>: This method handles the PushBActivate event and does
  *   a check on ...
  *
  * @param Command [in]
  *   Pointer to the publisher of the event.
  * @param Notification [in]
  *   Pointer to the notification representing the event.
  * @param data [in]
  *   Possible useful data transmitted to the command OnPushButtonSelectFilePushBActivateNotification
  *
  *
  */
  virtual void OnPushButtonSelectFilePushBActivateNotification (CATCommand *, CATNotification* , CATCommandClientData data);

  void OpenTXT ();
  wchar_t *txtConvert_Wchar(std::string str);
  CATUnicodeString CAAUStringBuildFromChar(char * strchar);


  private:

   int            m_FirstTime;

   CATUnicodeString _fileName;

//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgContainer*      _Container002;
 CATDlgEditor*      _EditorDir;
 CATDlgFrame*      _Frame004;
 CATDlgPushButton*      _PushButtonReadTXT;
 CATDlgFrame*      _Frame008;
 CATDlgPushButton*      _PushButtonSelectFile;
 CATDlgSelectorList*      _SelectorListTXTContent;
 CATDlgContainer*      _Container010;
 CATDlgContainer*      _Container011;
//END CAA2 WIZARD WIDGET DECLARATION SECTION


//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
