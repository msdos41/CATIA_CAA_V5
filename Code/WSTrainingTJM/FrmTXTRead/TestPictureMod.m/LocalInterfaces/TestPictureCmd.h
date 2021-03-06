// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestPictureCmd.h
// The state chart based command: TestPictureCmd
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
//  Sep 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestPictureCmd_H
#define TestPictureCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

#include "TestPictureDlg.h"

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
class TestPictureCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestPictureCmd, CATStateCommand )

  public:

  TestPictureCmd();
  virtual ~TestPictureCmd();

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

	  TestPictureDlg				*_pDlg;

};

//----------------------------------------------------------------------

#endif
