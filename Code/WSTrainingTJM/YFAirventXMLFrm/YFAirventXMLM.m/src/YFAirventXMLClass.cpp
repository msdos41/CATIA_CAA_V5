
#include "YFAirventXMLClass.h"

//---------------------------------------------------------
YFAirventXMLClass::YFAirventXMLClass()
{
	m_pDoc = new TiXmlDocument();
}
//---------------------------------------------------------
YFAirventXMLClass::~YFAirventXMLClass()
{
	if (m_pDoc != NULL)
	{
		delete m_pDoc;
		m_pDoc = NULL;
	}
}
//---------------------------------------------------------
bool YFAirventXMLClass::OpenXmlFile(const char *filePath)
{
	m_pDoc->LoadFile(filePath);

	if (m_pDoc->Error())
	{
		int nError = m_pDoc->ErrorId();
		std::cout << m_pDoc->ErrorDesc();
		return false;
	}

	return true;
}
//---------------------------------------------------------
TiXmlElement *YFAirventXMLClass::GetRootElement()
{
	return m_pDoc->RootElement();
}
//---------------------------------------------------------
TiXmlElement *YFAirventXMLClass::GetChildElement(TiXmlElement *pParentElement, const char *title)
{
	if (pParentElement != NULL)
	{
		TiXmlNode *childNode = GetFirstChildElement(pParentElement);
		for (; childNode; childNode = GetNextChildElement(childNode->ToElement()))
		{
			if (!strcmp(title, childNode->Value()))
			{
				return childNode->ToElement();
			}
		}
	}

	return NULL;
}
//---------------------------------------------------------
TiXmlElement *YFAirventXMLClass::GetFirstChildElement(TiXmlElement *pParentElement)
{
	if (pParentElement != NULL)
	{
		TiXmlElement *child = pParentElement->FirstChildElement();
		return child;
	}

	return NULL;
}
//---------------------------------------------------------
TiXmlElement *YFAirventXMLClass::GetNextChildElement(TiXmlElement *pElement)
{
	if (pElement != NULL)
	{
		TiXmlElement *nextChild = pElement->NextSiblingElement();
		return nextChild;
	}

	return NULL;
}
//---------------------------------------------------------
const char * YFAirventXMLClass::GetElementValue(TiXmlElement *pElement)
{
	const char * result = NULL;
	if (pElement != NULL)
	{
		result = pElement->GetText();
	}

	return result;
}
//---------------------------------------------------------
const char * YFAirventXMLClass::GetElementAttributeValue(TiXmlElement *pElement, const char *pAttributeName)
{
	const char * reslut = NULL;
	if (pElement != NULL)
	{
		reslut = pElement->Attribute(pAttributeName); 
	}
	return reslut; 
}
//---------------------------------------------------------
const char * YFAirventXMLClass::GetChildElementValue(TiXmlElement *pParentElement, const char *title)
{
	const char * reslut = NULL;
	if(pParentElement != NULL)
	{
		TiXmlElement * pElem = GetChildElement(pParentElement,title);
		if (pElem != NULL)
		{
			reslut = GetElementValue(pElem);
		}	
	}
	return reslut;
}
//---------------------------------------------------------
const char * YFAirventXMLClass::GetChildElementAttributeValue(TiXmlElement *pParentElement, const char *title, const char *AttributeName)
{
	const char * reslut = NULL;
	if (pParentElement != NULL)
	{
		TiXmlElement * pElem = GetChildElement(pParentElement,title);
		if (pElem != NULL)
		{
			reslut = GetElementAttributeValue(pElem,AttributeName);
		}
	}
	return reslut;
}
//---------------------------------------------------------
void YFAirventXMLClass::Clear()
{
	m_pDoc->Clear();
}
//---------------------------------------------------------
TiXmlElement *YFAirventXMLClass::AddXmlRootElement(const char *title)
{
	TiXmlElement *element = new TiXmlElement(title);
	m_pDoc->LinkEndChild(element);
	return element;
}
//---------------------------------------------------------
TiXmlElement *YFAirventXMLClass::AddXmlChildElement(TiXmlElement *pParentElement, const char *title, const char *value)
{
	if (pParentElement != NULL)
	{
		TiXmlElement *childElem = new TiXmlElement(title);
		pParentElement->LinkEndChild(childElem);
		if (value != "\0")
		{
			AddElementValue(childElem, value);
		}
		return childElem;
	}
	return NULL;
}
//---------------------------------------------------------
void YFAirventXMLClass::AddXmlAttribute(TiXmlElement *pElement, const char *name, const char *value)
{
	if (pElement != NULL)
	{
		pElement->SetAttribute(name, value);
	}
}
//---------------------------------------------------------
void YFAirventXMLClass::AddXmlDeclaration(const char* vesion,const char* encoding,const char* standalone)
{
	TiXmlDeclaration *decl = new TiXmlDeclaration(vesion, encoding, standalone);
	m_pDoc->LinkEndChild(decl);
}
//---------------------------------------------------------
void YFAirventXMLClass::AddElementValue(TiXmlElement *pElement,const char* value) 
{ 
	if(pElement != NULL) 
	{ 
		TiXmlText * text =new TiXmlText(value); 
		pElement->LinkEndChild(text); 
	} 
} 
//---------------------------------------------------------
void YFAirventXMLClass::AddXmlComment(TiXmlElement* pElement,const char* Comment)
{
	if (pElement != NULL)
	{
		TiXmlComment *comment = new TiXmlComment(Comment);
		pElement->LinkEndChild(comment);
	}
}
//---------------------------------------------------------
bool YFAirventXMLClass::ReplaceElementValue(TiXmlElement* pElement,const char * newValue)
{
	if (pElement != NULL)
	{
		TiXmlNode * oldNode = NULL;
		oldNode = pElement->FirstChild();
		if (oldNode != NULL)
		{
			TiXmlText newText(newValue);
			pElement->ReplaceChild(oldNode,newText);
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------
bool YFAirventXMLClass::ReplaceElementAttribute(TiXmlElement* pElement,const char * name,const char * newValue)
{
	if (pElement != NULL)
	{
		TiXmlAttribute * oldAttribute = NULL;
		oldAttribute = pElement->FirstAttribute();
		for(;oldAttribute != NULL;oldAttribute = oldAttribute->Next())
		{
			if (!strcmp(name,oldAttribute->Name()))
			{
				oldAttribute->SetValue(newValue);
			}
		}
	}
	return false;
}
//---------------------------------------------------------
void YFAirventXMLClass::SaveFile(const char *filePath)
{
	m_pDoc->SaveFile(filePath);
}
//---------------------------------------------------------
TiXmlElement *YFAirventXMLClass::FindFirstElement(const char * title)
{
	if (title == "\0")
	{
		return 0;
	}
	TiXmlElement *pElem = NULL;
	pElem = GetRootElement();
	pElem = FindFirstElement(pElem, title);
	return pElem;
}
//---------------------------------------------------------
TiXmlElement *YFAirventXMLClass::FindFirstElement(TiXmlElement *pcrElement, const char *title)
{
	TiXmlNode *pNode = pcrElement;
	while(pNode)
	{
		if (strcmp(pNode->Value(), title) == 0)
		{
			return pNode->ToElement();
		}
		else
		{
			TiXmlNode *nextElement = pNode->FirstChildElement();
			while(nextElement)
			{
				if(strcmp(nextElement->Value(),title)==0)
				{
					return nextElement->ToElement();
				}
				else
				{
					TiXmlElement* reElement = NULL;
					reElement = FindFirstElement(nextElement->ToElement(),title);
					if(reElement)
					{
						return reElement;
					}
				}
				nextElement = nextElement->NextSiblingElement();
			}
		}
		pNode = pNode->NextSiblingElement();
	}
	return NULL;
}
//---------------------------------------------------------

