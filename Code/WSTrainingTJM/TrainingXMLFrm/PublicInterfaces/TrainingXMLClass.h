
#ifndef TrainingXMLClass_H
#define TrainingXMLClass_H

#include "TrainingXMLM.h"

#include <iostream>
#include "tinyxml.h"

class ExportedByTrainingXMLM TrainingXMLClass
{
public:

	TrainingXMLClass ();

	virtual ~TrainingXMLClass ();

private:

	TrainingXMLClass (TrainingXMLClass &);

	TrainingXMLClass& operator=(TrainingXMLClass&);

public:

	void Clear();

	bool OpenXmlFile(const char *filePath);

	void SaveFile(const char *filePath);

	TiXmlElement *FindFirstElement(const char * title);

	TiXmlElement *GetChildElement(TiXmlElement *pParentElement, const char *title);

	TiXmlElement *GetFirstChildElement(TiXmlElement *pParentElement);

	TiXmlElement *GetNextChildElement(TiXmlElement *pElement);

	TiXmlElement *GetRootElement();

	const char * GetChildElementValue(TiXmlElement *pParentElement, const char *title);

	const char * GetChildElementAttributeValue(TiXmlElement *pParentElement, const char *title, const char *AttributeName);

	const char * GetElementValue(TiXmlElement *pElement);

	const char * GetElementAttributeValue(TiXmlElement *pElement, const char *pAttributeName);

	void AddElementValue(TiXmlElement * pElement,const char* value); 

	void AddXmlAttribute(TiXmlElement *pElement, const char *name, const char *value);

	TiXmlElement *AddXmlChildElement(TiXmlElement *pParentElement, const char *title, const char *value = "\0");

	void AddXmlComment(TiXmlElement* pElement,const char* Comment);

	void AddXmlDeclaration(const char* vesion="1.0",const char* encoding="gb2312",const char* standalone=""); 

	TiXmlElement *AddXmlRootElement(const char *title);

	bool ReplaceElementValue(TiXmlElement * pElement,const char * newValue);

	bool ReplaceElementAttribute(TiXmlElement* pElement,const char * name,const char * newValue);

private:

	TiXmlElement *FindFirstElement(TiXmlElement* pcrElement,const char * title);

private:

	TiXmlDocument *m_pDoc;

};

//-----------------------------------------------------------------------

#endif
