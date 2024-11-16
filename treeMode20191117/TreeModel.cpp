#include "TreeModel.h"
#include <QtWidgets>
#include <QMetaType>
#include "treeitem.h"

const int COLUMN_NUMBER = 1;

TreeModel::TreeModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	this->m_pEntity = NULL;
	m_pEntity = new Entity();
	m_pEntity->parentEntity = nullptr;
	//构造一个根节点，在Qt中根节点的父节点为空，默认不显示，构造一个空节点充当父节点
}

TreeModel::~TreeModel()
{
	SAFE_DELETE(m_pEntity);
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
	return COLUMN_NUMBER;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		Entity* node = nodeFromIndex(index);
		return node->name;
	}
	return QVariant();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid()&& role == Qt::EditRole)
	{
		Entity* node = nodeFromIndex(index);
		node->name = value.toString();
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return 0;
	}
	return 	Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled |      \
		Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;// | Qt::ItemIsUserCheckable;| QAbstractItemModel::flags(index)	|Qt::ItemIsEnabled  | Qt::ItemIsEditable

}
Entity *TreeModel::getItem(const QModelIndex &index) const
{
	if (index.isValid())
	{
		//index.internalPointer()  QSortFilterProxyModel内部维护的指针
		Entity *item = static_cast<Entity*>(index.internalPointer());
		if (item != nullptr)
		{
			return item;
		}
	}
	return m_pEntity;
}
bool TreeModel::removeRows(int position, int rows, const QModelIndex &index)
{
	beginRemoveRows(index, 0, position + rows - 1);
	endRemoveRows();
	return true;
}
bool TreeModel::insertItem(int intRow, const QModelIndex &index)//
{
	return true;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
	//* 父节点是否有效
	//* 无效的父节点（说明是分组）返回父节点个数
	if (!parent.isValid())
	{
		return mItemList.count();
	}
	//*父节点是有效的，获取父节点原始数据
	Entity* d = static_cast<Entity*>(parent.internalPointer());
	if (d == nullptr)
	{
		return 0;
	}
	//* 父节点的原始数据中的子节点个数即为rowCount
	return d->children.count();
}
QModelIndex TreeModel::getTopParentIndex(QModelIndex itemIndex)
{
	QModelIndex secondItem = itemIndex;
	while (itemIndex.parent().isValid())
	{
		secondItem = itemIndex.parent();
		itemIndex = secondItem;
	}
	if (secondItem.column() != 0)
	{
		secondItem = secondItem.sibling(secondItem.row(), 0);
	}
	return secondItem;
}
void TreeModel::setEntityList(const entityViewItemList &li)
{
	mItemList = li;
	layoutChanged(); 
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	if (role == Qt::DisplayRole)
	{
		return QString("name");
	}
	return __super::headerData(section, orientation, role);
}

QMimeData * TreeModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData* mimeD = new QMimeData;			
	if (indexes.count() > 0)
	{
		mimeD->setData("drag", "mouse darg");
		for (int i = 0; i < indexes.size(); ++i)
		{
			const QModelIndex index = indexes.at(i);
			if (index.isValid())
			{
				QByteArray encoded;
				Entity* d = static_cast<Entity*>(index.internalPointer());
			
				//QDataStream datastream(&encoded,QIODevice::WriteOnly);
				//datastream << d->name << d->EntityId;
				encoded.append(d->name);
				mimeD->setData("name", encoded);
				encoded.clear();
				encoded.append(d->EntityId);
				mimeD->setData("EntityId", encoded);
				encoded.clear();
				//目前ArmyType测试编码0 红方 1 蓝方
				//目前PlantType测试编码0  兵力 1 DEVICE 设备
				QVariant planttype = QVariant::fromValue(d->plantType);
				encoded.append(planttype.toString());
				mimeD->setData("PlantType", encoded);
				encoded.clear();

				QVariant armytype = QVariant::fromValue(d->armyType);
				encoded.append(armytype.toString());
				mimeD->setData("Armytype", encoded);
				encoded.clear();

				encoded.append(d->isGroup);
				mimeD->setData("IsGroup", encoded);
				encoded.clear();
			}
		}
	}
	else
	{
		mimeD->setData("name", "NULL");
	}
	return mimeD;
}
bool TreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
	QByteArray strName = data->data("name");
	QByteArray strEntityId = data->data("EntityId");
	QByteArray strPlantType = data->data("PlantType");
	QByteArray strArmytype = data->data("Armytype");
	QByteArray stIsGroup = data->data("IsGroup");
	if (action == Qt::CopyAction)
	{
		Entity* parentData = static_cast<Entity*>(parent.internalPointer());
		Entity* parentTemp = new  Entity;
	/*	if (parentData->isGroup != stIsGroup)
		{
			QMessageBox::warning(NULL, tr("warning"), tr("do not  drag  group to team or  drag team to group"),QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		}
		else
		{*/
			//parentTemp->children = parentData->children;
			parentTemp->name = strName;
			parentTemp->EntityId = strEntityId;
			if (parentData->children.size() == 0)
			{
				    setupModelData(getEntityDataList(), parent, parentTemp);
					emit dataChange();
			}
			else
			{
				setupModelData(getEntityDataList(), parent, parentTemp);
			}
		
	}
	if (action == Qt::MoveAction)
	{
		setData(parent, strName);
	}
	m_rowCount++;
	return true;
}
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	//* 看父节点是否有效
	if (!parent.isValid()) //* 无效的父节点(那肯定是分组)
	{
		QModelIndex groupIndex;
		if (mItemList.count() > row) //* 使用有效的数据创建一个节点
		{
			//qDebug() << "mItemList.at(row)->name" << mItemList.at(row)->name << endl;
			groupIndex = createIndex(row, column, mItemList.at(row));
		}
		return groupIndex;
	}
	else
	{
		//* 有效的父节点
		//* 获取父节点的数据
		Entity* parentData = static_cast<Entity*>(parent.internalPointer());
		if (parentData != nullptr)
		{
			//* 使用父节点下的对应row的子对象结构创建一个节点
			if (parentData->children.count() > row)
			{
				//qDebug() << "parentData->children[row]->name" << parentData->children[row]->name << endl;
				//QModelIndex childIndex = createIndex(row, column, parentData->children[row]);
				QModelIndex childIndex = createIndex(row, column, parentData->children[row]);
				return childIndex;
			}
		}
	}
	//* 没有有效的数据项返回一个无效的节点
	return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	//* 如果是无效的节点则返回无效节点
	if (!index.isValid())
	{
		return QModelIndex();
	}
	Entity* indexData = static_cast<Entity*>(index.internalPointer());
	//1级节点循环
	for (int i = 0; i < mItemList.count(); i++)
	{
		//* 如果是父节点（分组）则返回无效父节点（分组没有父节点）
		if (mItemList[i] == indexData)
		{
			return QModelIndex();
		}
		else
		{
			//* 试图判断该节点的父节点是不是mItemList[i]
			//2级节点循环
			for (int ii = 0; ii < mItemList[i]->children.count(); ii++)
			{
				//* mItemList[i] 成功匹配为indexData的父节点
				indexData->name;
				if (indexData == mItemList[i]->children[ii])
				{
					//* 使用mItemList[i]作为数据创建一个父节点
					qDebug() << "indexData == mItemList[i]->children[ii]" << i << mItemList[i]->name << endl;
					QModelIndex parentIndex = createIndex(i, 0, mItemList[i]);
					return parentIndex;
				}
				else
				{
					//3级循环
					for (int kk = 0; kk < mItemList[i]->children[ii]->children.count(); kk++)
					{
						//* mItemList[i] 成功匹配为indexData的父节点
						indexData->name;
						if (indexData == mItemList[i]->children[ii]->children[kk])
						{
							//* 使用mItemList[i]作为数据创建一个父节点
							qDebug() << "mItemList[i]->children[ii]->children[kk]" << ii << mItemList[i]->children[ii]->name << endl;
							QModelIndex parentIndex = createIndex(ii, 0, mItemList[i]->children[ii]);
							return parentIndex;
						}
						else
						{
							//4级循环
							for (int ll = 0; ll < mItemList[i]->children[ii]->children[kk]->children.count(); ll++)
							{
								//* mItemList[i] 成功匹配为indexData的父节点
								indexData->name;
								if (indexData == mItemList[i]->children[ii]->children[kk]->children[ll])
								{
									//* 使用mItemList[i]作为数据创建一个父节点
									qDebug() << "mItemList[i]->children[ii]->children[kk]" << ii << mItemList[i]->children[ii]->name << endl;
									QModelIndex parentIndex = createIndex(ii, 0, mItemList[i]->children[ii]->children[kk]);
									return parentIndex;
								}
								else
								{
									//5级循环
									for (int nn = 0; nn < mItemList[i]->children[ii]->children[kk]->children[ll]->children.count(); nn++)
									{
										//* mItemList[i] 成功匹配为indexData的父节点
										indexData->name;
										if (indexData == mItemList[i]->children[ii]->children[kk]->children[ll]->children[nn])
										{
											//* 使用mItemList[i]作为数据创建一个父节点
											qDebug() << "mItemList[i]->children[ii]->children[kk]" << ii << mItemList[i]->children[ii]->name << endl;
											QModelIndex parentIndex = createIndex(ii, 0, mItemList[i]->children[ii]->children[kk]->children[ll]);
											return parentIndex;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//* 未匹配到有效的父节点数据，返回无效节点
	return QModelIndex();
}
QModelIndex TreeModel::parentHelpGetIndex(const entityViewItemList& li, const QModelIndex &index, Entity*indexData) const
{
	//Entity* indexDataTemp = static_cast<Entity*>(index.internalPointer());
	////5级循环
	//for (int i = 0; i < li.count(); i++)
	//{
	//	if (li[i]->children.count()>0)
	//	{
	//		for (int ii = 0; ii < li[i]->children.count(); ii++)
	//		{
	//			// mItemList[i] 成功匹配为indexData的父节点
	//			indexData->name;
	//			if (indexData == li[i]->children[ii])
	//			{
	//				//* 使用mItemList[i]作为数据创建一个父节点
	//				QModelIndex parentIndex = createIndex(ii, 0, li[i]);
	//				return parentIndex;
	//			}
	//			if (indexData == li[i])
	//			{
	//				//* 使用mItemList[i]作为数据创建一个父节点
	//				QModelIndex parentIndex = createIndex(ii, 0, li[i]);
	//				return parentIndex;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (indexData == li[i])
	//		{
	//			//使用mItemList[i]作为数据创建一个父节点
	//			qDebug() << "	QModelIndex parentIndex = createIndex(i, 0, li[i]);" << i << li[i]->name << endl;
	//			QModelIndex parentIndex = createIndex(i, 0, li[i]);
	//			return parentIndex;
	//		}
	//	}
	//}
	//for (int i = 0; i < li.count(); i++)
	//{
	//	// mItemList[i] 成功匹配为indexData的父节点
	//	indexData->name;
	//	if (indexData == li[i]->children)
	//	{
	//		//使用mItemList[i]作为数据创建一个父节点
	//		qDebug() << "	QModelIndex parentIndex = createIndex(i, 0, li[i]);" << i << li[i]->name << endl;
	//		QModelIndex parentIndex;
	//		return parentIndex;
	//	}
	//	else
	//	{
	//		for (int ii = 0; ii < li[i]->children.count(); ii++)
	//		{
	//			// mItemList[i] 成功匹配为indexData的父节点
	//			indexData->name;
	//			if (indexData == li[i]->children[ii])
	//			{
	//				//* 使用mItemList[i]作为数据创建一个父节点
	//				QModelIndex parentIndex = createIndex(ii, 0, li[i]);
	//				return parentIndex;
	//			}
	//			else
	//			{
	//				if (li[i]->children[ii]->children.count()>0)
	//				{
	//					QModelIndex parentIndex = parentHelpGetIndex(li[i]->children, index, indexData);
	//					return parentIndex;
	//				}
	//			}
	//		}
	//	}
	//}
	////* 未匹配到有效的父节点数据，返回无效节点
	return QModelIndex();
}
 void TreeModel::setupModelData(const entityViewItemList& li, const QModelIndex &index, Entity* pNode)
{
    bool  success=false;
	const entityViewItemList  ItemList = li;
	int count = 0;
	Entity* indexData = static_cast<Entity*>(index.internalPointer());
	for (int i = 0; i < ItemList.count(); i++)
	{
		//* 如果是父节点（分组）则返回无效父节点（分组没有父节点）
		count = i;
		if (ItemList[i] == indexData) 
		{
			ItemList[i]->children.append(pNode);
			//setEntityList(getEntityDataList()); // 20191126
			return  ;
		}
		else
		{
			//* 试图判断该节点的父节点是不是mItemList[i]
			for (int ii = 0; ii < ItemList[i]->children.count(); ii++)
			{
				if (indexData == ItemList[i]->children[ii])
				{
					ItemList[i]->children[ii]->name;
					pNode->name;
					ItemList[i]->children[ii]->children.append(pNode);				
					return  ;
				}
				else
				{
					if (ItemList[i]->children[ii]->children.size()>0)
					{
						setupModelData(ItemList[i]->children, index, pNode);
						break;
					}
				}
			}
		}
	}
}

void TreeModel::deleteModelData(const entityViewItemList& li, const QModelIndex &index, Entity* pNode)
{
	const entityViewItemList  ItemList = li;
	entityViewItemList  viewtemp;
	Entity* indexData = static_cast<Entity*>(index.internalPointer());
	for (int i = 0; i < ItemList.count(); i++)
	{
		//* 如果是父节点（分组）则返回无效父节点（分组没有父节点）
		if (ItemList[i] == indexData) 
		{
			ItemList[i]->children.removeAt(i);
			setEntityList(getEntityDataList());
		}
		else
		{
			//* 试图判断该节点的父节点是不是mItemList[i]
			for (int ii = 0; ii < ItemList[i]->children.count(); ii++)
			{
				if (indexData == ItemList[i]->children[ii])
				{
					ItemList[i]->children[ii]->children.removeAt(i);
					setEntityList(getEntityDataList());
				}
				else
				{
					if (ItemList[i]->children[ii]->children.size()>0)
					{
						deleteModelData(ItemList[i]->children[ii]->children, index, pNode);
					}
					else
					{
						return;
					}
				}
			}
		}
	}
}
//往某个父节点，添加一个子节点，如果parentNode为空，添加到父节点下
bool TreeModel::addTreeNode(Entity* pNode, const QModelIndex &index)
{
	return true;//暂时保留
}

QStringList TreeModel::mimeTypes() const
{
	QStringList  types;
	types << "drag";
	return types;
}
//设置设备树的根结点
void TreeModel::setRootNode(Entity *node)
{
	//要更新model数据时，先调用beginResetModel,结束时调用endResetModel，所有绑定在Model上的视图都会更新
	this->beginResetModel();
	if (m_pEntity != nullptr)
	{
		delete m_pEntity;
		m_pEntity = nullptr;
	}
	m_pEntity = node;
	endResetModel();
}
//pNode 为要查找节点， childNode 为被查找节点，返回被查找节点的父节点,pNode和childNode之间有层级关系
Entity* TreeModel::findParentNode(Entity* pNode, Entity* childNode)
{
	if (!pNode)
	{
		return NULL;
	}
	//如果子节点在所在的父节点，返回父节点
	if (pNode->children.indexOf(childNode))								
		return pNode;
	for (int i = 0; i < pNode->children.count(); i++)
	{
		return findParentNode(pNode->children.at(i), childNode);
	}
	return NULL;
}

//根据QModelIndex，返回指向其父结点的指针
Entity* TreeModel::nodeFromIndex(const QModelIndex &index) const
{
	if (index.isValid())				
	{
		Entity* d = static_cast<Entity*>(index.internalPointer());
		return  d;
	}
	return  m_pEntity;
}
entityViewItemList TreeModel::getEntityDataList() const
{
	return  mItemList;
}