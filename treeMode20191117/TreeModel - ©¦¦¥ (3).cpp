#include "TreeModel.h"
#include <QtWidgets>

#include "treeitem.h"
#include <QtGui>  

TreeModel::TreeModel(QObject *parent) :QAbstractItemModel(parent)
{
	rootItem = nullptr;
	updateData();
}

TreeModel::~TreeModel()
{
	SAFE_DELETE(rootItem);
}

void TreeModel::updateData()
{
	// �����ɵ�ģ������  
	if (rootItem)
	{
		delete rootItem;
		rootItem = NULL;
	}

	QList<QVariant> rootData;
	//rootData << "Tag" << "Type";

	//rootItem = new TreeItem(rootData);
	//setupModelData(rootItem);

	// ˢ��ģ��  
	//reset();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	// ���ͼ��  
	if (role == Qt::DecorationRole&&index.column() == 0)
		return QIcon("images/fold.png");

	// ��ʾ�ڵ�����ֵ  
	if (role == Qt::DisplayRole)
	{
		TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
		return item->data(index.column());
	}

	return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal&&role == Qt::DisplayRole)
		return rootItem->data(section);

	return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	TreeItem *parentItem;
	if (!parent.isValid())
	{
		parentItem = rootItem;
	}
	else
	{
		parentItem = static_cast<TreeItem*>(parent.internalPointer());
	}

	TreeItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem); // չ������,Ϊ�ӽڵ㽨������  
	else
		return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
	TreeItem *parentItem = childItem->parent();

	// ����ڵ�,ֱ�ӷ��ؿ�����  
	if (parentItem == rootItem)
		return QModelIndex();

	// Ϊ����㽨������  
	return createIndex(parentItem->childNumber(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
	TreeItem *parentItem;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<TreeItem*>(parent.internalPointer());

	return parentItem->childCount(); // ���ظ�������ӽ����Ŀ  
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
	return rootItem->columnCount();
}
entityViewItemList TreeModel::getEntityDataList() const
{
	return mItemList;
}
// ����ģ������,��������2�������,ÿ���������������ӽڵ�����νṹ  
void TreeModel::setupModelData(entityViewItemList  ItemList)
{	
	mItemList = ItemList;
	layoutChanged(); //* ֪ͨViewˢ������
	/*	for (int i = 0; i < ItemList.size(); ++i)
		{
			QList<QVariant> datas;
			datas.append(ItemList[i]->name);
			TreeItem *primary = new TreeItem(datas, ItemList[i]);
			if (ItemList[i]->children.size()>0)
			{
				for (int k = 0; k < ItemList[i]->children.size(); ++k)
				{
					QList<QVariant> data;
					data.append(ItemList[i]->children[k]->name);
					TreeItem *primaryChild = new TreeItem(data, ItemList[i]->children[k]);
					if (ItemList[i]->children[k]->children.size()>0)
					{
						setupModelData(ItemList[i]->children[k]->children);
					}
					else
					{
						return;
					}
				}
				break;
			}
			else
			{
				return;
			} 
	}*/
}