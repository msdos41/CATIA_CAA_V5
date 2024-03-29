// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// DrwAnnotationCmd.h
// The state chart based command: DrwAnnotationCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   STATECOMMAND
//End CAA2 Wizard Generation Report
//
//  Jan 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef DrwAnnotationCmd_H
#define DrwAnnotationCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "DrwAnnotationDlg.h"

class CATIndicationAgent;

//----------------------------------------------------------------------

/**
 * Describe your command here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog engine framework.
 * (consult base class description).
 */
class DrwAnnotationCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( DrwAnnotationCmd, CATStateCommand )

  public:

  DrwAnnotationCmd();
  virtual ~DrwAnnotationCmd();

    /**
     * Defines the command automata.
     * <br>
     * <i>(states, transitions and agents)</i>
     */
  virtual void     BuildGraph();

    /**
     * Action associated to state transitions.
     */
  virtual CATBoolean  ActionOne(void * data);

  private:

  CATIndicationAgent	* _Indication;

  DrwAnnotationDlg		* _pDlg;
};

//----------------------------------------------------------------------

#endif
