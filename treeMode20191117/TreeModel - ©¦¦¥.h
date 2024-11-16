#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "TreeItem.h"
#include <QMimeData>
#include <QPersistentModelIndex>

#include <QListView>
#include <QMutex>
#include <QMutexLocker>
#include <QAtomicPointer>
#include  "CommonStruct.h"
#include <qobject.h>
#include <QMessageBox>
//���ݽṹ
//* ��ʾ�����ã���״�ڵ�ṹ��
 //QMessageBox::warning(NULL, tr("warning"), "this  is error", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
class TreeItem;

class TreeModel : public QAbstractItemModel//QStandardItemModel   QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TreeModel(QObject *parent = nullptr);
	virtual ~TreeModel();
	//* �����ṩView header���ֵ�����
	virtual QVariant	headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	//* ��������
	virtual int	 columnCount(const QModelIndex & parent = QModelIndex()) const;

	//* ��ȡ�ڵ������
	virtual QVariant  data(const QModelIndex & index, int role = Qt::DisplayRole) const;

	//* ��ȡĳһ���ڵ�
	virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

	//* ��ȡĳһ���ڵ��parent
	virtual QModelIndex	parent(const QModelIndex & index) const;

	//* ��������
	virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;

	//* ����ԭʼ����
	void setEntityList(const entityViewItemList& li);

	//* ����ԭʼ����
	entityViewItemList EntityList();

	QModelIndex  getTopParentIndex(QModelIndex itemIndex);

	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Entity * getItem(const QModelIndex &index) const;//

	//Ŀǰע�͵��Ĵ���
	/*void treeItemChanged(Entity * item);
	void treeItem_checkAllChild(Entity * item, bool check);
	void treeItem_checkAllChild_recursion(Entity * item, bool check);
	void treeItem_CheckChildChanged(Entity * item);
	Qt::CheckState checkSibling(Entity * item);*/

	//�����϶���������
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;

	//�ڵ����Ӻ�ɾ��  
	bool insertItem(int position, int rows, const QModelIndex &index, Entity * item);//
	bool removeRows(int position, int rows, const QModelIndex &index);
	void setRootNode(Entity *node);

	//����ӵ��϶���Ӻ���
	bool  addTreeNode(Entity* pNode);
	Entity*  findParentNode(Entity* pNode, Entity* childNode);
	int  treeNodeHaveEqualInfo(Entity* parentNode, Entity* pAddChildNode);
	Entity*  nodeFromIndex(const QModelIndex &index) const;
 
	//��ȡ��data

	entityViewItemList getEntityDataList() const;
private:
	entityViewItemList mItemList; //* ��״�ṹ��ԭʼ����(���ڵ�list)
	QList<QPersistentModelIndex> m_checkedList;
	Entity  *m_pEntity;
	int m_rowCount;
};


//class NewTreeMode :public TreeModel
//{
//	Q_OBJECT
//
//public:
//	explicit NewTreeMode(QObject *parent = nullptr);
//	virtual ~NewTreeMode();
//public:
//	static NewTreeMode *instance();
//private:
//	static QAtomicPointer<NewTreeMode> m_pInstance;
//	static QMutex  m_mutex;
//};
// 
//
//class NewTreeModeView :public TreeModel
//{
//	Q_OBJECT
//
//public:
//	explicit NewTreeModeView(QObject *parent = nullptr);
//	virtual ~NewTreeModeView();
//public:
//	static NewTreeModeView *instance();
//private:
//	static QAtomicPointer<NewTreeModeView> m_pInstance;
//	static QMutex  m_mutex;
//};


#endif // TREEMODEL_H


