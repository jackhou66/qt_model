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

	// ����ģ������  
	void setupModelData(entityViewItemList  mItemList);

	// ����ģ������  
	void updateData();
	entityViewItemList getEntityDataList() const;
private:
	entityViewItemList  mItemList; //* ��״�ṹ��ԭʼ����(���ڵ�list)
	Entity *rootItem; // ��㶥���ڵ�(һ����Ч��QModelIndex)  
	QList<QPersistentModelIndex> m_checkedList;
	//Entity  *m_pEntity;
	int m_rowCount;
};
#endif // TREEMODEL_H


