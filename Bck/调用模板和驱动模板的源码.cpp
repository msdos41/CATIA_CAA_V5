
////实例化的udf
CATUnicodeString RunInCmd::InitOne(CATUnicodeString strUdfName)
{
	//*********************************************
	//***************获取当前激活的Part*******
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
	//***************根据名称设置几何集为当前工作对象*******
	//******************************************************
	CATUnicodeString strdesitinationName;//几何集的名称
	SetCurrentGeoSet(strdesitinationName);

	//*********************************************
	//***************判断是否已经实例化此udf*******
	//*********************************************
	if (isUdfFeatureInstance(strUdfName,spPrtPart))
	{
		return "UdfFeatureInstance";
	}

	//打开文档，尝试五次(文档在网页端，尝试5次，失败则返回)
	//******************************************************
	//***************打开UDF文档*******
	//******************************************************
	CATDocument *pUdfDoc = NULL;
	int trytimes=5;
	CATUnicodeString strDocumentPath;
	OpenDocument(strDocumentPath,trytimes,pUdfDoc);
	if(pUdfDoc==NULL)
		return "OpenDocument Failed";

	//锁定文档
	CATLockDocument(*pUdfDoc);

	CATInit *pInitOnDoc = NULL ;
	pUdfDoc->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
	if (pInitOnDoc==NULL)
	{
		cout<<"QI CATInit Failed"<<endl;
		return "QI CATInit Failed";
	}

	//获取CATIPrtContainer
	CATIPrtContainer *piPrtCont = NULL ;
	piPrtCont = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");
	if(piPrtCont==NULL)
	{
		cout<<"execution error, reason: file type is not CATPart"<<endl;
		return "execution error, reason: file type is not CATPart";
	}

	//获取CATIPrtPart
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

	//获取CATIUdfFactory
	CATIUdfFactory *pIUdfFactory = NULL ;
	piPrtCont->QueryInterface(IID_CATIUdfFactory,(void **) &pIUdfFactory);
	if (pIUdfFactory==NULL)
	{
		cout<<"Get CATIUdfFactory Failed"<<endl;
		return "Get CATIUdfFactory Failed";
	}

	//获取Udf 的特征列表
	CATListValCATISpecObject_var* lstUdfs = NULL;
	CATListValCATISpecObject_var* lstPcs = NULL;
	lstUdfs = pIUdfFactory->GetUserFeatureList();
	lstPcs = pIUdfFactory->GetPowerCopyList();

	//int length=strUdfName.GetLengthInChar();

	CATListValCATISpecObject_var lstNeed;
	lstNeed.RemoveAll();

	//UDF和PowerCopy
	if(lstUdfs!=NULL)
		for(int ii=1;ii<=lstUdfs->Size();ii++)
			lstNeed.Append((*lstUdfs)[ii]);

	if(lstPcs!=NULL)
		for(int ii=1;ii<=lstPcs->Size();ii++)
			lstNeed.Append((*lstPcs)[ii]);

	CATIAlias_var spAlias=NULL_var;
	//*********************************************
	//***************根据名称循环查找udf*********************
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
	//***************实例化udf*********************
	//*********************************************
	CATPathElement PathFirstInstantiate1(spPrtPart); 

	//将UDF实例化到当前激活的文档
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

	//修改udf的输入

	//*********************************************
	//***************获得UDF的输入*********************
	//*********************************************
	CATListOfCATUnicodeString * pListOfInputRole = NULL ;//UDF输入元素的名称
	CATListValCATBaseUnknown_var * pListOfInput = NULL  ;//UDF输入元素
	rc = spUdfIni->GetOldInputs(pListOfInput,pListOfInputRole);
	if ( FAILED(rc) || ( NULL ==pListOfInput ) || ( NULL== pListOfInputRole ) )
	{
		//无输入
		return "GetOldInputs Failed";
	}
	else
	{
		CATUnicodeString strNotValue,strNotInput;
		for(int ii=1;ii<=pListOfInputRole->Size();ii++)
		{
			//*********************************************
			//***************判断该文档下是否有此输入******
			//*********************************************
			CATUnicodeString strParaName=(*pListOfInputRole)[ii];

			//获得UDF的输入元素的路径(判断当前激活文档下是否有相同名称的参数)
			CATPathElement* pInput = GetUdfInput(strParaName);//根据名称查找输入参数

			CATICkeParm_var spPar = (*pListOfInput)[ii];//参数类型
			if(pInput==NULL)
			{
				if(spPar!=NULL_var)
				{
					//********************************************************
					//***************该文档下没有此输入,若为参数，则新建******
					//********************************************************
					CATIType_var spType = spPar->Type();
					CATUnicodeString strType =spType->Name();
					if(strType!="Surface"&&strType!="Plane"&&strType!="Curve"&&strType!="Line"&&strType!="Point")
					{
						//参数不为Surface，Plane，Curve，Line，Point，创建参数

						//****************************
						//**************新建参数******
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
							//设置新的输入
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
				//***************设置新的输入******
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
