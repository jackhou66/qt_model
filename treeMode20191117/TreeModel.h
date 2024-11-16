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
//
class TreeItem;

class TreeModel : public QAbstractItemModel//QStandardItemModel   QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TreeModel(QObject *parent = nullptr);
	virtual ~TreeModel();
	virtual QVariant  headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual QVariant  data(const QModelIndex & index, int role = Qt::DisplayRole) const;	//* ��ȡ�ڵ������
	virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;	//* ��ȡĳһ���ڵ�
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);	//* ��ȡĳһ���ڵ��parent
	virtual QModelIndex	parent(const QModelIndex & index) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	//* ��������
	virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;
	//* ��������
	virtual int	 columnCount(const QModelIndex & parent = QModelIndex()) const;
	QModelIndex  getTopParentIndex(QModelIndex itemIndex);
	Entity * getItem(const QModelIndex &index) const;//

	//�����϶���������
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;
	void setupModelData(const entityViewItemList& li, const QModelIndex &index, Entity* pNode);
	void deleteModelData(const entityViewItemList& li, const QModelIndex &index, Entity* pNode);

	QModelIndex  parentHelpGetIndex(const entityViewItemList& li, const QModelIndex &index,Entity*indexData) const;
	//�ڵ����Ӻ�ɾ��   
	bool insertItem(int intRow, const QModelIndex &index);
	bool removeRows(int position, int rows, const QModelIndex &index);

	//����ӵ��϶���Ӻ���
	bool  addTreeNode(Entity* pNode,const QModelIndex &index);
	Entity*  findParentNode(Entity* pNode, Entity* childNode);
	Entity*  nodeFromIndex(const QModelIndex &index) const;
	void setRootNode(Entity *node);

	//* ����ԭʼ����
	void setEntityList(const entityViewItemList& li);

	//��ȡ��data
	entityViewItemList getEntityDataList() const;

signals:
	void dataChange();

private:
	entityViewItemList mItemList; //* ��״�ṹ��ԭʼ����(���ڵ�list)
	QList<QPersistentModelIndex> m_checkedList;
	Entity  *m_pEntity;
	int m_rowCount;

};


#endif // TREEMODEL_H


