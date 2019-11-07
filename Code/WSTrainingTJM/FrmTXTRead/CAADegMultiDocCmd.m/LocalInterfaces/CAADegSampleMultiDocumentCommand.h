#ifndef CAADegSampleMultiDocumentCommand_h
#define CAADegSampleMultiDocumentCommand_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Sample of command which allows you to select in an another command.
//  This command must be associated to a CATOtherDocumentAgent. 
//  See the command CAADegCreateCylinder2.cpp
//     
//===========================================================================

// DialogEngine Framework
#include "CATMultiDocumentCommand.h" // to derive from
#include "CATPathElementAgent.h"     // for Dialog agent
#include "CATIProduct.h"
class CAADegSampleMultiDocumentCommand : public CATMultiDocumentCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegSampleMultiDocumentCommand.CATNls
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegSampleMultiDocumentCommand.
  //
  CmdDeclareResource(CAADegSampleMultiDocumentCommand, CATMultiDocumentCommand)

  public:

      CAADegSampleMultiDocumentCommand();

      virtual  ~CAADegSampleMultiDocumentCommand();

      // BuildGraph
      // -----------
      // This Command contains only one CATPathElementAgent and one state
      //
      virtual void BuildGraph ();
  
  private:

      // Copy constructor, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAADegSampleMultiDocumentCommand(const CAADegSampleMultiDocumentCommand &iObjectToCopy);

      // Assignment operator, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAADegSampleMultiDocumentCommand & operator = (const CAADegSampleMultiDocumentCommand &iObjectToCopy);

      // SelectionDone
      // --------------
      // This method is called when the end user clicks a circle. 
      // Its role is to valuate the CATOtherDocumentAgent.
      //
      CATBoolean   SelectionDone (void *iDummy);
  
  private:

      // The agent to get the Circle
      CATPathElementAgent _AcquisitionAgent;
};


#endif

