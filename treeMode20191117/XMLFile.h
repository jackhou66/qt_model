#ifndef  XMLFile_H
#define   XMLFile_H

#include <iostream>
#include "tinyxml.h"
#include <string>
#include <map>
#include <memory>
#include  "CommonStruct.h"
//#include <cctype>
using namespace std;

class XMLFile
{
public:
	XMLFile(const char *xmlFileName);
	~XMLFile();

public:
	void createXML(const entityViewItemList& mItemList);
	void ReadXML();//��ȡXML�ļ���������
	void createEntityXML(entityViewItemList & children, TiXmlElement& pRoot); //����XML
	void ReadDeclaration(string &version, string &encoding, string &standalone);//��ȡXML����
	bool FindNode(TiXmlElement *pRoot, const string nodeName, TiXmlElement *&pNode);//���ݽڵ������жϽڵ��Ƿ����
	bool GetNodeText(const string nodeName, const char *&text);//���ݽڵ�������ȡ�ýڵ��ı�
	bool GetNodeAttribute(const string nodeName, map<string, string> &mapAttribute);//��ȡ���ݽڵ����� ��ȡ�ڵ�����
	bool DeleteNode(const string nodeName);//���ݽڵ�����ɾ���ڵ�
	bool modifyText(const string nodeName, const string text);//�޸Ľڵ��ı�
	bool modifyAttribution(const string nodeName, map<string, string> &mapAttribute);//�޸Ľڵ�����
	bool AddNode(const string nodeName, const char * newNodeName, const char *text);//��ӽڵ�
private:
	char *m_xmlFileName;
	TiXmlDocument *m_pDocument;
};
#endif   //XMLFile_H