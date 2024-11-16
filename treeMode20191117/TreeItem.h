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

	TreeItem *child(int number);//获取第row个子节点指针
	int childCount() const;//获取 子节点计数
	int columnCount() const;
	QVariant data(int column) const;//获取节点column 列的数据
	int childNumber() const; //返回子项的行数，在只读模型中是int row() const;其实功能是一样的。
	TreeItem *parent();//获取父节点指针

	//可以编辑模式 begin
	void appendChild(TreeItem *child);
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);

	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	bool setData(int column, const QVariant &value);
	//可以编辑模式 end

private:
	//QList<TreeItem*> childItems;// 父结点  
	//QVector<QVariant> itemData; // 子结点列表  
	//TreeItem * parentItem;

	TreeItem *parentItem;  // 父结点  
	QList<TreeItem*> childItems; // 子结点列表  
	QList<QVariant> itemData; // 子节点对应数据  
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

//* 设置原始数据
	
	QAbstractItemModel *model();
	//获取树data
	//
private:
	MyTreeItem *m_rootItem;
	entityViewItemList   m_pItemList; //* 树状结构的原始数据(父节点list)
	Entity  *m_pEntity;
};
 
 
#endif // TREEITEM_H
