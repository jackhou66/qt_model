#include "TreeUserMode.h"


TreeUserMode::TreeUserMode(QObject *parent)
	: QAbstractItemModel(parent)
{
	this->m_pEntity = NULL;
	//����һ�����ڵ㣬��Qt�и��ڵ�ĸ��ڵ�Ϊ�գ�Ĭ�ϲ���ʾ������һ���սڵ�䵱���ڵ�

	m_pEntity = new Entity();
	m_pEntity->parentEntity = NULL;
}

TreeUserMode::~TreeUserMode()
{
	if (m_pEntity != nullptr)
	{
		delete m_pEntity;
		m_pEntity = nullptr;
	}
}

int TreeUserMode::columnCount(const QModelIndex &parent) const
{
	//* ��ʾ����ֻ��һ������
	return 1;
}

QVariant TreeUserMode::data(const QModelIndex &index, int role) const
{
	//* �������Ч�ڵ��򷵻ؿ�����
	if (!index.isValid())
	{
		return QVariant();
	}

	//* ���Ի�ȡԭʼ����
	Entity* d = static_cast<Entity*>(index.internalPointer());
	if (d == NULL)//* û��ԭʼ�����򷵻ؿ�����
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole)//* ����ֻ������DisplayRole������
	{
		return d->name;
	}
	// check    hjc 
	if (role == Qt::CheckStateRole && index.column() == 0) //�ж���ʾ�Ķ�����checkbox������λ�ڵ�һ��
	{
		if (m_checkedList.contains(index))    //��m_checkedList�в��ң�����У���ʾcheckbox��ѡ��
		{
			return Qt::Checked;
		}
		else
		{
			return Qt::Unchecked;             //���û����ʾcheckboxû��ѡ��
		}
	}
	return QVariant();
}
bool TreeUserMode::setData(const QModelIndex &index, const QVariant &value, int role) //
{

	Entity *item = getItem(index);
	bool result = insertItem(index, item);
	if (result)
	{
		emit dataChanged(index, index);
	}
	return false;
}

Qt::ItemFlags TreeUserMode::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return 0;
	}
	if (index.column() == 0)   //����ǵ�һ�еĽ�㣬��ʹ������ʾcheckbox������
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;//Qt::ItemIsSelectable | Qt::ItemIsEditable | 
	}
	return Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled | QAbstractItemModel::flags(index);

}
Entity *TreeUserMode::getItem(const QModelIndex &index) const //
{
	if (index.isValid())
	{
		Entity *item = static_cast<Entity*>(index.internalPointer());//index.internalPointer()  QSortFilterProxyModel�ڲ�ά����ָ��
		if (item != nullptr)
		{
			return item;
		}
	}
	return m_pEntity;
}
QModelIndex TreeUserMode::index(int row, int column, const QModelIndex &parent) const
{
	////* �����ڵ��Ƿ���Ч

	if (!parent.isValid()) //* ��Ч�ĸ��ڵ�(�ǿ϶��Ƿ���)
	{
		QModelIndex groupIndex;
		if (mItemList.count() > row) //* ʹ����Ч�����ݴ���һ���ڵ�
		{
			groupIndex = createIndex(row, column, mItemList.at(row));
		}
		return groupIndex;
	}
	else //* ��Ч�ĸ��ڵ�
	{
		//* ��ȡ���ڵ������
		Entity* parentData = static_cast<Entity*>(parent.internalPointer());
		if (parentData != NULL)
		{
			if (parentData->children.count() > row) //* ʹ�ø��ڵ��µĶ�Ӧrow���Ӷ���ṹ����һ���ڵ�
			{
				QModelIndex childIndex = createIndex(row, column, parentData->children[row]);
				return childIndex;
			}
		}
	}

}

bool TreeUserMode::insertItem(const QModelIndex &parent, Entity * item)//
{
	if (parent.row() < 0 || parent.row() > mItemList.size())//position  ��row 
	{
		return false;
	}

	for (int i = 0; i < parent.row(); ++i)
	{
		mItemList.insert(i, item);
	}
	return true;
}

QModelIndex TreeUserMode::parent(const QModelIndex &index) const
{
	//* �������Ч�Ľڵ��򷵻���Ч�ڵ�
	if (!index.isValid())
	{
		return QModelIndex();
	}
	Entity* indexData = static_cast<Entity*>(index.internalPointer());
	for (int i = 0; i < mItemList.count(); i++)
	{
		if (mItemList[i] == indexData) //* ����Ǹ��ڵ㣨���飩�򷵻���Ч���ڵ㣨����û�и��ڵ㣩
		{
			return QModelIndex();
		}
		else
		{
			//* ��ͼ�жϸýڵ�ĸ��ڵ��ǲ���mItemList[i]
			for (int ii = 0; ii < mItemList[i]->children.count(); ii++)
			{
				if (indexData == mItemList[i]->children[ii]) //* mItemList[i] �ɹ�ƥ��ΪindexData�ĸ��ڵ�
				{
					//* ʹ��mItemList[i]��Ϊ���ݴ���һ�����ڵ�
					QModelIndex parentIndex = createIndex(i, 0, mItemList[i]);
					return parentIndex;
				}
			}
		}
	}

	//* δƥ�䵽��Ч�ĸ��ڵ����ݣ�������Ч�ڵ�
	return QModelIndex();
}


int TreeUserMode::rowCount(const QModelIndex &parent) const
{
	//* ���ڵ��Ƿ���Ч

	if (!parent.isValid()) //* ��Ч�ĸ��ڵ㣨˵���Ƿ��飩���ظ��ڵ����
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
QModelIndex TreeUserMode::getTopParentIndex(QModelIndex itemIndex)
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
void TreeUserMode::setEntityList(const entityViewItemList &li)
{
	mItemList = li;
	layoutChanged(); //* ֪ͨViewˢ������
}

entityViewItemList TreeUserMode::EntityList()
{
	return mItemList;
}

QVariant TreeUserMode::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	//* ֻ����header��DisplayRole����
	if (role == Qt::DisplayRole)
	{
		return QString("name");
	}
	return __super::headerData(section, orientation, role);
}
 
//��д
QMimeData * TreeUserMode::mimeData(const QModelIndexList &indexes)const
{
	QMimeData* mimeD = QAbstractItemModel::mimeData(indexes);				//�Ȼ�ȡԭʼ��mimeData;
	if (indexes.count() > 0)
	{
		mimeD->setData("drag", "mouse darg");
		QByteArray encoded;
		for (int i = 0; i < indexes.size(); ++i)
		{
			const QModelIndex index = indexes.at(i);
			if (index.isValid())
			{
				QVariant v = data(index, Qt::DisplayRole);
				encoded.append(v.toString());
			}
		}
		mimeD->setData("name", encoded);				//���Լ���Ҫ������ ���뵽MimeData��
	}
	else
	{
		mimeD->setData("name", "NULL");
	}
	return mimeD;
}
bool TreeUserMode::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{

	QByteArray st = data->data("name");
	if (action == Qt::CopyAction)
	{
		Entity* parentData = static_cast<Entity*>(parent.internalPointer());
		parentData->parent = parent;
		//parentData->name = QString::fromLocal8Bit(st);
		//insertItem(parent, parentData);
	}
	if (action == Qt::MoveAction)
	{
		setData(parent, st);
	}
	/*
	parentData->name = st;
	insertItem(parent.row(), parent.column(), parentData);*/
	m_rowCount++;
	return true;
}
QStringList TreeUserMode::mimeTypes() const
{
	QStringList  types;
	types << "drag";
	return types;
}
//�����豸���ĸ����
void TreeUserMode::setRootNode(Entity *node)
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

//��ĳ�����ڵ㣬���һ���ӽڵ㣬���parentNodeΪ�գ���ӵ����ڵ���
bool TreeUserMode::addTreeNode(Entity* pNode)
{
	if (this->treeNodeHaveEqualInfo(m_pEntity, pNode) > 0)			//���������ڵ㣬�ڸ��ڵ�������ͬIp�����������
	{
		//TODO MSG
		delete pNode;												//������Ľڵ� ��������
		return true;
	}
	this->beginResetModel();
	do
	{
		if (!pNode->parentEntity)						//parentNodeΪ�գ�ֱ�Ӽ����ڸ��ڵ���
		{
			m_pEntity->children.append(pNode);
			pNode->parentEntity = m_pEntity;
			break;
		}
	} while (0);

	//���parentNode�����е�����ϵ�У�������������ϵ��������ڣ�������ڵ���
	/*TreeNode* pNode = FindParentNode(mRootNode, pNode->mParentNode);
	if (!pNode)
	{
	mRootNode->mChildNodes.append(pNode);
	pNode->mParentNode = mRootNode;
	return true;
	}*/

	this->endResetModel();
	return true;
}

//pNode ΪҪ���ҽڵ㣬 childNode Ϊ�����ҽڵ㣬���ر����ҽڵ�ĸ��ڵ�,pNode��childNode֮���в㼶��ϵ
Entity* TreeUserMode::findParentNode(Entity* pNode, Entity* childNode)
{
	//if (!pNode)
	//	return NULL;

	//if (pNode->mChildNodes.indexOf(childNode))								//����ӽڵ������ڵĸ��ڵ㣬���ظ��ڵ�
	//	return pNode;
	//for (int i = 0; i < pNode->mChildNodes.count(); i++)
	//{
	//	return FindParentNode(pNode->mChildNodes.at(i), childNode);
	//}
	return NULL;
}

int TreeUserMode::treeNodeHaveEqualInfo(Entity* parentNode, Entity* pAddChildNode)
{
	/*for (int i = 0; i < parentNode->mChildNodes.size(); i++)
	{
	if (parentNode->mChildNodes.at(i)->mDeviceInfo.mDevIp != pAddChildNode->mDeviceInfo.mDevIp)
	continue;
	else
	return 1;
	}
	*/
	return 0;
}

//����QModelIndex������ָ���丸����ָ��
Entity* TreeUserMode::nodeFromIndex(const QModelIndex &index) const
{
	if (index.isValid())				//�������Ч���
		return static_cast<Entity*>(index.internalPointer());
	else
		return m_pEntity;
}

///////////////////////////////////////////////////////////////////////////

QAtomicPointer<MyNewTreeModeView> MyNewTreeModeView::m_pInstance = 0;
QMutex MyNewTreeModeView::m_mutex;

MyNewTreeModeView::MyNewTreeModeView(QObject *parent)
	: TreeUserMode(parent)
{

}

MyNewTreeModeView::~MyNewTreeModeView()
{

}
MyNewTreeModeView *MyNewTreeModeView::instance()
{

#ifndef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
	if (!QAtomicPointer::isTestAndSetNative())//����ʱ���
	{
		qDebug() << "Error: TestAndSetNative not supported!";
	}
#endif
	//ʹ��˫�ؼ�⡣
	/*! testAndSetOrders������֤��ԭ�Ӳ���ǰ�ͺ�ĵ��ڴ����
	* ���ᱻ��������
	*/
	if (m_pInstance.testAndSetOrdered(0, 0))//��һ�μ��
	{
		QMutexLocker locker(&m_mutex);//�ӻ�������
		m_pInstance.testAndSetOrdered(0, new MyNewTreeModeView);//�ڶ��μ�⡣
	}
	return  m_pInstance;
}