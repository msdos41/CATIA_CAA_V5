
// COPYRIGHT DASSAULT SYSTEMES 2000

//---------------------------------------------------------------------
// CATIA Shape design and Styling  
//---------------------------------------------------------------------
// CAAGsiUserTool class 
//---------------------------------------------------------------------
// 
// Mission         : Class providing tools to handle Shape design features 
// Type            : Class 
// Inputs          : None
// Outputs         : 
// 
// Illustrates     : 1- OpenSession/Create or Open document / close document / end session
//                   2- Save document 
//                   3- Create of Geometrical Set or Ordered Geometrical Sets 
//                   4- Insert feature Wireframe and Shape Design in procedural view 
//                   5- Update 
//                   6- Use GSD Interface for create oand Modify features 
//
//---------------------------------------------------------------------
// Historic 
// creation     : March 2000 / Level V5R7  / 
// modification : Sept. 2002 / Level V5R12 / Integration new Object CATIGSMproceduralView 
// modification : Janv. 2004 / Level V5R14 / Integration GS/OGS 
//-------------------------------------------------------------------

#include "CAAGsiUserTools.h"

// General includes
#include <iostream.h>                  // To have cout


//ObjectModelerBase Framework
#include "CATSession.h"                // To handle Session   
#include "CATDocument.h"               // To Handle Document
#include "CATSessionServices.h"        // To create session
#include "CATDocumentServices.h"       // To create document
#include "CATBaseUnknown.h"            // Base class for V5 Objects 
#include "CATIDescendants.h"           // To aggregats Features and locate them
#include "LifeCycleObject.h"           // To manage LifeCycle
#include "CATIContainer.h"             // To handle Containers imbeded in document 
#include "CATError.h"                  // To manage errors in UpdateObject()
#include "CATInit.h"                   // To initialize documents

//Visualization framework 
#include "CATIModelEvents.h"
#include "CATDelete.h"

// MechanicalModeler Framework 
#include "CATIPrtContainer.h"          // To handle Part Conatiner 
#include "CATIPrtPart.h"               // To handle Part Object
#include "CATMmrLinearBodyServices.h"  // To Handle linearity in OGS 

#include "CATIMechanicalRootFactory.h" // To create Open Body
#include "CATIGSMTool.h"               // To handle GSMTool (Open Body)  
#include "CATMfErrUpdate.h"            // To handle Update Exceptions

// ObjectSpecsModeler Framework 
#include "CATIAlias.h"                 // To change the Display Name of a Feature 
#include "CATISpecObject.h"            // To handle Features
#include "CATIBasicTool.h"            // To handle Features

// Constant 
#include "CATMathConstant.h"           // To access CATPI constant
#include "CATLib.h"                    // To get an environment variable

// LiteralFeatures Framework
#include "CATICkeParmFactory.h"        // To create Literal Features (Parameters)
#include "CATICkeParm.h"               // To handle Literal Features

// GSMInterfaces Framework
#include "CATIGSMFactory.h"            // To create Shape Design Features
#include "CATGSMSweepDef.h"            // To access Sweep Definition enumerates
#include "CATGSMOrientation.h"            // To access Sweep Definition enumerates
#include "CATGSMLoftDef.h"             // To access Loft Definition enumerates
#include "CATIGSMDirection.h"          // To handle Direction Features
#include "CATIGSMPointCoord.h"         // To handle Point Coordinates Features
#include "CATIGSMPointOnCurve.h"       // To handle Point On Curve Features
#include "CATIGSMLinePtPt.h"           // To handle Line Point Point Features
#include "CATIGSMLineAngle.h"          // To handle Line At Angle Features 
#include "CATIGSMLineNormal.h"         // To handle Line Normal Features
#include "CATIGSMSpline.h"             // To handle Spline Features 
#include "CATIGSMCircle2PointsRad.h"   // To handle Circle 2 Points Radius Feature
#include "CATIGSMCircle3Points.h"      // To handle Circle 3 Points Feature
#include "CATIGSMCircleCtrPt.h"        // To handle Circle Center Point Feature     
#include "CATIGSMPlaneEquation.h"      // To handle Plane Equation Feature
#include "CATIGSMPlaneAngle.h"         // To handle Plane At Angle Feature
#include "CATIGSMSplit.h"              // To handle Split Feature
#include "CATIGSMSweepUnspec.h"        // To handle Sweep Unspec Feature
#include "CATIGSMLoft.h"               // To handle Loft Feature
#include "CATIGSMAssemble.h"           // To handle Assemble/join Feature

// GSMInterfaces Framework
#ifdef CAAV5R12 
#include "CATIGSMProceduralView.h"     // To insert in the procedural View (Proposed since V5R12)       
#endif 

//CATImplementClass( CAAGsiUserTools,
//				  Implementation, 
//				  CATBaseUnknown,
//				  CATNull );


// Constructor 
// ---------------------------------------------------------
CAAGsiUserTools::CAAGsiUserTools()
{
    _pSession  = NULL;
    _pDoc      = NULL;
    _pFact     = NULL;
}


// Destructor 
// ---------------------------------------------------------
CAAGsiUserTools::~CAAGsiUserTools()
{
    _pSession = NULL;
    _pDoc     = NULL;
    if (NULL != _pFact) _pFact -> Release();
    _pFact    = NULL ;
}

// Methods 
// ---------------------------------------------------------

// ---------------------------------------------------------------------------
// 1/ SESSION/ CONTAINER /DOCUMENT 
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// Init session and create a part 
// ---------------------------------------------------------------------------
HRESULT CAAGsiUserTools::Init(char *& ipSessionName) 
{
    // The aim of this method is 
    // 1- open a CATIA V5 session 
    // 2- initialize a new Part document as a repository for all geometry created within the sample 
    // 3- retreive shape design factory 
    
    // Return Code Management 
    HRESULT rc = S_OK;
    
    // Create Session: 
    InitSession(ipSessionName);
    New() ;
    return (rc); 
    
}


// Init session
// ---------------------------------------------------------------------------
HRESULT CAAGsiUserTools::InitSession (char *& ipSessionName) 
{
    // The aim of this method is 
    // 1- open a CATIA V5 session 
    // 2- initialize a new Part document as a repository for all geometry created within the sample 
    // 3- retreive shape design factory 
    
    // Return Code Management 
    HRESULT rc = S_OK;
    
    // Create Session: 
    Create_Session(ipSessionName,_pSession);
    return (rc); 
    
    
}

// Creates  a new Part 
// ---------------------------------------------------------------------------
HRESULT CAAGsiUserTools::New() 
{
    // The aim of this method is 
    // 1- Initialize a new Part document as a repository for all geometry created within the sample 
    // 2- retreive shape design factory 
    
    // Return Code Management 
    HRESULT rc = S_OK;
    
    // Creates a New Part Document with Default Name: 'Part1.CATPart'
    CATDocumentServices::New("CATPart",_pDoc);
    if(NULL == _pDoc) {
        cout << "ERROR in creating New document" << endl << flush;
        rc = E_FAIL;
        return rc ; 
    }
    
    // Initializes the Document  
    // --   CATInit_var spInit = _pDoc;
    // --   spInit -> Init(TRUE);
    
    CATInit *piInitOnDoc =NULL;
    rc = _pDoc -> QueryInterface(IID_CATInit ,(void**)&piInitOnDoc);
    
    if (NULL!= piInitOnDoc) { 
        // Retrieve the Root Conatiner which responds to CATIPrtContainer 
        // interface.
        CATIPrtContainer * piPartContainer = 
            (CATIPrtContainer*) piInitOnDoc -> GetRootContainer("CATIPrtContainer");	
        if (NULL != piPartContainer ) {
            
            // Part 
             CATIPrtPart_var  spPart       = piPartContainer -> GetPart();
            
            
            // GSMFactory 
            // Retrieve the Generative Shape Design Interface 
            // == > Keeop in the GsiToll" class to call services in every 'CreateXXX' method
            rc = piPartContainer -> QueryInterface(IID_CATIGSMFactory ,(void**)&_pFact);
            if (FAILED(rc)) {
                cout << "ERROR: CATIGSMFactory is NULL" << endl << flush;
                rc = E_FAIL;
            }
            
            piPartContainer -> Release();piPartContainer= NULL; 
        }
        else {
            
            cout << "ERROR: CATIPrtContainer is NULL" << endl << flush;
            rc = E_FAIL;
        }
        piInitOnDoc ->Release();   piInitOnDoc = NULL; 
        
    }
    else { 
        
        cout << "ERROR: Init part failed " << endl << flush;
        rc = E_FAIL;
    }
    return rc;
    
    
}


// Open  Part 
// ---------------------------------------------------------------------------
HRESULT CAAGsiUserTools::Open(char *& ipDocName)
{
    
    // The aim of this method is 
    // 1- Open exiting CATPart 
    // 3- retreive shape design factory 
    
    // Return Code Management 
    HRESULT rc = S_OK;
    
    
    cout << "Open = " << ipDocName << endl << flush;
    
    // Open Part 
    CATDocumentServices::OpenDocument( ipDocName, _pDoc);
    if(NULL == _pDoc) {
        cout << "ERROR in openning document" << ipDocName <<  endl << flush;
        rc = E_FAIL;
    }
    
    // Initializes the Document _pDoc 
    CATInit_var spInit = _pDoc;
    if (NULL_var != spInit) { 
        
        // Retrieve the Root Conatiner which responds to CATIPrtContainer 
        // interface.
        CATIPrtContainer * piPartContainer = 
            (CATIPrtContainer*) spInit -> GetRootContainer("CATIPrtContainer");	

        if (NULL != piPartContainer ) {
            
            // Part 
            CATIPrtPart_var   spPart       = piPartContainer -> GetPart();
            
            
            // GSMFactory 
            // Retrieve the Generative Shape Design Interface 
            // == > Keeop in the GsiToll" class to call services in every 'CreateXXX' method
            rc = piPartContainer -> QueryInterface(IID_CATIGSMFactory ,(void**)&_pFact);
            if (FAILED(rc)) {
                cout << "ERROR: CATIGSMFactory is NULL" << endl << flush;
                rc = E_FAIL;
            }
            
            piPartContainer -> Release();piPartContainer= NULL; 
        }
        else {
            
            cout << "ERROR: CATIPrtContainer is NULL" << endl << flush;
            rc = E_FAIL;
        }
    }

    return rc;

}

// Save Part 
// ---------------------------------------------------------------------------
HRESULT CAAGsiUserTools::Save(char *& ipDocName)
{
    // The aim of this method is to  save generated geometry in a persistant CATPart file 
    
    // Saving CATPart 
    //---------------------------------------------------------------
    // Save the document under the name entered as an argument:  the entire path is  necessary 
    // If only the name is given, the CATPart is save in current directory 
    HRESULT rc = S_OK; 
    if (NULL != ipDocName)      {    
        cout << "Document name = "<< ipDocName << endl << flush;
        rc = CATDocumentServices::SaveAs  (*_pDoc, ipDocName);
        if (SUCCEEDED(rc))   {
            cout << "Document saved OK" << endl << flush;
        }
        else {
            cout << "ERROR in saving document" << endl << flush;
        }
    }
    return rc;
}

// Close session
// ---------------------------------------------------------------------------
HRESULT CAAGsiUserTools::Close(char *& ipSessionName)
{
    
    // The aim of this method is to close the session 
    
    // Remove the document from the session
    HRESULT rc = S_OK;
    
    rc = CATDocumentServices::Remove ( * _pDoc);
    if (SUCCEEDED(rc)) { 
        cout << "Document removed OK" << endl << flush;
    }
    else    {
        cout << "ERROR in removing document" << endl << flush;
        return E_FAIL;
    }
    
    // Delete session
    rc = Delete_Session(ipSessionName);
    if (SUCCEEDED(rc)) {
        cout << "Session deleted OK" << endl << flush;
    }
    else     {
        cout << "ERROR in deleting session" << endl << flush;
        return E_FAIL;
    }
    return S_OK;
    
}

//
// Retrieve current document 
// ---------------------------------------------------------------------------
CATDocument * CAAGsiUserTools::GetDoc()
{
    return _pDoc;
}

// ---------------------------------------------------------------------------
// 2/ GSD Tools  
// ---------------------------------------------------------------------------
// An important aspect of managing objects in V5 is the ability to group them 
// in logical bodies named a tool that allow to clarify the design a Part. 
// GSM Objects are created in a GSMTool, several GSMTools can be used in order
// to describe different sub-part of a Part  
//
//   Part
//    ! 
//    ! - PartBody 
//    !      ! 
//    !      ! -- <Feature.1>
//    !      ! -- <Feature.2>
//    !      ! -- <Feature.3>
//    !      ! -- GS or OGS.2  <--------  Body created if Feature.3 is  current  and Toplevel = 0  
//    !      ! -- <Feature.3>         
//    !      ! ....
//    ! 
//    ! - GS or OGS.1          <--------  Prexistent Body>    
//    !  
//    ! - GS or OGS.3          <--------  Body created if PartBody (or GS or OGS) is current whatever Toplevel value   
//    ! 
//    ! 

// Create  GSM Tools 
// ---------------------------------------------------------------------------
//
// Enhanced  V5R13 : Add argument for GS or OGS creation 
// --------------------------------------------
CATIGSMTool_var 
CAAGsiUserTools::CreateGSMTool(const CATUnicodeString& iName,int iSetAsCurrent, int iTopLevel, int iType )
// CATIGSMTool_var 
// CAAGsiUserTools::CreateGSMTool(const CATUnicodeString& iName,int iSetAsCurrent, int iTopLevel)

{
    
    // Create a new GSM Tool  
    // Warning:   father of New GSMTool can be an objet or the root PartBody tool  
    
    
    // Phase 1: Retrieve the current Part container
    // --------------------------------------------- 
    CATIContainer_var             spCont       = _pFact ;
    CATIPrtContainer_var          spPartCont   = spCont;
    CATIPrtPart_var               spPart       = spPartCont -> GetPart();
    
    CATIGSMTool_var spTool = NULL_var;
    if (NULL_var != spPart )
    {
        int Position = -1;
        // Note: iTopLevel allow to create the tools directly under the root of the graph  
        // iTopLevel = 0 : Create under current feature  
        // iTopLevel = 1 : Create directly under Part 
        
        // Phase 2: Retreive the active Tool (Always one exist) 
        // --------------------------------------------- 
        
        // Reference Part 
        CATISpecObject_var spParentForGSMTool = spPart;
        
        // iTopLevel = 1 / GSM Tools is created under Part
        // Note: It is the default behavior 
        
        // iTopLevel = 0 / GSM Tools is created under current feature 
        if (iTopLevel==0)
        {
            // Read Current Tool
            // Note: Current Tool is 
            // either a PartBody (  Necessary: spCurrentFeat == spCurrentTool)
            // either a GS or OGS(  Necessary: spCurrentFeat == spCurrentTool)
            CATIBasicTool_var spCurrentTool = spPart -> GetCurrentTool();
            
            // Read Current feature 
            // A  tool can be insert after an already defined part feature  
            CATISpecObject_var spCurrentFeat = spPart->GetCurrentFeature();
            
            // Note: Current Feature is 
            // either a PartBody 
            //    Necessary: spCurrentFeat == spCurrentTool 
            //    Position = 0 : The tool is created under Part 
            // either an GS or OGS
            //    Necessary: spCurrentFeat == spCurrentTool 
            //    Position = 0 : The tool is created under Part 
            // either a Feature under a PartBody  
            //    The Tools is created after the current feature which position is set below
            if ( spCurrentFeat != spCurrentTool)
            {
                // The Tool Parent will be the Current Tool
                spParentForGSMTool  = spCurrentTool;
                // Read position of Current Feature in Tool
                CATIDescendants_var spRoot = spCurrentTool;
                Position = spRoot -> GetPosition( spCurrentFeat);
            }
        }
        
        
        CATISpecObject_var spSpecTool;  
        // Phase 3: Create a GSMTool
        // --------------------------------------------- 
        if (NULL_var != spParentForGSMTool)
        {
            CATIMechanicalRootFactory_var spMechRoot = spCont ;
            
            //  Enhanced V5R13 
            // ------------------------------------------
            HRESULT rc = E_FAIL; 
            if (0 == iType ) { 
                
                //cout << " Create GS  "<< iName << endl; 
                rc = spMechRoot -> CreateGeometricalSet(iName,spParentForGSMTool,spSpecTool,Position);
                
            }
            else  if (1 == iType ) { 
               
                //cout << " Create OGS  "<< iName << endl; 
                rc = spMechRoot -> CreateOrderedGeometricalSet(iName,spParentForGSMTool,spSpecTool,Position);
                
            }
            // Deprecated method in V5R13 
            // ------------------------------------------
            // spSpecTool  = spMechRoot -> CreateGSMTool(iName,spParentForGSMTool,Position);
        }
        
        if (NULL_var != spSpecTool) {
            
            spTool = spSpecTool ; 
            // Phase 4: Set  GSMTool as current 
            // --------------------------------------------- 
            if (0 != iSetAsCurrent)
            {
                // CATIPrtManagement deprecated in V5R11
                if (NULL_var != spPart) { 
                    //cout << " Tools "<< iName << " set as current" << endl; 
                    spPart -> SetCurrentFeature(spSpecTool);
                }
            }
        }
    }
    
    // Return GSMTool
    return spTool;
}  

//
//  Get current GSM Tool and create one if none found 
//---------------------------------------------------------------------

CATIGSMTool_var 
CAAGsiUserTools::GetCurrentGSMTool(const CATUnicodeString& iName,int iSetAsCurrent)
{
    // Get Current part 
    CATIContainer_var             spCont      = _pFact;
    CATIPrtContainer_var          spPartCont  = spCont;
    CATIPrtPart_var               spPart      = spPartCont -> GetPart();
    
    CATIGSMTool_var spTool = NULL_var;
    
    if (NULL_var != spPart)
    {    
        // Is-it a GSMTool in current Tool ?
        CATIBasicTool_var spCurrentTool = spPart->GetCurrentTool();
        spTool = spCurrentTool;
        
        //1. GSMTool is the current 
        if (NULL_var != spTool)
        {
            // Retrieve existant tools 
            CATISpecObject_var spExternalRef = spPart->GetBodyForExternalReferences();
            if (NULL_var != spExternalRef && spTool == spExternalRef)
                spTool = NULL_var;
        }
        
        //2. No Pre-existant GSMTool  
        if (NULL_var == spTool)
        {
            
            spTool = CreateGSMTool(iName);
        }
    }
    
    // Return GSMTool
    return spTool;
}



// Insert a Feature in the procedural view 
//-----------------------------------------------------------------------------
// The aim of this method is to allow created and updated feature  to be visible 
// in the standard V5 Graph Editor 

HRESULT 
CAAGsiUserTools::InsertInProceduralView(const CATISpecObject_var& ispObjectToAppend,
                                        const CATISpecObject_var& ispInputParent)
{
    
    
#ifdef CAAV5R12 
    // V5R12 AND FOLLOWING VERSIONS: Tool to Insert into the procedural view 
    //   ----------------------------------------------------------------------------
    
    HRESULT rc = E_FAIL; 
    CATIGSMProceduralView_var curobj = ispObjectToAppend;
    if (NULL_var != curobj ) {
        rc = curobj->InsertInProceduralView(ispInputParent);
    }
    return rc ;
    
#elif
    // BEFORE V5R12 : Insert in procedural view  
    // -----------------------------------------------------------------------------
    //  Note: Section deprecated V5R12 
    
    CATIGSMTool_var spTool = ispInputParent;
    // Check Father / Initialize current GSMTool  
    if (NULL_var == spTool)
        spTool = GetCurrentGSMTool("",1);
    
    // Append object 
    if ( NULL_var != ispObjectToAppend && NULL_var != spTool)
    {
        CATIDescendants_var spParent = spTool;
        if ( NULL_var != spParent)
            // Add in current GSMTool ispObjectToAppend
            spParent -> Append ( ispObjectToAppend );
        else
            return E_FAIL;
    }
    else  
        return E_FAIL;
    return S_OK;
#endif 
}


// Update 
// ---------------------------------------------------------------------------
// This method encapsulates the standard update, in order to catch if needed update errors 
HRESULT CAAGsiUserTools::ObjectUpdate(const CATISpecObject_var & ispSpec)
{
    HRESULT rc = S_OK; 
    if ( NULL_var != ispSpec ) {
        // Declare a bloc where every exceptions will be catch and treated in
        // the CATCatch() block
        CATTry  {	
            
            // Update feature 
            ispSpec -> Update();
            
            //
            // Enhanced V5R13 : Manage linearity for OGS 
            // --------------------------------------------
            // check Linearity / usefull for absorbant feature inserted  in OGS 
            CATISpecObject_var spFather = ispSpec->GetFather();
            if ( NULL_var  != spFather )        {
                CATIGSMTool *piGSMToolFather = NULL;
                rc =spFather->QueryInterface ( IID_CATIGSMTool, (void**) &piGSMToolFather);
                if ( SUCCEEDED(rc) ) { 
                    int IsAnOGS = -1 ;
                    piGSMToolFather->GetType(IsAnOGS) ;
                    if ( 1 == IsAnOGS ) {
                        CATBaseUnknown_var spUnkwnSpec = ispSpec;
                        rc = CATMmrLinearBodyServices::Insert(spUnkwnSpec) ; 
                    } 
                    piGSMToolFather->Release() ; piGSMToolFather=NULL; 
                }   
                spFather -> Release() ; 
            }
            // End of update
            
            
        }
        
        // This block is specific for Update Errors
        CATCatch(CATMfErrUpdate,error)	 {
            cerr << " Update Error: " << (error-> GetDiagnostic()).ConvertToChar() << endl; 
            Flush(error) ; 
            return E_FAIL; 
        }
        // This block treats every other exception
        CATCatch(CATError,error)    {
            cerr << " Error: " << error->GetMessageText() <<endl; 
            Flush(error);
            return E_FAIL; 
        }
        CATEndTry;
        
    }
    return rc ; 
}


// ---------------------------------------------------------------------------
// 4/ GSM Object Creation 
// ---------------------------------------------------------------------------
// see CATIGSMFactory 

// Litteral Definition 
//---------------------------------------------------------------------------
HRESULT 
CAAGsiUserTools::CreateLength (const char* ipNameParam ,const double iValue, CATISpecObject_var &ospCkeParam) 
{
    CATICkeParmFactory_var spCkeFact = _pFact ;
    
    CATICkeParm_var  spParm = NULL_var;
    spParm    = spCkeFact -> CreateLength(ipNameParam,iValue/1000.);
    if (NULL_var == spParm) {
        cout << "ERROR in creating Cke length paramater" << endl << flush;
        return E_FAIL;
    }
    else {
        ospCkeParam = spParm; 
        return S_OK;
    }
    
}

HRESULT 
CAAGsiUserTools::CreateAngle (const char* ipNameParam ,const double iValue, CATISpecObject_var &ospCkeParam) 
{
    CATICkeParmFactory_var spCkeFact = _pFact ;
    
    CATICkeParm_var spParm = NULL_var;
    spParm = spCkeFact -> CreateAngle(ipNameParam,(iValue/180.)*CATPI);
    if (NULL_var == spParm) {
        cout << "ERROR in creating Cke angle paramater" << endl << flush;
        return E_FAIL;
    }
    else {
        ospCkeParam = spParm; 
        return S_OK;
    }
}
HRESULT 
CAAGsiUserTools::CreateReal (const char* ipNameParam ,const double iValue, CATISpecObject_var &ospCkeParam) 
{
    CATICkeParmFactory_var spCkeFact = _pFact;
    
    CATICkeParm_var spParm = NULL_var;
    spParm = spCkeFact -> CreateReal(ipNameParam,iValue);
    if (NULL_var == spParm) {
        cout << "ERROR in creating Cke real paramater" << endl << flush;
        return E_FAIL;
    }
    else {
        ospCkeParam = spParm; 
        return S_OK;
    }
}

// Direction
//---------------------------------------------------------------------------
// Direction:  standard GSM Object used as input of several other GSM Features 
CATISpecObject_var CAAGsiUserTools::CreateDirection(CATISpecObject_var & ispSpec)
{
    CATISpecObject_var spDirObj ; 
    if ( NULL != _pFact ) { 
        CATIGSMDirection_var spDir = _pFact -> CreateDirection(ispSpec);
        spDirObj = spDir;
    }
    return spDirObj;
}

// Point Coord 
//---------------------------------------------------------------------------
// Create a point using with 3D coordinates 
//
// Inputs : 
// List= (3 Cke parameters (X,Y,Z)) 
// see CATIGSMFactory.h 
// 
CATISpecObject_var CAAGsiUserTools::CreatePointCoord(
                                                     CATLISTV(CATISpecObject_var) &iaObjectsParam)
{
    int size = iaObjectsParam.Size();
    CATICkeParm_var spParm1 = iaObjectsParam [size-2];
    CATICkeParm_var spParm2 = iaObjectsParam [size-1];
    CATICkeParm_var spParm3 = iaObjectsParam [size];
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        
        // Create feature 
        CATIGSMPointCoord_var spPoint = _pFact -> CreatePoint(spParm1,spParm2,spParm3);
        
        // Insert in procedural view 
        spSpecTmp = spPoint;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}

// Point OnCurve 
//---------------------------------------------------------------------------
// Create a point on a curve  
//
// Inputs :  
//  List= (Reference curve, reference point, parameter (between 0. and 1.)),Orientation  
// see CATIGSMFactory.h 
// 
CATISpecObject_var CAAGsiUserTools::CreatePointOnCurve(
                                                       CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iProx)
{
    int size = iaObjectsParam.Size();
    CATISpecObject_var spCurve = iaObjectsParam [size-2];
    CATISpecObject_var spPoint = iaObjectsParam [size-1];
    CATICkeParm_var spParm = iaObjectsParam [size];
    
    CATGSMOrientation hOrient(CATGSMSameOrientation);
    if (FALSE == iProx)
        hOrient = CATGSMInvertOrientation;
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMPointOnCurve_var spPoint1 = _pFact -> CreatePoint(spCurve,spPoint,spParm,hOrient);
        
        // Insert in procedural view 
        spSpecTmp = spPoint1;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}


// Lines PtPt 
//---------------------------------------------------------------------------
// Line Point point 
//
// Inputs :  
//  List= (First point, Second Point) 
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateLinePtPt(CATLISTV(CATISpecObject_var) &iaObjectsParam)
{
    int size = iaObjectsParam.Size();
    CATISpecObject_var spFirst = iaObjectsParam [size - 1];
    CATISpecObject_var spSecond = iaObjectsParam [size];
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMLinePtPt_var spLine = _pFact -> CreateLine(spFirst,spSecond);
        
        // Insert in procedural view 
        spSpecTmp = spLine;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}


// Lines Normal to a Curve
//---------------------------------------------------------------------------
// Line Point to a curve = Line Angle of 90DEG to a curve on a point  
//
// Inputs :  
// List=(Ref curve, Ref Surface, Ref Point,Start Length,End Length) , Orientation 
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateLineNormalCrv(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iGeodesic,CATBoolean iOrient)
{
    int size = iaObjectsParam.Size();
    CATISpecObject_var spCurve = iaObjectsParam [size-4];
    CATISpecObject_var spSurf  = iaObjectsParam [size-3];
    CATISpecObject_var spPoint = iaObjectsParam [size-2];
    CATICkeParm_var spStart    = iaObjectsParam [size-1];
    CATICkeParm_var spEnd      = iaObjectsParam [size]; 
    
    // Define the angle value (90DEG) for a Line Angle to a curve 
    int num       = 1; 	
    double values = -90.;
    CATICkeParmFactory_var spCkeFact = _pFact;
    CATICkeParm_var spAngle          = NULL_var ;
    spAngle  = spCkeFact -> CreateAngle("Angle",(values/180.)*CATPI);
    
    
    CATGSMOrientation hOrient(CATGSMSameOrientation);
    if ( FALSE == iOrient)
        hOrient = CATGSMInvertOrientation;
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMLineAngle_var spLine = _pFact -> CreateLine(spCurve,spSurf,spPoint,iGeodesic,spStart,spEnd,spAngle,hOrient);
        
        // Insert in procedural view 
        spSpecTmp = spLine;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}


// Circle 2 Points and a radius 
//---------------------------------------------------------------------------
// Circle passing by two point with an impose radius 
//
// Inputs :  
//  List= (First Point , Seccond Point, Ref Surface, Radius) , Geodesic param, Orientation 
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateCircle2PointsRad(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iGeodesic,CATBoolean iOrient)
{
    int size = iaObjectsParam.Size() ;
    CATISpecObject_var spFirst  = iaObjectsParam [size-3];
    CATISpecObject_var spSecond = iaObjectsParam [size-2];
    CATISpecObject_var spSurf   = iaObjectsParam [size-1];
    CATICkeParm_var hRad       = iaObjectsParam [size];
    CATGSMOrientation hOrient(CATGSMSameOrientation);
    if (FALSE == iOrient)
        hOrient = CATGSMInvertOrientation;
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMCircle2PointsRad_var spCircle = _pFact -> CreateCircle(spFirst,spSecond,spSurf,iGeodesic,hRad,hOrient);
        
        // Insert in procedural view 
        spSpecTmp = spCircle;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    
    return spSpecTmp;
}


// Circle 3 Points 
//---------------------------------------------------------------------------
// Circle passing by two point with an impose radius 
//
// Inputs :  
// List= (First Point , Second Point, Third Point) 
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateCircle3Points(CATLISTV(CATISpecObject_var) &iaObjectsParam)
{
    int size = iaObjectsParam.Size();
    CATISpecObject_var spFirst = iaObjectsParam [size-2];
    CATISpecObject_var spSecond = iaObjectsParam [size-1];
    CATISpecObject_var spThird = iaObjectsParam [size];
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMCircle3Points_var spCircle = _pFact -> CreateCircle(spFirst,spSecond,spThird);
        
        // Insert in procedural view 
        spSpecTmp = spCircle;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}


// Circle center and a point  
//---------------------------------------------------------------------------
// Circle or part of circle defined by its center and a passing point 
//
// Inputs :  
// List=(Center, PassingPoint, Ref Surface,  ,Start Length,End Length) , Geodesic parameter 
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateCircleCenterRad(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iGeodesic)
{
    int size = iaObjectsParam.Size();
    CATISpecObject_var spCenter = iaObjectsParam [size-4];
    CATISpecObject_var spPassPt = iaObjectsParam [size-3];
    CATISpecObject_var spSurf   = iaObjectsParam [size-2];
    CATICkeParm_var spStart     = iaObjectsParam [size-1];
    CATICkeParm_var spEnd       = iaObjectsParam [size];
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMCircleCtrPt_var spCircle = _pFact -> CreateCircle(spCenter,spPassPt,spSurf,iGeodesic,spStart,spEnd);
        
        // Insert in procedural view 
        spSpecTmp = spCircle;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}


// Spline curve define n Points and 2 tgte extremity 
//---------------------------------------------------------------------------
// Define n Points and 2 tgte extremity
//
// Inputs :  
// List=(Points), Direction of 1st Tgcy, Orientation 1st Tgcy, Direction of 2nd Tgcy, Orientation 2nd Tgcy
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateSpline(CATLISTV(CATISpecObject_var) &iaObjectsParam,
                                                 CATISpecObject_var & ispSpecStart,CATBoolean iOrientStart, 
                                                 CATISpecObject_var & ispSpecEnd  ,CATBoolean iOrientEnd)
{
    
    // Create feature 
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        CATIGSMSpline_var  spSpline =	_pFact -> CreateSplinePoints( iaObjectsParam );
        spSpecTmp = spSpline;
        if (NULL_var != ispSpecStart) {
            CATIGSMDirection_var spDirStart = ispSpecStart; 
            spSpline -> AddTangentDirection (spDirStart,1);
            if (TRUE == iOrientStart) spSpline -> InvertDirection(1);
        }
        if (NULL_var != ispSpecEnd) {
            CATIGSMDirection_var spDirEnd = ispSpecEnd;
            int size = 0;
            spSpline -> GetSize(size);
            spSpline -> AddTangentDirection(spDirEnd,size);
            if (TRUE == iOrientEnd) spSpline -> InvertDirection(size);
        }
        
        // Insert in procedural view 
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}  


// Plane Equation
//---------------------------------------------------------------------------
// Define n Points and 2 tgte extremity
//
// Inputs :  
// List=(A,B,C,D Cartesian Parameters)
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreatePlaneEquation(CATLISTV(CATISpecObject_var) &iaObjectsParam)
{
    int size = iaObjectsParam.Size();
    CATICkeParm_var hA = iaObjectsParam [size - 3];
    CATICkeParm_var hB = iaObjectsParam [size - 2];
    CATICkeParm_var hC = iaObjectsParam [size - 1];
    CATICkeParm_var hD = iaObjectsParam [size];
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMPlaneEquation_var spPlane = _pFact -> CreatePlane(hA,hB,hC,hD);
        
        // Insert in procedural view 
        spSpecTmp = spPlane;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}

// Plane Angle 
//---------------------------------------------------------------------------
// Plan define from an other plane by rotation on a Line Axis 
//
// Inputs :  
// List=(Ref Plane, Rotation axis, Angle parameter), Orientation 
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreatePlaneAngle(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iOrient)
{
    int size = iaObjectsParam.Size();
    CATISpecObject_var spPlane = iaObjectsParam [size - 2];
    CATISpecObject_var spAxis  = iaObjectsParam [size - 1];
    CATICkeParm_var spParm     = iaObjectsParam [size];
    CATGSMOrientation hOrient(CATGSMSameOrientation);
    if (FALSE == iOrient) hOrient = CATGSMInvertOrientation;
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMPlaneAngle_var spPlane1 = _pFact -> CreatePlane(spPlane,spAxis,spParm,hOrient);
        
        // Insert in procedural view 
        spSpecTmp = spPlane1;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}

// Split
//---------------------------------------------------------------------------
// Split of and Object by another 
//
// Inputs :  
// List=(Objec t to split, Ref Object), Orientation 
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateSplit(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iOrient)
{
    int size = iaObjectsParam.Size();
    CATISpecObject_var spFirst  = iaObjectsParam [size - 1];
    CATISpecObject_var spSecond = iaObjectsParam [size];
    CATGSMOrientation hOrient(CATGSMSameOrientation);
    if (FALSE == iOrient)  hOrient = CATGSMInvertOrientation;
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMSplit_var spSplit = _pFact -> CreateSplit(spFirst,spSecond,hOrient);
        
        // Insert in procedural view 
        spSpecTmp = spSplit;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}

// Sweep with a profile and a guide 
//---------------------------------------------------------------------------
// Sweep define by a profile and one Guide 
//
// Inputs :  
// List=(Guide,profile)
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateSweepOneGuide(CATLISTV(CATISpecObject_var) &iaObjectsParam)
{
    int size = iaObjectsParam.Size();
    CATISpecObject_var spGuide   = iaObjectsParam [size - 1];
    CATISpecObject_var spProfile = iaObjectsParam [size];
    CATISpecObject_var spUnused  = NULL_var;
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMSweepUnspec_var spSweep = _pFact -> CreateExplicitSweep(spGuide,spUnused,spProfile,spGuide);
        
        // Insert in procedural view 
        spSpecTmp = spSweep;
        InsertInProceduralView(spSpecTmp);
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}


// Loft 
//---------------------------------------------------------------------------
// Loft surface define by section ans guide and an optionnal spine 
//
// Inputs :  
// List=(sections, guides ), spine curve
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateLoft(CATLISTV(CATISpecObject_var) & iaObjectsParamSections,
                                               CATLISTV(CATISpecObject_var) & iaObjectsParamGuides,
                                               CATISpecObject_var & ispSpine)
{
    int sizeS = iaObjectsParamSections.Size();
    int sizeG = iaObjectsParamGuides.Size();
    
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMLoft_var spLoft = _pFact -> CreateLoft();
        int i = 1;
        // Sections
        for (;i <= sizeS; i++) {
            spLoft -> AddSection(iaObjectsParamSections[i]);
        }
        // Guides
        for (i=1; i<= sizeG; i++) {
            spLoft -> AddGuide(iaObjectsParamGuides[i]);
        }
        // Spine
        if (NULL_var != ispSpine) {
            spLoft -> SetSpine(CATGSMLoftUserSpine,ispSpine);
        }
        else {
            // Case of Automatic Spine for Loft
            spLoft -> SetSpine();
        } 
        
        // Insert in procedural view 
        spSpecTmp = spLoft;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}

// Assemble 
//---------------------------------------------------------------------------
// Loft surface define by section ans guide and an optionnal spine 
//
// Inputs :  
// List    = Spec to Assemble 
// ispDev  = Merging distance fixed by the user 
// iConnex = Check connexity 
// see CATIGSMFactory.h 
CATISpecObject_var CAAGsiUserTools::CreateAssemble(CATLISTV(CATISpecObject_var) & iaObjectsParamAssemble,
                                                   const double  iDev,
                                                   CATBoolean iConnex)
{
    int sizeAss = iaObjectsParamAssemble.Size();
    // cout << "(CAAGsiUserTools::CreateAssemble) iDev = " << iDev<< endl << flush;
    CATICkeParmFactory_var spCkeFact = _pFact ;
    
    CATICkeParm_var  spDev = NULL_var;
    /*
    spDev    = spCkeFact -> CreateLength("MergingDistance",iDev);
    if (NULL_var == spDev) {
    cout << "ERROR in creating Cke length paramater" << endl << flush;
    return NULL_var;
    
      }
    */
    CATISpecObject_var spSpecTmp ;
    if ( NULL != _pFact ) { 
        // Create feature 
        CATIGSMAssemble_var spAssemble = _pFact -> CreateAssemble(iaObjectsParamAssemble,spDev,iConnex);
        
        // Insert in procedural view 
        spSpecTmp = spAssemble;
        InsertInProceduralView(spSpecTmp);
        
        // Update  
        ObjectUpdate(spSpecTmp);
    }
    return spSpecTmp;
}

