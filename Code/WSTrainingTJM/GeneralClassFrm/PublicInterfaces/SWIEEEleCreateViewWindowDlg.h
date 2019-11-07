#ifndef SWIEEEleCreateViewWindowDlg_h
#define SWIEEEleCreateViewWindowDlg_h

//#include "SWIEEEleViewWindowM.h"
#include "GeneralClassMod.h"
#include "CATDlgDialog.h"
#include "CATDlgDocument.h"
#include "CATVisManager.h"
#include "CATViewpoint.h"
#include "CATFrmEditor.h"
#include "CATI3DGeoVisu.h"
#include "CATFrmEditor.h"
#include "CATNavigBox.h"
#include "CATNavigController.h"
#include "CATHSO.h"
#include "CATIGraphNode.h"
#include "CATINavigElement.h"
#include "CATINavigateObject.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATPSO.h"
#include "CATHSO.h"
#include "CATISO.h"
#include "CATFrmWindow.h"

#include "CATApplicationFrame.h"




// Dialog Framework
class CATInteractiveApplication; // Application kept in data member

// Visualization Framework
class CAT3DBagRep ;               
class CATNavigation3DViewer;

class ExportedByGeneralClassMod SWIEEEleCreateViewWindowDlg: public CATDlgDialog
{
	DeclareResource(SWIEEEleCreateViewWindowDlg, CATDlgDialog)

  public:

	  SWIEEEleCreateViewWindowDlg(CATDialog* iParent, const CATString& iName,CATBaseUnknown_var spViewOccurrence);

	  virtual ~SWIEEEleCreateViewWindowDlg();

	  void     Build();

	  HRESULT GetNavigBox(CATNavigController *&pNavigController,CATNavigBox *&pNavigBox);

	  void ExpandCollapseNode(CATNavigController *pNavigController,CATBaseUnknown_var iObject);

	  void ExpandAllNode(CATNavigController *pNavigController,CATBaseUnknown_var iRootObject,CATBaseUnknown_var iExpendObject);


private:

	void CreateViewer();

	void CreateModelRepresentation();

	void VisualizeModel();

	void Close(CATCommand* iSendingCommand, 
		CATNotification    * iSentNotification, 
		CATCommandClientData iUsefulData);

	HRESULT CreateNavigBox(CATDialog *iDialog);

	void DeleteWindow();

	SWIEEEleCreateViewWindowDlg (SWIEEEleCreateViewWindowDlg &);
	SWIEEEleCreateViewWindowDlg& operator=(SWIEEEleCreateViewWindowDlg&);


  private:

    CATInteractiveApplication * _pApplication;

    CAT3DBagRep               * _p3DBagRep ;

    CATNavigation3DViewer     * _p3DViewer ;

	CATBaseUnknown_var _spViewOccurrence;

	CATNavigController *_pNavigController;

	CATNavigBox *_pNavigBox;
    
};
#endif

