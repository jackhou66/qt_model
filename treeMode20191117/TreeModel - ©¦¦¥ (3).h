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

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TreeModel(QObject *parent = 0);
	virtual ~TreeModel();

	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	// 构建模型数据  
	void setupModelData(entityViewItemList  mItemList);

	// 更新模型数据  
	void updateData();
	entityViewItemList getEntityDataList() const;
private:
	entityViewItemList  mItemList; //* 树状结构的原始数据(父节点list)
	Entity *rootItem; // 最顶层顶根节点(一个无效的QModelIndex)  
	QList<QPersistentModelIndex> m_checkedList;
	//Entity  *m_pEntity;
	int m_rowCount;
};
#endif // TREEMODEL_H


