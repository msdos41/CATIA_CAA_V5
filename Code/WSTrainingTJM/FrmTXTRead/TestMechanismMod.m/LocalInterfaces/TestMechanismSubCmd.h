// COPYRIGHT Dassault Systemes 2021
//===================================================================
//
// TestMechanismSubCmd.h
// The command: TestMechanismSubCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   COMMAND
//End CAA2 Wizard Generation Report
//
//  Nov 2021  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestMechanismSubCmd_H
#define TestMechanismSubCmd_H

#include "CATCommand.h"

//----------------------------------------------------------------------

/**
 * Describe your command here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of System framework.
 * (consult base class description).
 */
class TestMechanismSubCmd: public CATCommand
{
  public:

  TestMechanismSubCmd();
  virtual ~TestMechanismSubCmd();

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
   HRESULT CreateImportedMechanism();
};

//----------------------------------------------------------------------

#endif