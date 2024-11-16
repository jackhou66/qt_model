#include "XMLFile.h"

XMLFile::XMLFile(const char *xmlFileName)
{
	m_xmlFileName = new char[100];
	strcpy(m_xmlFileName, xmlFileName);
	m_pDocument = nullptr;
	//	m_pDeclaration = nullptr;
}

XMLFile::~XMLFile()
 {
	if (m_xmlFileName != nullptr)
		delete m_xmlFileName;

	if (m_pDocument != nullptr)
		delete m_pDocument;

	//if (m_pDeclaration != nullptr)
	//{
	//	delete m_pDeclaration;
	//}
}
void XMLFile::createEntityXML(entityViewItemList & children, TiXmlElement& pRoot)
{
	if (children.size()>0)
	{
		TiXmlElement *pEntity = new TiXmlElement("Entity");
		if (NULL == pEntity)
		{
			return;
		}
		for (int i = 0; i <children.size(); ++i)
		{
			//�������ӽڵ�
			pEntity->SetAttribute("EntityId", (children[i]->EntityId).toInt());
			pEntity->SetAttribute("PlantType", (int)(children[i]->plantType));
			pEntity->SetAttribute("armyType", (int)(children[i]->armyType));
			pEntity->SetAttribute("devicetype", (int)(children[i]->devicetype));
			pEntity->SetAttribute("name", (children[i]->name).toInt());
			pEntity->SetAttribute("isGroup", (children[i]->isGroup).toInt());
			//�������ڵ㣬��Ϊ���ڵ�ĺ��ӽڵ�
			if (children[i]->children.size()>0)
			{
				createEntityXML(children[i]->children, *pEntity);
			}
			if (children[i]->parameter.ParameterId == "1")
			{
				TiXmlElement *Parameter = new TiXmlElement("Parameter");
				Parameter->SetAttribute("ParameterId", children[i]->parameter.ParameterId.toInt());
				Parameter->SetAttribute("devicetype", (int)children[i]->parameter.devicetype);
				Parameter->SetAttribute("Azimuth", children[i]->parameter.Azimuth.toInt());
				Parameter->SetAttribute("Pitch", children[i]->parameter.Pitch.toInt());//parameter.name 
				Parameter->SetAttribute("name", children[i]->parameter.name.toInt());
				pEntity->LinkEndChild(Parameter);
			}
		}
		pRoot.LinkEndChild(pEntity);
	}
	else
	{
		return;
	}

}
void XMLFile::createXML(const entityViewItemList& mItemList)
{
	entityViewItemList fli=mItemList;

	//����XML�ĵ�ָ��
	m_pDocument = new TiXmlDocument(m_xmlFileName);
	if (NULL == m_pDocument)
	{
		return;
	}
	//����XML
	TiXmlDeclaration* m_pDeclaration;
	m_pDeclaration = new TiXmlDeclaration("1.0", "UTF-8", "");
	if (NULL == m_pDeclaration)
	{
		return;
	}
	m_pDocument->LinkEndChild(m_pDeclaration);

	//�������ڵ�
	string xmlFileName = m_xmlFileName;
	string rootName = (xmlFileName.substr(0, xmlFileName.find(".")));//���ڵ�Ԫ����Ϊ�ļ���ȥ��.xml     yuan StuInfo.xml  <StuInfo>Student biao

	//����XML�ĵ�����ΪXML�ĵ��ĸ��ڵ�

	for (int k = 0; k < fli.size(); ++k)
	{
		TiXmlElement *pRoot = new TiXmlElement(rootName.c_str());
		if (NULL == pRoot)
		{
			return;
		}
		m_pDocument->LinkEndChild(pRoot);
		if ((fli[k]->parentEntity) != nullptr)  //���ø��ڵ������
		{
			if (k==0)
			{
				pRoot->SetAttribute("ArmyType", (int)fli[k]->armyType);
				pRoot->SetAttribute("PlantType", (int)fli[k]->plantType);
				pRoot->SetAttribute("devicetype", (int)fli[k]->devicetype);
				pRoot->SetAttribute("name", fli[k]->name.toInt());
			}
			if (k == 1)
			{
				pRoot->SetAttribute("ArmyType", (int)fli[k]->armyType);
				pRoot->SetAttribute("PlantType", (int)fli[k]->plantType);
				pRoot->SetAttribute("devicetype", (int)fli[k]->devicetype);
				pRoot->SetAttribute("name", fli[k]->name.toInt());
			}

		}
		createEntityXML(fli[k]->children, *pRoot);
	}
	m_pDocument->SaveFile(m_xmlFileName);
}
	////����XML�ĵ�ָ��
	//m_pDocument = new TiXmlDocument(m_xmlFileName);
	//if (NULL == m_pDocument)
	//{
	//	return;
	//}
	////����XML
	//TiXmlDeclaration* m_pDeclaration;
	//m_pDeclaration = new TiXmlDeclaration("1.0", "UTF-8", "");
	//if (NULL == m_pDeclaration)
	//{
	//	return;
	//}
	//m_pDocument->LinkEndChild(m_pDeclaration);

	////�������ڵ�
	//string xmlFileName = m_xmlFileName;
	//string rootName = (xmlFileName.substr(0, xmlFileName.find(".")));//���ڵ�Ԫ����Ϊ�ļ���ȥ��.xml     yuan StuInfo.xml  <StuInfo>Student biao
	//TiXmlElement *pRoot = new TiXmlElement(rootName.c_str());
	//if (NULL == pRoot)
	//{
	//	return;
	//}
	////����XML�ĵ�����ΪXML�ĵ��ĸ��ڵ�
	//m_pDocument->LinkEndChild(pRoot);
 //
	//pRoot->SetAttribute("ArmyType", 1);
	//pRoot->SetAttribute("PlantType", 1);
	//pRoot->SetAttribute("devicetype", 1);

	////�������ӽڵ�
	//TiXmlElement *pEntity = new TiXmlElement("Entity");
	//if (NULL == pEntity)
	//{
	//	return;
	//}
	//pEntity->SetAttribute("EntityId", 1);
	//pEntity->SetAttribute("PlantType", 1);
	//pEntity->SetAttribute("armyType", 1);
	//pEntity->SetAttribute("devicetype", 1);

	//TiXmlElement *pEntity1 = new TiXmlElement("Entity");
	//if (NULL == pEntity)
	//{
	//	return;
	//}
	//pEntity1->SetAttribute("EntityId", 1);
	//pEntity1->SetAttribute("PlantType", 1);
	//pEntity1->SetAttribute("armyType", 1);
	//pEntity1->SetAttribute("devicetype", 1);

	//TiXmlElement *Parameter = new TiXmlElement("Parameter");
	//Parameter->SetAttribute("ParameterId", 1);
	//Parameter->SetAttribute("devicetype", 1);
	//Parameter->SetAttribute("Azimuth", 1);
	//Parameter->SetAttribute("Pitch", 1);
 //
	//pEntity1->LinkEndChild(Parameter);
	//pEntity->LinkEndChild(pEntity1);

	////�������ڵ㣬��Ϊ���ڵ�ĺ��ӽڵ�
	//pRoot->LinkEndChild(pEntity);
	//m_pDocument->SaveFile(m_xmlFileName);
	//TiXmlElement *EntityId = new TiXmlElement("EntityId");//����
	//TiXmlText *SoderText = new TiXmlText("1");//�������id
	//EntityId->LinkEndChild(SoderText);

	//TiXmlElement *PlantType = new TiXmlElement("PlantType");
	//TiXmlText *PlantTypeText = new TiXmlText("0");
	//PlantType->LinkEndChild(PlantTypeText);
	//
	//TiXmlElement *armyType = new TiXmlElement("armyType");
	//TiXmlText *armyTypeText = new TiXmlText("1");
	//armyType->LinkEndChild(armyTypeText);
	//
	//TiXmlElement *deviceType = new TiXmlElement("devicetype");
	//TiXmlText *deviceTypeText = new TiXmlText("1");
	//deviceType->LinkEndChild(deviceTypeText);

	////��������
	//TiXmlElement *Parameter = new TiXmlElement("Parameter");
	//TiXmlText *ParameterTypeText = new TiXmlText("1");
	//Parameter->LinkEndChild(ParameterTypeText);
	//deviceType->LinkEndChild(Parameter);


	//TiXmlElement *name = new TiXmlElement("name");
	//TiXmlText *nameText = new TiXmlText("RadJam1");
	//name->LinkEndChild(nameText);

	//TiXmlElement *mode2D = new TiXmlElement("Mode2D");
	//TiXmlText *mode2DText = new TiXmlText("kuku16");
	//mode2D->LinkEndChild(mode2DText);

	//�ӽڵ�
	/*TiXmlElement *mode2D = new TiXmlElement("Mode2D");
	TiXmlText *mode2DText = new TiXmlText("kuku16");
	mode2D->LinkEndChild(mode2DText);*/
 
//��ȡXML�ļ���������   ��ȡ�����ļ���·��
void XMLFile::ReadXML()
{
	TiXmlDocument* m_pDocument = new TiXmlDocument(m_xmlFileName);
	if (m_xmlFileName == NULL)
	{
		cout << " null " << endl;
		return;
	}
	m_pDocument->LoadFile(m_xmlFileName);
	//m_pDocument->Print();
}

//��ȡXML���������磺<?xml version="1.0" encoding="UTF-8" ?>   m_pDeclaration  ����  
void XMLFile::ReadDeclaration(string &version, string &encoding, string &standalone)
{
	TiXmlDocument* m_pDocument = new TiXmlDocument(m_xmlFileName);

	m_pDocument->LoadFile(m_xmlFileName);

	TiXmlNode *pNode = m_pDocument->FirstChild();
	if (nullptr != pNode)
	{
		//��ȡ����ָ��
		TiXmlDeclaration* m_pDeclaration;
		m_pDeclaration = pNode->ToDeclaration();

		if (nullptr != m_pDeclaration)
		{
			version = m_pDeclaration->Version();
			encoding = m_pDeclaration->Encoding();
			standalone = m_pDeclaration->Standalone();
		}
	}
}

//���ݽڵ������жϽڵ��Ƿ����
bool XMLFile::FindNode(TiXmlElement *pRoot, const string nodeName, TiXmlElement *&pNode)
{
	const char *value = pRoot->Value();
	if (strcmp(pRoot->Value(), nodeName.c_str()) == 0)
	{
		pNode = pRoot;
		return true;
	}

	TiXmlElement *p = pRoot;
	for (p = p->FirstChildElement(); p != NULL; p = p->NextSiblingElement())
	{
		FindNode(p, nodeName, pNode);
		return true;
	}

	return false;
}

//���ݽڵ�������ȡ�ýڵ��ı�
bool XMLFile::GetNodeText(const string nodeName, const char *&text)
{
	TiXmlDocument* m_pDocument = new TiXmlDocument(m_xmlFileName);
	m_pDocument->LoadFile(m_xmlFileName);
	if (NULL == m_pDocument)
	{
		return false;
	}

	TiXmlElement *pRoot = m_pDocument->RootElement();
	const char *value = pRoot->Value();
	if (NULL == pRoot)
	{
		return false;
	}

	TiXmlElement *pNode = NULL;
	if (FindNode(pRoot, nodeName, pNode))
	{
		text = pNode->GetText();
		return true;
	}

	return false;
}

//��ȡ���ݽڵ����� ��ȡ�ڵ�����
bool XMLFile::GetNodeAttribute(const string nodeName, map<string, string> &mapAttribute)
{
	TiXmlDocument* m_pDocument = new TiXmlDocument(m_xmlFileName);
	m_pDocument->LoadFile(m_xmlFileName);
	if (NULL == m_pDocument)
	{
		return false;
	}

	TiXmlElement *pRoot = m_pDocument->RootElement();
	if (NULL == pRoot)
	{
		return false;
	}

	TiXmlElement *pNode = NULL;
	if (FindNode(pRoot, nodeName, pNode))
	{
		TiXmlAttribute *pAttr = NULL;
		for (pAttr = pNode->FirstAttribute(); pAttr != NULL; pAttr = pAttr->Next())
		{
			string name = pAttr->Name();
			string value = pAttr->Value();
			mapAttribute.insert(make_pair(name, value));
		}

		return true;
	}

	return false;
}

//ɾ���ڵ�
bool XMLFile::DeleteNode(const string nodeName)
{
	m_pDocument->LoadFile(m_xmlFileName);

	TiXmlElement *pRoot = m_pDocument->RootElement();
	if (NULL == pRoot)
	{
		return false;
	}

	TiXmlElement *pNode = NULL;
	if (FindNode(pRoot, nodeName, pNode))
	{
		if (pNode == pRoot)
		{//����Ǹ��ڵ�
			m_pDocument->RemoveChild(pRoot);
			m_pDocument->SaveFile(m_xmlFileName);
			return true;
		}
		else
		{//�ӽڵ�
			TiXmlNode *parent = pNode->Parent();//�ҵ��ýڵ�ĸ��ڵ�
			if (NULL == parent)
			{
				return false;
			}

			TiXmlElement *parentElem = parent->ToElement();
			if (NULL == parentElem)
			{
				return false;
			}
			parentElem->RemoveChild(pNode);
			m_pDocument->SaveFile(m_xmlFileName);
			return true;
		}
	}

	return false;
}

//�޸Ľڵ��ı�
bool XMLFile::modifyText(const string nodeName, const string text)
{
	TiXmlDocument* m_pDocument = new TiXmlDocument(m_xmlFileName);
	m_pDocument->LoadFile(m_xmlFileName);

	TiXmlElement *pRoot = m_pDocument->RootElement();
	if (NULL == pRoot)
	{
		return false;
	}

	TiXmlElement *pNode = NULL;
	if (FindNode(pRoot, nodeName, pNode))
	{
		//pNode->Clear();//ɾ��ԭ�ڵ��µ�����Ԫ��
		TiXmlText *pText = new TiXmlText(text.c_str());
		pNode->LinkEndChild(pText);
		m_pDocument->SaveFile(m_xmlFileName);
		return true;
	}

	return false;
}

//�޸Ľڵ�����
bool XMLFile::modifyAttribution(const string nodeName, map<string, string> &mapAttribute)
{
	TiXmlDocument* m_pDocument = new TiXmlDocument(m_xmlFileName);
	m_pDocument->LoadFile(m_xmlFileName);

	TiXmlElement *pRoot = m_pDocument->RootElement();
	if (NULL == pRoot)
	{
		return false;
	}

	TiXmlElement *pNode = NULL;
	if (FindNode(pRoot, nodeName, pNode))
	{
		TiXmlAttribute *pAttr = pNode->FirstAttribute();
		char *strName = NULL;
		for (; pAttr != NULL; pAttr = pAttr->Next())
		{
			strName = const_cast<char *>(pAttr->Name());
			for (auto it = mapAttribute.begin(); it != mapAttribute.end(); ++it)
			{
				if (strName == it->first)
				{
					pNode->SetAttribute(strName, it->second.c_str());
				}
			}
		}
		m_pDocument->SaveFile(m_xmlFileName);
		return true;
	}

	return false;
}

//����ΪnodeName�Ľڵ��²����ӽڵ�
bool XMLFile::AddNode(const string nodeName, const char * newNodeName, const char *text)
{
	TiXmlDocument* m_pDocument = new TiXmlDocument(m_xmlFileName);

	m_pDocument->LoadFile(m_xmlFileName);

	TiXmlElement *pRoot = m_pDocument->RootElement();
	if (NULL == pRoot)
	{
		return false;
	}

	TiXmlElement *pNode = NULL;
	if (FindNode(pRoot, nodeName, pNode))
	{
		TiXmlElement *pNewNode = new TiXmlElement(newNodeName);
		TiXmlText *pNewText = new TiXmlText(text);
		pNewNode->LinkEndChild(pNewText);
		pNode->InsertEndChild(*pNewNode);
		m_pDocument->SaveFile(m_xmlFileName);
		return true;
	}

	return false;
}
