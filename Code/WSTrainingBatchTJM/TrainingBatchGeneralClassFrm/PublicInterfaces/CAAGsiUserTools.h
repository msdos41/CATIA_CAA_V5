#ifndef CAAGsiUserTools_h
#define CAAGsiUserTools_h 
// ===========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//  Abstract of the class:
//  ----------------------
//
//  Concrete class exposing general services for Document, 
//  Open Body creation and ProceduralView Management.
//  This class exposes services for creating Generative Shape Design
//  Features, encapsulating the CATIGSMFactory services. 
//  This Class can be used to write various batch creation files of GSM Features. 
//
// ===========================================================================
//  Inheritance:
//  ------------
//             None
//
// ===========================================================================
//  Main Method:
//  ------------
// (General Services)
//   Init
//   Save
//   Close
// 
// (Open Body and Procedural View Management)
//   CreateGSMTool
//   GetCurrentGSMTool
//   InsertInProceduralView
//   ObjectUpdate
// 
// (Datum)
//   ConvertToDatum
//
// (Literal FeatureCreation)
//   CreateLength
//   CreateAngle
//   CreateReal
//
// (Generative Shape Design Feature Creation)
//   CreateDirection
//   CreatePointCoord   
//   CreatePointOnCurve
//   CreateLinePtPt
//   CreateLineNormalCrv
//   CreateCircle2PointsRad
//   CreateCircleCenterRad
//   CreateCircle3Points   
//   CreateSpline
//   CreatePlaneEquation
//   CreatePlaneAngle
//   CreateSplit
//   CreateSweepOneGuide
//   CreateLoft
//   
// =========================================================================== 
#include "TestBatchGeneralClassMod.h"

#define CAAV5R12 

// ObjectModelerBase Framework
class CATSession;                     // To Create Session
class CATDocument;                    // To Create Document

// ObjectSpecsModeler Framework
class CATISpecObject_var;             // To handle Features
#include "CATLISTV_CATISpecObject.h"  // To handle List of Features

// MechanicalModeler Framework
class CATIGSMTool_var;                // To handle Open Body

// GSMInterfaces Framework 
class CATIGSMFactory;                 // To handle GSM Factory and Create GSM Features

// System Framework
#include "CATUnicodeString.h"         // To handle Display Name for Open Body 
#include "CATBoolean.h"               // Definition of TRUE, FALSE values 

// PrivateInterfaces
//#include "CAAGsiToolkit.h"            // To export Services to CAAGsiNozzle


#define CAAV5R12      // Tool to Insert into the procedural View Proposed in V5R12 and following 

/**
 * GSM Feature user tools objects.
 * <b>Role</b>: To provide all require methods used to create Generative Shape Design Features 
 * <br> The CAAGsiUserTools object illustrate :
 * <br> - The creation of a GSMTool (also called Open Body)
 * <br> - The insertion of a Generative Shape Design Feature into the graph editor 
 * <br> - The creation of different Generative Shape Design Features  
 * <br 
 * <br>   For each Feature, it is created from the inputs, updated in order to 
 * <br>   generate geometry and insert in procedural view in order to see it  
 * <br>   in Graph editor
 * <br>  
 * <br> You can use this class like this:
 * <pre> CAAGsiUserTools MyTools;
 *       MyTools.Init("TheSessionForMyWork");     
 *       ...
 *       MyTools.Save("ThePartIWantToKeep.CATPart");
 *       MyTools.Close("TheSessionForMyWork");
 * </pre>
 * @see CATIGSMFactory
 */
class ExportedByTestBatchGeneralClassMod CAAGsiUserTools
{
 
public:
 
  /**
   * Constructor 
   */ 
  CAAGsiUserTools();

  /**
   * Destructor 
   */ 
  virtual ~CAAGsiUserTools();
  
  // Session/Part 
  // --------------

  /**
   * Initialization 
   * <br>- Open a CATIA V5 session.
   * <br>- Initialize a new Part document as a repository for all geometry created within the sample 
   * <br>- Retreive shape design factory 
   *   @param ipSessionName 
   *      Name of the session 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   * note : encapsulate InitSession + New 
   */ 
   HRESULT   Init(char *& ipSessionName);  

  /**
   * Initialization of session.
   * <br>- Open a CATIA V5 session.
   *   @param ipSessionName 
   *      Name of the session 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */ 
   HRESULT   InitSession(char *& ipSessionName);  

  /**
   * Initialization of session.
   * <br>- Initialize a new Part document as a repository for all geometry created within the sample 
   * <br>- Retreive shape design factory 
   *   @param ipSessionName 
   *      Name of the session 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */ 
   HRESULT   New () ;

  /**
   * Initialization of session.
   * <br>- Open an exiting CATPart 
   * <br>- Retreive shape design factory 
   *   @param ipSessionName 
   *      Name of the session 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */ 
   HRESULT   Open (char *& ipDocName);
   
   /**
   *  Saving generated geometry in a persistant CATPart file 
   *  <br> Note: The CATPart will be save if the environnemnet variable CAAGsi_SAVE_PART is set 
   *   @param ipDocName 
   *      Name of the CATPart document to save 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */ 
   HRESULT   Save(char *& ipDocName);
 
  /** 
   * Closing the session 
   *   @param ipSessionName 
   *      Name of the session 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */
   HRESULT   Close(char *& ipSessionName);

  /**
   * Getting the CATDocument _pDoc
   *   @return
   *      Current document
   */
   CATDocument * GetDoc();
  
   
  
  
  //  Tools 
  // -------------------------------
  /** 
   * Tool management 
   * An important aspect of managing objects in V5 is the ability to group them 
   * in logical bodies named a tool that allow to clarify the design a Part. 
   * GSM Objects are created in a GSMTool, several GSMTools can be used in order
   * to describe different sub-part of a Part  
   */

  /**
   * Create a new Geometrical Set  or  ordered Geometrical Set 

   *   @param iName 
   *      Name of Tool to create 
   *   @param iSetAsCurrent 
   *      =0 not become current GSMtool 
   *      =1 set new GSM tool at current 
   *   @param iTopLevel 
   *      = 0 created at current position
   *      = 1 directly created under the PartBody 
   *  // Enhanced  V5R13 : Add argument for GS or OGS creation 
   *   @param iType  
   *      = 0 GS
   *      = 1 OGS 
   *  //  #endif 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */ 
   CATIGSMTool_var CreateGSMTool
    ( const CATUnicodeString& iName = "", int iSetAsCurrent = 1 , int iTopLevel = 0 , int iType = 0 );
   //CATIGSMTool_var CreateGSMTool
   // ( const CATUnicodeString& iName = "", int iSetAsCurrent = 1 , int iTopLevel = 0 );
   
  /**
   * Retrieve a courrent GSMTool.
   * <br>Note : If no GSMTool found as current a new one is automatically created 
   *   @param iName 
   *      Name of Tool to create 
   *   @param iSetAsCurrent 
   *      =0 not become current GSMtool 
   *      =1 set new GSM tool at current 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */ 
   CATIGSMTool_var GetCurrentGSMTool
   ( const CATUnicodeString& iName = "", int iSetAsCurrent = 1 );

  /**
   * Make a GSM Feature to become visible in the standard CATIA V5 graph editor. 
   *   @param ispObjectToAppend
   *      Object to insert in CATIA V5 graph editor 
   *   @param ispInputFather
   *      Specify the object under which the object to append is insert 
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */
   HRESULT InsertInProceduralView
       ( const CATISpecObject_var& ispObjectToAppend,const CATISpecObject_var& ispInputParent=NULL_var);

  
  /**
   * Update a GSM Feature in order to generate its geometrical representation 
   *   @param ispSpec 
   *      Object to update
   *   @return
   *      S_OK if OK, E_FAIL if fail

   */
  HRESULT ObjectUpdate    (const CATISpecObject_var & ispSpec);

  
  //  Litteral 
  // -------------------------------

  /**
   * Create a Length Cke paramater for GSM Features 
   *   @param ipNameParam 
   *      Naming Cke parameter 
   *   @param iValue 
   *      Value associate to the parameter 
   *   @param ospCkeParam 
   *      Cke parameter return as a  CATISpecObject_var   
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */

  HRESULT CreateLength  (const char* ipNameParam ,const double iValue, CATISpecObject_var &ospCkeParam);
  /**
   * Create an angle  Cke paramater for GSM Features 
   *   @param ipNameParam 
   *      Naming Cke parameter 
   *   @param iValue 
   *      Value associate to the parameter 
   *   @param ospCkeParam 
   *      Cke parameter return as a  CATISpecObject_var   
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */
  HRESULT CreateAngle   (const char* ipNameParam ,const double iValue, CATISpecObject_var &ospCkeParam) ;

  /**
   * Create a real cke paramater for GSM Features 
   *   @param ipNameParam 
   *      Naming Cke parameter 
   *   @param iValue 
   *      Value associate to the parameter 
   *   @param ospCkeParam 
   *      Cke parameter return as a  CATISpecObject_var   
   *   @return
   *      S_OK if OK, E_FAIL if fail
   */
  HRESULT CreateReal(const char* ipNameParam ,const double iValue, CATISpecObject_var &ospCkeParam) ;

  // Direction 
  // -------------------------------
  /**
   * Create a direction feature. 
   *   @param ispSpec 
   *      Naming Cke parameter 
   *   @return CATISpecObjects_var 
   *       Created direction.
   */
  CATISpecObject_var CreateDirection(CATISpecObject_var & iSpec);
 
 
   // Point
  // -------------------------------
  /**
   * Create a direction feature. 
   *   @param iaObjectsParam
   *      List of parameter required for creating a Point coordinates feature:
   *      1- X cke param 
   *      2- Y cke param 
   *      3- Z cke param 
   *   @return CATISpecObjects_var 
   *       Created point 
   */
  CATISpecObject_var CreatePointCoord(
					CATLISTV(CATISpecObject_var) &iaObjectsParam);
 
  /**
   * Create a direction feature. 
   *   @param iaObjectsParam
   *      List of parameter required for creating a PointOnCurve feature
   *      1- Curve 
   *      2- Reference Point 
   *      3- Real Parameter for the Curvilign length (between 0. and 1.) 
   *   @return CATISpecObjects_var 
   *       Created point 
   */
  CATISpecObject_var CreatePointOnCurve(
					CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iProx);


  // Line
  // -------------------------------
  /**
   * Create a line ptpt.
   *   @param iaObjectsParam
   *      List of parameter required for creating a line ptpt feature
   *      1- starting gsm point 
   *      2- end gsm point 
   *   @return CATISpecObjects_var 
   *       Created line
   */
  CATISpecObject_var CreateLinePtPt(CATLISTV(CATISpecObject_var) &iaObjectsParam);

  /**
   * Create a line normal to a curve. 
   *   @param iaObjectsParam
   *      List of parameter required for creating a line normal to a curve 
   *      1- Curve Feature 
   *      2- Reference Surface Feature
   *      3- Reference Point 
   *      4- Start Length Parameter
   *      5- End Length Parameter
   *   @return CATISpecObjects_var 
   *       Created line
   */
  CATISpecObject_var CreateLineNormalCrv(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iGeodesic,CATBoolean iOrient);

  // Circle
  // -------------------------------
  /**
   * Create a circle defined by 2 points and a radius 
   *   @param iaObjectsParam
   *      List of parameter required for creating a circle
   *      1- First Point Feature
   *      2- Second Point Feature
   *      3- Reference Surface Feature
   *      4- Radius Length Parameter 
   *   @return CATISpecObjects_var 
   *       Created circle 
   */
  CATISpecObject_var CreateCircle2PointsRad(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iGeodesic,CATBoolean iOrient);

  /**
   * Create a circle defined by a center  and a radius 
   *   @param iaObjectsParam
   *      List of parameter required for creating a circle
   *      1- Center Point Feature
   *      2- Point On Circle Feature
   *      3- Reference Surface Faeture
   *      4- Start Angle Parameter
   *      5- End Angle Parameter
   *   @return CATISpecObjects_var 
   *       Created circle
   */
  CATISpecObject_var CreateCircleCenterRad(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iGeodesic);

  /**
   * Create a circle defined by a center  and a radius 
   *   @param iaObjectsParam
   *      List of parameter required for creating a circle
   *      1- First Point Feature
   *      2- Second Point Feature
   *      3- Third Point Feature
   *   @return CATISpecObjects_var 
   *       Created circle
   */
  CATISpecObject_var CreateCircle3Points(CATLISTV(CATISpecObject_var) &iaObjectsParam);

  // Spline
  // -------------------------------
  /**
   * Create a spline define by n point and its extremity directions.
   *   @param iaObjectsParam
   *      List of imposed points for the Spline
   *   @param ispSpecStart
   *      Direction at the First Point
   *   @param iOrientStart
   *      Sens of the Direction at the first Point
   *   @param ispSpecEnd
   *      Direction at the End Point
   *   @param iOrientEnd
   *      Sens of the Direction at the last Point
   *   @return CATISpecObjects_var 
   *       Created spline 
   */
  CATISpecObject_var CreateSpline(CATLISTV(CATISpecObject_var) &iaObjectsParam,
				 CATISpecObject_var & ispSpecStart,CATBoolean iOrientStart, 
				 CATISpecObject_var & ispSpecEnd  ,CATBoolean iOrientEnd);

  // Plane
  // -------------------------------
  //   CATISpecObject_var CreatePlane3Pts(CATLISTV(CATISpecObject_var) &iaObjectsParam);

  /**
   * Create a plane throuph 3 points.
   *   @param iaObjectsParam
   *      List of parameter required for creating a spline 
   *      1- A Length Parameter 
   *      2- B Length Parameter 
   *      3- C Length Parameter 
   *      4- D Length Parameter 
   *   @return CATISpecObjects_var 
   *       Created plane 
   */
  CATISpecObject_var CreatePlaneEquation(CATLISTV(CATISpecObject_var) &iaObjectsParam);

  /**
   * Create a plane define by a rotation from a reference plane and a direction.
   *   @param iaObjectsParam
   *      List of parameter required for creating a spline 
   *      1- Input Reference Plane
   *      2- Input Axis Line or Direction
   *      3- Rotation Angle Parameter
   *   @return CATISpecObjects_var 
   *       Created plane 
   */
  CATISpecObject_var CreatePlaneAngle(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iOrient);


  // Operators
  // -------------------------------

  /**
   * Create a split.
   *   @param iaObjectsParam
   *      List of parameter required for creating a split 
   *      1- Input Spec to Split
   *      2- Cutting Spec
   *   @return CATISpecObjects_var 
   *       Created split
   */
  CATISpecObject_var CreateSplit(CATLISTV(CATISpecObject_var) &iaObjectsParam,CATBoolean iOrient);

  // Sweep, Loft
  // -------------------------------
  /**
   * Create a sweep define with on guide. 
   *   @param iaObjectsParam
   *      List of parameter required for creating a sweep
   *      1- Guide Curve of the Sweep
   *      2- Profile Curve of the Sweep
   *   @return CATISpecObjects_var 
   *       Created sweep
   */
  CATISpecObject_var CreateSweepOneGuide(CATLISTV(CATISpecObject_var) &iaObjectsParam);
 
  /**
   * Create a loft define by sections guides and a spine
   *   @param iaObjectsParamSections
   *      List of Sections for creating a loft
   *   @param iaObjectsParam
   *      List of Guides for creating a loft
   *   @param ispSpine
   *      Input Spine Curve, could be NULL_var 
   *      in that case this an automatic Spine that is used
   *      for the Loft
   *   @return CATISpecObjects_var 
   *       Created loft 
   */
  CATISpecObject_var CreateLoft(CATLISTV(CATISpecObject_var) &iaObjectsParamSections,
								CATLISTV(CATISpecObject_var) &iaObjectsParamGuides,
								CATISpecObject_var & ispSpine);

  /**
   * Create an Assemble 
   *   @return CATISpecObjects_var 
   *       Created Assemble  
   */
  CATISpecObject_var CreateAssemble(CATLISTV(CATISpecObject_var) & iaObjectsParamAssemble,const double iDev,CATBoolean iConnex);
  

private:
  /**
   * This Pointer is stored in order to Close the Session at the end of any 
   * batch code using CAAGsiUserTools.
   */
  CATSession             * _pSession;

  /**
   * This Pointer is stored in order to Close the Document at the end of any 
   * batch code using CAAGsiUserTools.
   */
  CATDocument            * _pDoc;


  
  /**
   * This pointer allow the class to call at any time
   * the method of the CATIGSMFactory interface.
   */
  CATIGSMFactory         * _pFact;

};
#endif
