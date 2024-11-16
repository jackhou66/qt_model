#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include <QStandardItem>
#include <QObject>
#include  "CommonStruct.h"
#include <QStringList>
#include <QAbstractItemModel>
#include <QDebug>
#include  <QMimeData>

//201912 15:45 TreeMode 
class TreeItem
{
public:
	explicit TreeItem(const QList<QVariant> &data, TreeItem *parent);
	explicit TreeItem(TreeItem *parent = nullptr);
	virtual ~TreeItem();

	TreeItem *child(int number);//��ȡ��row���ӽڵ�ָ��
	int childCount() const;//��ȡ �ӽڵ����
	int columnCount() const;
	QVariant data(int column) const;//��ȡ�ڵ�column �е�����
	int childNumber() const; //�����������������ֻ��ģ������int row() const;��ʵ������һ���ġ�
	TreeItem *parent();//��ȡ���ڵ�ָ��

	//���Ա༭ģʽ begin
	void appendChild(TreeItem *child);
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);

	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	bool setData(int column, const QVariant &value);
	//���Ա༭ģʽ end

private:
	//QList<TreeItem*> childItems;// �����  
	//QVector<QVariant> itemData; // �ӽ���б�  
	//TreeItem * parentItem;

	TreeItem *parentItem;  // �����  
	QList<TreeItem*> childItems; // �ӽ���б�  
	QList<QVariant> itemData; // �ӽڵ��Ӧ����  
	//entityViewItemList  mItemList;
};

class MyTreeItem :public Entity
{

public:
	MyTreeItem(const QList<QVariant> &data);
	MyTreeItem();
	~MyTreeItem();

	void appendChild(MyTreeItem *child);

	MyTreeItem *child(int row);

	int childCount() const;

	int columnCount() const;

	QVariant  data(int column) const;

	int row() const;
	bool setData(int column, const QVariant &value);
	MyTreeItem *parent();

	void setParent(MyTreeItem *parent);
	QVariant   getEntityDataList() const;
	bool  insertChildren(int position, int count, int  columns, MyTreeItem *item, QList<QVariant> data);//
private:
	MyTreeItem *m_parentItem;
	QList<MyTreeItem*> m_childItems;
	QList<QVariant> m_itemData;
};

class MyTreeItemModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	MyTreeItemModel(QObject *parent, const QList<Entity *> &data);

	~MyTreeItemModel();

	QVariant data(const QModelIndex &index, int role) const;

	Qt::ItemFlags flags(const QModelIndex &index) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

	QModelIndex parent(const QModelIndex &index) const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const;

	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	void setEntityListShow(const entityViewItemList &li, MyTreeItem* rootItem);
	QHash<int, QByteArray> roleNames() const;
	void setEntityList(const entityViewItemList& li);
	entityViewItemList   getEntityDataList() const;

	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;

public slots:

//* ����ԭʼ����
	
	QAbstractItemModel *model();
	//��ȡ��data
	//
private:
	MyTreeItem *m_rootItem;
	entityViewItemList   m_pItemList; //* ��״�ṹ��ԭʼ����(���ڵ�list)
	Entity  *m_pEntity;
};
 
 
#endif // TREEITEM_H
