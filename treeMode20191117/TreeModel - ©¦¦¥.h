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
//数据结构
//* （示例所用）树状节点结构体
 //QMessageBox::warning(NULL, tr("warning"), "this  is error", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
class TreeItem;

class TreeModel : public QAbstractItemModel//QStandardItemModel   QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TreeModel(QObject *parent = nullptr);
	virtual ~TreeModel();
	//* 用来提供View header部分的数据
	virtual QVariant	headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	//* 返回列数
	virtual int	 columnCount(const QModelIndex & parent = QModelIndex()) const;

	//* 获取节点的数据
	virtual QVariant  data(const QModelIndex & index, int role = Qt::DisplayRole) const;

	//* 获取某一个节点
	virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

	//* 获取某一个节点的parent
	virtual QModelIndex	parent(const QModelIndex & index) const;

	//* 返回行数
	virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;

	//* 设置原始数据
	void setEntityList(const entityViewItemList& li);

	//* 返回原始数据
	entityViewItemList EntityList();

	QModelIndex  getTopParentIndex(QModelIndex itemIndex);

	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Entity * getItem(const QModelIndex &index) const;//

	//目前注释掉的代码
	/*void treeItemChanged(Entity * item);
	void treeItem_checkAllChild(Entity * item, bool check);
	void treeItem_checkAllChild_recursion(Entity * item, bool check);
	void treeItem_CheckChildChanged(Entity * item);
	Qt::CheckState checkSibling(Entity * item);*/

	//关于拖动属性设置
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;

	//节点的添加和删除  
	bool insertItem(int position, int rows, const QModelIndex &index, Entity * item);//
	bool removeRows(int position, int rows, const QModelIndex &index);
	void setRootNode(Entity *node);

	//新添加的拖动添加函数
	bool  addTreeNode(Entity* pNode);
	Entity*  findParentNode(Entity* pNode, Entity* childNode);
	int  treeNodeHaveEqualInfo(Entity* parentNode, Entity* pAddChildNode);
	Entity*  nodeFromIndex(const QModelIndex &index) const;
 
	//获取树data

	entityViewItemList getEntityDataList() const;
private:
	entityViewItemList mItemList; //* 树状结构的原始数据(父节点list)
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


