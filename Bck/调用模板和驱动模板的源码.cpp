
////ʵ������udf
CATUnicodeString RunInCmd::InitOne(CATUnicodeString strUdfName)
{
	//*********************************************
	//***************��ȡ��ǰ�����Part*******
	//*********************************************
	CATISpecObject_var spPartObject = GetActivePart();
	if (spPartObject==NULL_var)
	{
		cout<<"GetActivePart Failed"<<endl;
		return "GetActivePart Failed";
	}

	CATIPrtPart_var spPrtPart = spPartObject;
	if (spPrtPart==NULL_var)
	{
		cout<<"GetActivePart Failed"<<endl;
		return "GetActivePart Failed";
	}

	//******************************************************
	//***************�����������ü��μ�Ϊ��ǰ��������*******
	//******************************************************
	CATUnicodeString strdesitinationName;//���μ�������
	SetCurrentGeoSet(strdesitinationName);

	//*********************************************
	//***************�ж��Ƿ��Ѿ�ʵ������udf*******
	//*********************************************
	if (isUdfFeatureInstance(strUdfName,spPrtPart))
	{
		return "UdfFeatureInstance";
	}

	//���ĵ����������(�ĵ�����ҳ�ˣ�����5�Σ�ʧ���򷵻�)
	//******************************************************
	//***************��UDF�ĵ�*******
	//******************************************************
	CATDocument *pUdfDoc = NULL;
	int trytimes=5;
	CATUnicodeString strDocumentPath;
	OpenDocument(strDocumentPath,trytimes,pUdfDoc);
	if(pUdfDoc==NULL)
		return "OpenDocument Failed";

	//�����ĵ�
	CATLockDocument(*pUdfDoc);

	CATInit *pInitOnDoc = NULL ;
	pUdfDoc->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
	if (pInitOnDoc==NULL)
	{
		cout<<"QI CATInit Failed"<<endl;
		return "QI CATInit Failed";
	}

	//��ȡCATIPrtContainer
	CATIPrtContainer *piPrtCont = NULL ;
	piPrtCont = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");
	if(piPrtCont==NULL)
	{
		cout<<"execution error, reason: file type is not CATPart"<<endl;
		return "execution error, reason: file type is not CATPart";
	}

	//��ȡCATIPrtPart
	CATISpecObject_var  spudfPartObject= piPrtCont->GetPart();
	if (spudfPartObject==NULL_var)
	{
		cout<<"GetPart Failed"<<endl;
		return "GetPart Failed";
	}

	CATIPrtPart_var  spUdfPart=spudfPartObject;
	if (spUdfPart==NULL_var)
	{
		cout<<"GetPrtPart Failed"<<endl;
		return "GetPrtPart Failed";
	}

	//��ȡCATIUdfFactory
	CATIUdfFactory *pIUdfFactory = NULL ;
	piPrtCont->QueryInterface(IID_CATIUdfFactory,(void **) &pIUdfFactory);
	if (pIUdfFactory==NULL)
	{
		cout<<"Get CATIUdfFactory Failed"<<endl;
		return "Get CATIUdfFactory Failed";
	}

	//��ȡUdf �������б�
	CATListValCATISpecObject_var* lstUdfs = NULL;
	CATListValCATISpecObject_var* lstPcs = NULL;
	lstUdfs = pIUdfFactory->GetUserFeatureList();
	lstPcs = pIUdfFactory->GetPowerCopyList();

	//int length=strUdfName.GetLengthInChar();

	CATListValCATISpecObject_var lstNeed;
	lstNeed.RemoveAll();

	//UDF��PowerCopy
	if(lstUdfs!=NULL)
		for(int ii=1;ii<=lstUdfs->Size();ii++)
			lstNeed.Append((*lstUdfs)[ii]);

	if(lstPcs!=NULL)
		for(int ii=1;ii<=lstPcs->Size();ii++)
			lstNeed.Append((*lstPcs)[ii]);

	CATIAlias_var spAlias=NULL_var;
	//*********************************************
	//***************��������ѭ������udf*********************
	//*********************************************
	CATIUdfInstantiate_var spUdfIni=NULL_var;
	for(int ii =1;ii<=lstNeed.Size();ii++)
	{
		spAlias = lstNeed[ii];

		CATUnicodeString strName = spAlias->GetAlias();

		//int length=strName.GetLengthInChar();

		if(strName==strUdfName)
		{
			spUdfIni=lstNeed[ii];
			break;
		}
	}

	//*********************************************
	//***************ʵ����udf*********************
	//*********************************************
	CATPathElement PathFirstInstantiate1(spPrtPart); 

	//��UDFʵ��������ǰ������ĵ�
	CATPathElement * FirstUIactiveObject1 = NULL ;
	CATBaseUnknown_var FirstDest1 = NULL_var ; 
	rc = spUdfIni->SetDestinationPath(&PathFirstInstantiate1,FirstUIactiveObject1,FirstDest1);
	if ( FAILED(rc) )
	{
		cout<<"execution error, reason: there is error when executing SetDestinationPath"<<endl;
		return "execution error, reason: there is error when executing SetDestinationPath";
	}

	CATTry
	{
		spPartObject->Update();
	}
	CATCatch(CATError,error)
	{
	}
	CATEndTry;

	//�޸�udf������

	//*********************************************
	//***************���UDF������*********************
	//*********************************************
	CATListOfCATUnicodeString * pListOfInputRole = NULL ;//UDF����Ԫ�ص�����
	CATListValCATBaseUnknown_var * pListOfInput = NULL  ;//UDF����Ԫ��
	rc = spUdfIni->GetOldInputs(pListOfInput,pListOfInputRole);
	if ( FAILED(rc) || ( NULL ==pListOfInput ) || ( NULL== pListOfInputRole ) )
	{
		//������
		return "GetOldInputs Failed";
	}
	else
	{
		CATUnicodeString strNotValue,strNotInput;
		for(int ii=1;ii<=pListOfInputRole->Size();ii++)
		{
			//*********************************************
			//***************�жϸ��ĵ����Ƿ��д�����******
			//*********************************************
			CATUnicodeString strParaName=(*pListOfInputRole)[ii];

			//���UDF������Ԫ�ص�·��(�жϵ�ǰ�����ĵ����Ƿ�����ͬ���ƵĲ���)
			CATPathElement* pInput = GetUdfInput(strParaName);//�������Ʋ����������

			CATICkeParm_var spPar = (*pListOfInput)[ii];//��������
			if(pInput==NULL)
			{
				if(spPar!=NULL_var)
				{
					//********************************************************
					//***************���ĵ���û�д�����,��Ϊ���������½�******
					//********************************************************
					CATIType_var spType = spPar->Type();
					CATUnicodeString strType =spType->Name();
					if(strType!="Surface"&&strType!="Plane"&&strType!="Curve"&&strType!="Line"&&strType!="Point")
					{
						//������ΪSurface��Plane��Curve��Line��Point����������

						//****************************
						//**************�½�����******
						//****************************
						pInput = CreateUdfParamterInput((*pListOfInputRole)[ii],spPar,spExternalParamSet,spiParamSetpredecessors);
						if(pInput==NULL)
						{
							cout<<"udf input element is  parameter and not create sucess or not find parameter value in list"<<endl;

							if(strNotValue!="")
								strNotValue+=",";
							strNotValue=strNotValue+strParaName;
						}
						else
						{
							//�����µ�����
							rc=spUdfIni->SetNewInput(ii,pInput);
							if (FAILED(rc))
							{
								cout<<strParaName<<"--->"<<"SetNewInput Failed"<<endl;
							}

						}

					}
					else
					{
						cout<<"udf input element is not parameter and not find"<<endl;

						if(strNotInput!="")
							strNotInput+=",";
						strNotInput=strNotInput+strParaName;
					}
				}
				else
				{
					if(strNotInput!="")
						strNotInput+=",";
					strNotInput=strNotInput+strParaName;

				}
			}
			else
			{
				//********************************************************
				//***************�����µ�����******
				//********************************************************
				rc=spUdfIni->SetNewInput(ii,pInput);
				if (FAILED(rc))
				{
					cout<<strParaName<<"<--->"<<"SetNewInput Failed"<<endl;
				}
			}

			if (NULL!=pInput)
			{
				pInput->Release();
				pInput=NULL;
			}
		}


	}

	CATUnLockDocument(*pUdfDoc);

	return ;

}
