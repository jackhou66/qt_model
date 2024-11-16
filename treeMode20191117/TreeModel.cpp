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
	//����һ�����ڵ㣬��Qt�и��ڵ�ĸ��ڵ�Ϊ�գ�Ĭ�ϲ���ʾ������һ���սڵ�䵱���ڵ�
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
		//index.internalPointer()  QSortFilterProxyModel�ڲ�ά����ָ��
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
	//* ���ڵ��Ƿ���Ч
	//* ��Ч�ĸ��ڵ㣨˵���Ƿ��飩���ظ��ڵ����
	if (!parent.isValid())
	{
		return mItemList.count();
	}
	//*���ڵ�����Ч�ģ���ȡ���ڵ�ԭʼ����
	Entity* d = static_cast<Entity*>(parent.internalPointer());
	if (d == nullptr)
	{
		return 0;
	}
	//* ���ڵ��ԭʼ�����е��ӽڵ������ΪrowCount
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
				//ĿǰArmyType���Ա���0 �췽 1 ����
				//ĿǰPlantType���Ա���0  ���� 1 DEVICE �豸
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
	//* �����ڵ��Ƿ���Ч
	if (!parent.isValid()) //* ��Ч�ĸ��ڵ�(�ǿ϶��Ƿ���)
	{
		QModelIndex groupIndex;
		if (mItemList.count() > row) //* ʹ����Ч�����ݴ���һ���ڵ�
		{
			//qDebug() << "mItemList.at(row)->name" << mItemList.at(row)->name << endl;
			groupIndex = createIndex(row, column, mItemList.at(row));
		}
		return groupIndex;
	}
	else
	{
		//* ��Ч�ĸ��ڵ�
		//* ��ȡ���ڵ������
		Entity* parentData = static_cast<Entity*>(parent.internalPointer());
		if (parentData != nullptr)
		{
			//* ʹ�ø��ڵ��µĶ�Ӧrow���Ӷ���ṹ����һ���ڵ�
			if (parentData->children.count() > row)
			{
				//qDebug() << "parentData->children[row]->name" << parentData->children[row]->name << endl;
				//QModelIndex childIndex = createIndex(row, column, parentData->children[row]);
				QModelIndex childIndex = createIndex(row, column, parentData->children[row]);
				return childIndex;
			}
		}
	}
	//* û����Ч���������һ����Ч�Ľڵ�
	return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	//* �������Ч�Ľڵ��򷵻���Ч�ڵ�
	if (!index.isValid())
	{
		return QModelIndex();
	}
	Entity* indexData = static_cast<Entity*>(index.internalPointer());
	//1���ڵ�ѭ��
	for (int i = 0; i < mItemList.count(); i++)
	{
		//* ����Ǹ��ڵ㣨���飩�򷵻���Ч���ڵ㣨����û�и��ڵ㣩
		if (mItemList[i] == indexData)
		{
			return QModelIndex();
		}
		else
		{
			//* ��ͼ�жϸýڵ�ĸ��ڵ��ǲ���mItemList[i]
			//2���ڵ�ѭ��
			for (int ii = 0; ii < mItemList[i]->children.count(); ii++)
			{
				//* mItemList[i] �ɹ�ƥ��ΪindexData�ĸ��ڵ�
				indexData->name;
				if (indexData == mItemList[i]->children[ii])
				{
					//* ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
					qDebug() << "indexData == mItemList[i]->children[ii]" << i << mItemList[i]->name << endl;
					QModelIndex parentIndex = createIndex(i, 0, mItemList[i]);
					return parentIndex;
				}
				else
				{
					//3��ѭ��
					for (int kk = 0; kk < mItemList[i]->children[ii]->children.count(); kk++)
					{
						//* mItemList[i] �ɹ�ƥ��ΪindexData�ĸ��ڵ�
						indexData->name;
						if (indexData == mItemList[i]->children[ii]->children[kk])
						{
							//* ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
							qDebug() << "mItemList[i]->children[ii]->children[kk]" << ii << mItemList[i]->children[ii]->name << endl;
							QModelIndex parentIndex = createIndex(ii, 0, mItemList[i]->children[ii]);
							return parentIndex;
						}
						else
						{
							//4��ѭ��
							for (int ll = 0; ll < mItemList[i]->children[ii]->children[kk]->children.count(); ll++)
							{
								//* mItemList[i] �ɹ�ƥ��ΪindexData�ĸ��ڵ�
								indexData->name;
								if (indexData == mItemList[i]->children[ii]->children[kk]->children[ll])
								{
									//* ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
									qDebug() << "mItemList[i]->children[ii]->children[kk]" << ii << mItemList[i]->children[ii]->name << endl;
									QModelIndex parentIndex = createIndex(ii, 0, mItemList[i]->children[ii]->children[kk]);
									return parentIndex;
								}
								else
								{
									//5��ѭ��
									for (int nn = 0; nn < mItemList[i]->children[ii]->children[kk]->children[ll]->children.count(); nn++)
									{
										//* mItemList[i] �ɹ�ƥ��ΪindexData�ĸ��ڵ�
										indexData->name;
										if (indexData == mItemList[i]->children[ii]->children[kk]->children[ll]->children[nn])
										{
											//* ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
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
	//* δƥ�䵽��Ч�ĸ��ڵ����ݣ�������Ч�ڵ�
	return QModelIndex();
}
QModelIndex TreeModel::parentHelpGetIndex(const entityViewItemList& li, const QModelIndex &index, Entity*indexData) const
{
	//Entity* indexDataTemp = static_cast<Entity*>(index.internalPointer());
	////5��ѭ��
	//for (int i = 0; i < li.count(); i++)
	//{
	//	if (li[i]->children.count()>0)
	//	{
	//		for (int ii = 0; ii < li[i]->children.count(); ii++)
	//		{
	//			// mItemList[i] �ɹ�ƥ��ΪindexData�ĸ��ڵ�
	//			indexData->name;
	//			if (indexData == li[i]->children[ii])
	//			{
	//				//* ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
	//				QModelIndex parentIndex = createIndex(ii, 0, li[i]);
	//				return parentIndex;
	//			}
	//			if (indexData == li[i])
	//			{
	//				//* ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
	//				QModelIndex parentIndex = createIndex(ii, 0, li[i]);
	//				return parentIndex;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (indexData == li[i])
	//		{
	//			//ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
	//			qDebug() << "	QModelIndex parentIndex = createIndex(i, 0, li[i]);" << i << li[i]->name << endl;
	//			QModelIndex parentIndex = createIndex(i, 0, li[i]);
	//			return parentIndex;
	//		}
	//	}
	//}
	//for (int i = 0; i < li.count(); i++)
	//{
	//	// mItemList[i] �ɹ�ƥ��ΪindexData�ĸ��ڵ�
	//	indexData->name;
	//	if (indexData == li[i]->children)
	//	{
	//		//ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
	//		qDebug() << "	QModelIndex parentIndex = createIndex(i, 0, li[i]);" << i << li[i]->name << endl;
	//		QModelIndex parentIndex;
	//		return parentIndex;
	//	}
	//	else
	//	{
	//		for (int ii = 0; ii < li[i]->children.count(); ii++)
	//		{
	//			// mItemList[i] �ɹ�ƥ��ΪindexData�ĸ��ڵ�
	//			indexData->name;
	//			if (indexData == li[i]->children[ii])
	//			{
	//				//* ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
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
	////* δƥ�䵽��Ч�ĸ��ڵ����ݣ�������Ч�ڵ�
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
		//* ����Ǹ��ڵ㣨���飩�򷵻���Ч���ڵ㣨����û�и��ڵ㣩
		count = i;
		if (ItemList[i] == indexData) 
		{
			ItemList[i]->children.append(pNode);
			//setEntityList(getEntityDataList()); // 20191126
			return  ;
		}
		else
		{
			//* ��ͼ�жϸýڵ�ĸ��ڵ��ǲ���mItemList[i]
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
		//* ����Ǹ��ڵ㣨���飩�򷵻���Ч���ڵ㣨����û�и��ڵ㣩
		if (ItemList[i] == indexData) 
		{
			ItemList[i]->children.removeAt(i);
			setEntityList(getEntityDataList());
		}
		else
		{
			//* ��ͼ�жϸýڵ�ĸ��ڵ��ǲ���mItemList[i]
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
//��ĳ�����ڵ㣬���һ���ӽڵ㣬���parentNodeΪ�գ���ӵ����ڵ���
bool TreeModel::addTreeNode(Entity* pNode, const QModelIndex &index)
{
	return true;//��ʱ����
}

QStringList TreeModel::mimeTypes() const
{
	QStringList  types;
	types << "drag";
	return types;
}
//�����豸���ĸ����
void TreeModel::setRootNode(Entity *node)
{
	//Ҫ����model����ʱ���ȵ���beginResetModel,����ʱ����endResetModel�����а���Model�ϵ���ͼ�������
	this->beginResetModel();
	if (m_pEntity != nullptr)
	{
		delete m_pEntity;
		m_pEntity = nullptr;
	}
	m_pEntity = node;
	endResetModel();
}
//pNode ΪҪ���ҽڵ㣬 childNode Ϊ�����ҽڵ㣬���ر����ҽڵ�ĸ��ڵ�,pNode��childNode֮���в㼶��ϵ
Entity* TreeModel::findParentNode(Entity* pNode, Entity* childNode)
{
	if (!pNode)
	{
		return NULL;
	}
	//����ӽڵ������ڵĸ��ڵ㣬���ظ��ڵ�
	if (pNode->children.indexOf(childNode))								
		return pNode;
	for (int i = 0; i < pNode->children.count(); i++)
	{
		return findParentNode(pNode->children.at(i), childNode);
	}
	return NULL;
}

//����QModelIndex������ָ���丸����ָ��
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