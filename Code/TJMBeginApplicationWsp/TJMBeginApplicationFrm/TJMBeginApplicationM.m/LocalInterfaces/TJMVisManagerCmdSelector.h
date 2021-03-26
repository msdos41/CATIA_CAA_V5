#ifndef TJMVisManagerCmdSelector_H
#define TJMVisManagerCmdSelector_H

// COPYRIGHT DASSAULT SYSTEMES 1999

// System FrameWork
#include "CATCommand.h"

//Visualization FrameWork
#include "CATHSO.h"
#include "CATPSO.h"


//System FrameWork
class CATPathElement;
class CATNotification;

////Local FrameWork
//class TJMVisManagerCxtMenu;

class TJMVisManagerCmdSelector : public CATCommand
{
public :

   //Constructs the command selector from a Hso and a Pso.
   TJMVisManagerCmdSelector(CATHSO &iHso,CATPSO&iPso);
   virtual ~TJMVisManagerCmdSelector();

   // Analyses eventsb received by the current object thru 
   // the send/receive mechanism of the CATCommand objects.
   CATNotifPropagationMode AnalyseNotification(CATCommand * iFromClient,
               CATNotification * iNotification);
private: 

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    TJMVisManagerCmdSelector ();
        
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    TJMVisManagerCmdSelector(const TJMVisManagerCmdSelector &iObjectToCopy);

    // Assignment operator , not implemented
    // Set as private to prevent from compiler automatic creation as public.
    TJMVisManagerCmdSelector & operator = (const TJMVisManagerCmdSelector &iObjectToCopy);

private:
   CATHSO &_Hso;
   CATPSO &_Pso;
   //TJMVisManagerCxtMenu * _pCxtMenu;
   
};

#endif
