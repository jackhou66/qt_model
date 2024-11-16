#include "TreeItem.h"
#include <QStringList>

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
	parentItem = parent;
	itemData = data;
}
TreeItem::TreeItem(TreeItem *parent)
{
	parentItem = parent;
}

TreeItem::~TreeItem()
{
	qDeleteAll(childItems);
}

TreeItem *TreeItem::child(int number)//row
{
	return childItems.value(number);
}

int TreeItem::childCount() const
{
	return childItems.count();
}

int TreeItem::childNumber() const//孩子的索引值  目录
{
	if (parentItem)
	{
		return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
	}
	return 0;
}

int TreeItem::columnCount() const   //多少列就是多少数据量？  列记录数据
{
	return itemData.count();
}

QVariant TreeItem::data(int column) const//第几列的值
{
	return itemData.value(column);
}
//自行添加
void TreeItem::appendChild(TreeItem *child)
{
	childItems.append(child);
}
//给item插入孩子    第几行插入孩子  孩子的行数     第几列获取孩子的数据  
bool TreeItem::insertChildren(int position, int count, int  columns)//
{
	if (position < 0 || position > childItems.size())//position  即row 
	{
		return false;
	}

	for (int row = 0; row < count; ++row) 
	{
		QList<QVariant> data;
		TreeItem *item = new TreeItem(data, this);//  此处有修改
		childItems.insert(position, item);
	}
	return true;
}

bool TreeItem::insertColumns(int position, int columns)//position  row 
{
	if (position < 0 || position > itemData.size())
	{
		return false;
	}

	for (int column = 0; column < columns; ++column)
	{
		itemData.insert(position, QVariant());
	}

	for(TreeItem *child:childItems)
	{
		child->insertColumns(position, columns);
	}

	return true;
}

TreeItem *TreeItem::parent()
{
	return parentItem;
}

bool TreeItem::removeChildren(int position, int count)//position  row 
{
	if (position < 0 || position + count > childItems.size())
	{
		return false;
	}

	for (int row = 0; row < count; ++row)
	{
		delete	childItems.takeAt(position);
	}
	return true;
}

bool TreeItem::removeColumns(int position, int columns)//row position
{
	if (position < 0 || position + columns > itemData.size())
	{
		return false;
	}
	for (int column = 0; column < columns; ++column)
	{
		itemData.removeAt(position);
	}
	for (TreeItem *child : childItems)
	{
		child->removeColumns(position, columns);
	}
	return true;
}

bool TreeItem::setData(int column, const QVariant &value)
{
	if (column < 0 || column >= itemData.size())
	{
		return false;
	}
	itemData[column] = value;
	return true;
}

////////////////////////////////////////////////////////////////////////////

MyTreeItem::MyTreeItem(const QList<QVariant> &data)
{
	m_itemData = data;
}
MyTreeItem::MyTreeItem()
{
}
MyTreeItem::~MyTreeItem()
{
	qDeleteAll(m_childItems);
}

void MyTreeItem::appendChild(MyTreeItem *item)
{
	item->setParent(this);
	m_childItems.append(item);
}

MyTreeItem *MyTreeItem::child(int row)
{
	return m_childItems.value(row);
}

int MyTreeItem::childCount() const
{
	return m_childItems.count();
}

int MyTreeItem::columnCount() const
{
	return m_itemData.count();
}

QVariant MyTreeItem::data(int column) const
{
	return m_itemData.value(column);
}

MyTreeItem *MyTreeItem::parent()
{
	Q_ASSERT(m_parentItem);
	return m_parentItem;
}

void MyTreeItem::setParent(MyTreeItem *parent)
{
	m_parentItem = parent;
}

int MyTreeItem::row() const
{
	if (!m_parentItem) { return 0; }

	return m_parentItem->m_childItems.indexOf(const_cast<MyTreeItem*>(this));
}
QVariant  MyTreeItem::getEntityDataList() const
{
	return  m_itemData;
}

bool MyTreeItem::setData(int column, const QVariant &value)
{
	if (column < 0 || column >= m_itemData.size())
	{
		return false;
	}
	m_itemData[column] = value;
	return true;
}
bool MyTreeItem::insertChildren(int position, int count, int  columns, MyTreeItem *item, QList<QVariant> data)//
{
	if (position < 0 || position > m_childItems.size())//position  即row 
	{
		return false;
	}

	for (int row = 0; row < count; ++row)
	{
	    //item = new MyTreeItem(data);//  此处有修改
		m_childItems.insert(position, item);
	}
	return true;
}
//////////////////////////////////////////////
MyTreeItemModel::MyTreeItemModel(QObject *parent, const QList<Entity *> &data) :
QAbstractItemModel(parent)
{

	/*QList<QVariant> data22;
	QVariant v;
	v.setValue(data);
	data22.append(v);
	m_rootItem= new MyTreeItem(data22);
	m_pItemList = data;*/
	//setEntityListShow(m_pItemList, m_rootItem);
	QList<QVariant> data22;
	data22.append("111");
	m_rootItem = new MyTreeItem(data22);
	m_rootItem->name = "123";
	QList<QVariant> data1;
	data1.append("a");
	QList<QVariant> data2;
	data2.append("aa");
	QList<QVariant> data3;
	data3.append("aaa");
	auto item1 = new MyTreeItem(data1);
	item1->name = "456";
	auto item2 = new MyTreeItem(data2);
	item2->name = "789";
	auto item3 = new MyTreeItem(data3);
	item3->name = "112";

	m_rootItem->appendChild(item1);
	item1->appendChild(item2);
	item2->appendChild(item3);
	m_pItemList = data;
	//for (int i = 0; i < mItemList.count(); i++)
	//{
	//	auto primary = new MyTreeItem(mItemList[i]->children);
	//	m_rootItem->appendChild(primary);
	//	//* 试图判断该节点的父节点是不是mItemList[i]
	//	for (int ii = 0; ii < mItemList[i]->children.count(); ii++)
	//	{
	//		auto primary2 = new MyTreeItem(mItemList[i]->children[ii]->children);
	//		m_rootItem->appendChild(primary2);
	//		if (mItemList[i]->children[ii]->children.size()>0)
	//		{
	//			setEntityListShow(mItemList[i]->children[ii]->children, m_rootItem);
	//		}
	//		else
	//		{
	//			return;
	//		}
	//	}
	//}
}

MyTreeItemModel::~MyTreeItemModel()
{
	delete m_rootItem;
}

int MyTreeItemModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
	{
		return static_cast<MyTreeItem*>(parent.internalPointer())->columnCount();
	}
	else
	{
		return m_rootItem->columnCount();
	}
}

QHash<int, QByteArray> MyTreeItemModel::roleNames() const
{
	/*
	roleName可以自己定义，我这里是随便写的
	*/

	QHash<int, QByteArray> names(QAbstractItemModel::roleNames());
	names[12345] = "text";
	names[12346] = "text2";
	return names;
}

QVariant MyTreeItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
	if (role == Qt::DisplayRole)
	{
		auto  rootItem=static_cast<MyTreeItem*>(index.internalPointer());
//		Entity*  a = rootItem->data(index.column()).value<Entity*>();
		//qDebug() << "1111111111111" << a->name << endl;
		return 	rootItem->data(index.column());
		//return 	rootItem->name;
	}
	return QVariant();
}

Qt::ItemFlags MyTreeItemModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return 0;
	}
	return 	Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | \
		Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant MyTreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	//if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	//{
	//	return m_rootItem->data(section);
	//}

	//return QVariant();
	//* 只返回header的DisplayRole数据
	if (role == Qt::DisplayRole)
	{
		return QString("name");
	}
	return __super::headerData(section, orientation, role);
}

QModelIndex MyTreeItemModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	MyTreeItem *parentItem;
	if (!parent.isValid())
	{
		parentItem = m_rootItem;
	}
	else
	{
		parentItem = static_cast<MyTreeItem*>(parent.internalPointer());
	}

	MyTreeItem *childItem = parentItem->child(row);
	if (childItem)
	{
		return createIndex(row, column, childItem);
	}
	else
	{
		return QModelIndex();
	}
}

QModelIndex MyTreeItemModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return QModelIndex();
	}

	MyTreeItem *childItem = static_cast<MyTreeItem*>(index.internalPointer());
	MyTreeItem *parentItem = childItem->parent();

	if (parentItem == m_rootItem)
	{
		return QModelIndex();
	}

	return createIndex(parentItem->row(), 0, parentItem);
}

int MyTreeItemModel::rowCount(const QModelIndex &parent) const
{
	MyTreeItem *parentItem;
	if (parent.column() > 0)
	{
		return 0;
	}

	if (!parent.isValid())
	{
		parentItem = m_rootItem;
	}
	else
	{
		parentItem = static_cast<MyTreeItem*>(parent.internalPointer());
	}

	return parentItem->childCount();
}

QAbstractItemModel *MyTreeItemModel::model()
{
	return this;
}
entityViewItemList  MyTreeItemModel::getEntityDataList() const
{
	return  m_pItemList;
}

void MyTreeItemModel::setEntityList(const entityViewItemList &li)
{
	//entityViewItemList 	mItemList = li;
	//QList<QVariant> datas;
	//QVariant  temp;
	//temp.setValue(mItemList);
	//datas.append(temp);
	//entityViewItemList s = temp.value<entityViewItemList>();
	//m_rootItem = new MyTreeItem(datas);
	//for (int i = 0; i < mItemList.size(); ++i)
	//{
	//	QList<QVariant> data1;
	//	QVariant temp2;
	//	temp2.setValue(mItemList[i]->children); //设置QVariant的值
	//	data1.append(temp2);
	//	entityViewItemList ss = temp2.value<entityViewItemList>();
	//	MyTreeItem *primary = new MyTreeItem(data1);
	//	m_rootItem->appendChild(primary);
	//	if (mItemList[i]->children.size()>0)
	//	{
	//			for (int k = 0; k < mItemList[i]->children.size(); ++k)
	//			{
	//				QList<QVariant> data2;
	//				QVariant temp3;
	//				temp3.setValue(mItemList[i]->children[k]->children); //设置QVariant的值
	//				data2.append(temp3);
	//				entityViewItemList sss = temp3.value<entityViewItemList>();
	//				MyTreeItem *primaryChild = new MyTreeItem(data2);
	//				primary->appendChild(primaryChild);
	//				if (mItemList[i]->children[k]->children.size()>0)
	//				{
	//					setEntityList(mItemList[i]->children[k]->children);
	//				}
	//			}
	//   }
 //  }
	m_pItemList = li;
}
void MyTreeItemModel::setEntityListShow(const entityViewItemList & mItemList, MyTreeItem* rootItem)
{
	//for (int i = 0; i < mItemList.count(); i++)
	//{
	//	  rootItem = new MyTreeItem(mItemList[i]->children);
	//	//* 试图判断该节点的父节点是不是mItemList[i]
	//	for (int ii = 0; ii < mItemList[i]->children.count(); ii++)
	//	{
	//		auto primary = new MyTreeItem(mItemList[i]->children[ii]->children);
	//	    rootItem->appendChild(primary);
	//		if (mItemList[i]->children[ii]->children.size()>0)
	//		{
	//			setEntityListShow(mItemList[i]->children[ii]->children, rootItem);
	//		}
	//		else
	//		{
	//			return;
	//		}
	//	}
	//}

	/*for (int i = 0; i < mItemList.count(); i++)
	{
		m_rootItem->children.append(mItemList[i]);
		if (mItemList[i]->children.size()>0)
		{
			for (int ii = 0; ii < mItemList[i]->children.count(); ii++)
			{
				QList<QVariant> data33;
				QVariant c;
				c.setValue(mItemList[i]->children[i]);
				data33.append(c);
				auto item1 = new MyTreeItem(data33);
				m_rootItem->appendChild(item1);
				item1->children.append(mItemList[i]->children);
				if (mItemList[i]->children[ii]->children.size()>0)
				{
					setEntityListShow(mItemList[i]->children[ii]->children, m_rootItem);
				}
				else
				{
					return;
				}
			}
		}
	}*/
}

//重写
QMimeData * MyTreeItemModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData* mimeD = new QMimeData;			//先获取原始的mimeData;
	if (indexes.count() > 0)
	{
		mimeD->setData("drag", "mouse darg");

		for (int i = 0; i < indexes.size(); ++i)
		{
			const QModelIndex index = indexes.at(i);
			if (index.isValid())
			{

				auto  rootItem = static_cast<MyTreeItem*>(index.internalPointer());
				QByteArray encoded;
				//QDataStream datastream(&encoded,QIODevice::WriteOnly);
				//datastream << d->name << d->EntityId;
				encoded.append(rootItem->name);
				mimeD->setData("name", encoded);
			}
		}
	}
	else
	{
		mimeD->setData("name", "NULL");
	}
	return mimeD;
}
bool MyTreeItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{

	QByteArray st = data->data("name");
	if (action == Qt::CopyAction)
	{
		auto  rootItem = static_cast<MyTreeItem*>(parent.internalPointer());
		rootItem->name = st;
		QList<QVariant> v;
		v.append("");
		MyTreeItem* parentTemp = new MyTreeItem (v);
		parentTemp= rootItem;
		rootItem->insertChildren(parent.row(), rootItem->childCount(), parent.column(), rootItem, v);
		//rootItem->appendChild(parentTemp);
	}
	if (action == Qt::MoveAction)
	{
		setData(parent, st);
	}
	return true;
}

QStringList MyTreeItemModel::mimeTypes() const
{
	QStringList  types;
	types << "drag";
	return types;
}