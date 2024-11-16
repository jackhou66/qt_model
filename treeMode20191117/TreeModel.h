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
//
class TreeItem;

class TreeModel : public QAbstractItemModel//QStandardItemModel   QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TreeModel(QObject *parent = nullptr);
	virtual ~TreeModel();
	virtual QVariant  headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual QVariant  data(const QModelIndex & index, int role = Qt::DisplayRole) const;	//* 获取节点的数据
	virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;	//* 获取某一个节点
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);	//* 获取某一个节点的parent
	virtual QModelIndex	parent(const QModelIndex & index) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	//* 返回行数
	virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;
	//* 返回列数
	virtual int	 columnCount(const QModelIndex & parent = QModelIndex()) const;
	QModelIndex  getTopParentIndex(QModelIndex itemIndex);
	Entity * getItem(const QModelIndex &index) const;//

	//关于拖动属性设置
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;
	void setupModelData(const entityViewItemList& li, const QModelIndex &index, Entity* pNode);
	void deleteModelData(const entityViewItemList& li, const QModelIndex &index, Entity* pNode);

	QModelIndex  parentHelpGetIndex(const entityViewItemList& li, const QModelIndex &index,Entity*indexData) const;
	//节点的添加和删除   
	bool insertItem(int intRow, const QModelIndex &index);
	bool removeRows(int position, int rows, const QModelIndex &index);

	//新添加的拖动添加函数
	bool  addTreeNode(Entity* pNode,const QModelIndex &index);
	Entity*  findParentNode(Entity* pNode, Entity* childNode);
	Entity*  nodeFromIndex(const QModelIndex &index) const;
	void setRootNode(Entity *node);

	//* 设置原始数据
	void setEntityList(const entityViewItemList& li);

	//获取树data
	entityViewItemList getEntityDataList() const;

signals:
	void dataChange();

private:
	entityViewItemList mItemList; //* 树状结构的原始数据(父节点list)
	QList<QPersistentModelIndex> m_checkedList;
	Entity  *m_pEntity;
	int m_rowCount;

};


#endif // TREEMODEL_H


