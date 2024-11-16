#include "TreeModel.h"
#include <QtWidgets>

#include "treeitem.h"
TreeModel::TreeModel(QObject *parent)
: QAbstractItemModel(parent)
{
	
	this->m_pEntity = NULL;
	//����һ�����ڵ㣬��Qt�и��ڵ�ĸ��ڵ�Ϊ�գ�Ĭ�ϲ���ʾ������һ���սڵ�䵱���ڵ�
	m_pEntity = new Entity();
	m_pEntity->parentEntity = NULL;

}

TreeModel::~TreeModel()
{
	if (m_pEntity != nullptr)
	{
		delete m_pEntity;
		m_pEntity = nullptr;
	}
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
	//* ��ʾ����ֻ��һ������
	return 1;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
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
	//if (role == Qt::CheckStateRole && index.column() == 0) //�ж���ʾ�Ķ�����checkbox������λ�ڵ�һ��
	//{
	//	if (m_checkedList.contains(index))    //��m_checkedList�в��ң�����У���ʾcheckbox��ѡ��
	//	{
	//		return Qt::Checked;
	//	}
	//	else
	//	{
	//		return Qt::Unchecked;             //���û����ʾcheckboxû��ѡ��
	//	}
	//}
	return QVariant();
}
bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role) //
{
 
	Entity *item = getItem(index);
	/*bool result = insertItem(index, item);
	if (result)
	{
		emit dataChanged(index, index);
	}*/

	//if (role == Qt::CheckStateRole && index.column() == 0)
	//{
	//	if (value == Qt::Unchecked)
	//	{
	//		m_checkedList.removeOne(index);
	//		emit(dataChanged(index, index));
	//	}
	//	else if (value == Qt::Checked)
	//	{
	//		m_checkedList.append(index);
	//		emit(dataChanged(index, index));
	//	}
	//	int childCount = rowCount(index);
	//	if (childCount>0)                    //�ж��Ƿ����ӽڵ�  dataChanged�źŻᴥ����Ӧ�Ĳۺ��������һ���õ�data()���������������¼����������״̬
	//	{
	//		for (int i = 0; i<childCount; i++)
	//		{
	//			QModelIndex child = this->index(i, 0, index); //����ӽڵ��index
	//			setData(child, value, Qt::CheckStateRole);    //�ݹ飬���ӽڵ��checkbox��Ϊѡ��״̬
	//		}
	//	}
	//}
	return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return 0;
	}
	if (index.column() == 0)   //����ǵ�һ�еĽ�㣬��ʹ������ʾcheckbox������
	{
		return   Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;//| Qt::ItemIsUserCheckableQt::ItemIsEnabled | Qt::ItemIsSelectable  |Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | 
	}
	return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled  | Qt::ItemIsSelectable | Qt::ItemIsEnabled ;// | Qt::ItemIsUserCheckable;| QAbstractItemModel::flags(index)
	//|Qt::ItemIsEnabled
}
Entity *TreeModel::getItem(const QModelIndex &index) const //
{
	if (index.isValid())
	{
		Entity *item = static_cast<Entity*>(index.internalPointer());//index.internalPointer()  QSortFilterProxyModel�ڲ�ά����ָ��
		if (item!=nullptr)
		{
			return item;
		}
	}
	return m_pEntity;
}
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
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
bool TreeModel::removeRows(int position, int rows, const QModelIndex &index)
{
	//qDebug() << "in removeRows";
	beginRemoveRows(index, 0, position + rows - 1);
    endRemoveRows();
	return true;
	//return removeRows(rows, 1, index);
}
bool TreeModel::insertItem(int position, int rows, const QModelIndex &index, Entity * item)//
{
	beginInsertRows(index, position, position+index.row() - 1);
	endInsertRows();
	return true;
	
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
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


int TreeModel::rowCount(const QModelIndex &parent) const
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
	layoutChanged(); //* ֪ͨViewˢ������
}

entityViewItemList TreeModel::EntityList()
{
	return mItemList;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	//* ֻ����header��DisplayRole����
	if (role == Qt::DisplayRole)
	{
		return QString("name");
	}
	return __super::headerData(section, orientation, role);
}

//void TreeModel::treeItemChanged(Entity * item)
//{
//	if (item == nullptr)
//	{
//		return;
//	}
//	if (item->isCheckable())
//	{
//		//�����Ŀ�Ǵ��ڸ�ѡ��ģ���ô�ͽ�������Ĳ���
//		Qt::CheckState state = item->checkState(); //��ȡ��ǰ��ѡ��״̬
//		if (item->isTristate())
//		{
//			//�����Ŀ����̬�ģ�˵�����Զ���Ŀ¼����ȫѡ��ȫ��ѡ������
//			if (state != Qt::PartiallyChecked)
//			{
//				//��ǰ��ѡ��״̬����Ҫ��������Ŀ����ȫѡ
//				treeItem_checkAllChild(item, state == Qt::Checked ? true : false);
//			}
//		}
//		else
//		{
//			//˵������̬�ģ���̬��Ը�������̬��Ӱ��
//			//�ж��ֵܽڵ�����
//			treeItem_CheckChildChanged(item);
//		}
//	}
//}

//��д
QMimeData * TreeModel::mimeData(const QModelIndexList &indexes) const
{ 
 
	//data->setData("drag", "mouse darg");
	//data->setData("team", item(indexes.at(0).row(), 0)->text().toLocal8Bit());
	//QModelIndex index = indexes.at(0);
	QMimeData* mimeD = QAbstractItemModel::mimeData(indexes);				//�Ȼ�ȡԭʼ��mimeData;
	if (indexes.count() > 0)
	{	
		mimeD->setData("drag", "mouse darg"); 
		QByteArray encoded;
		for (int i = 0; i < indexes.size();++i)
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
bool TreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{

		QByteArray st = data->data("name");
		if (action==Qt::CopyAction)
		{
			Entity* parentData = static_cast<Entity*>(parent.internalPointer());
			parentData->name = QString::fromLocal8Bit(st);	
			removeRows(column, row,parent);
		}
		if (action == Qt::MoveAction)
		{
			setData(parent, st);
		}
      m_rowCount++;
      return true; 
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
	if (m_pEntity!=nullptr)
	{
		delete m_pEntity;
		m_pEntity = nullptr;
	}
	m_pEntity = node;
	endResetModel();
}
 
//��ĳ�����ڵ㣬���һ���ӽڵ㣬���parentNodeΪ�գ���ӵ����ڵ���
bool TreeModel::addTreeNode(Entity* pNode)
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
Entity* TreeModel::findParentNode(Entity* pNode, Entity* childNode)
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

int TreeModel::treeNodeHaveEqualInfo(Entity* parentNode, Entity* pAddChildNode)
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
Entity* TreeModel::nodeFromIndex(const QModelIndex &index) const
{
	if (index.isValid())				//�������Ч���
		return static_cast<Entity*>(index.internalPointer());
	else
		return m_pEntity;
}
 
///////////////////////////////////////////////////////////////////////////////

///
/// \brief �ݹ��������е�����ĿΪȫѡ��ȫ��ѡ״̬
/// \param item ��ǰ��Ŀ
/// \param check trueʱΪȫѡ��falseʱȫ��ѡ
///
//void TreeModel::treeItem_checkAllChild(Entity * item, bool check)
//{
//	if (item == nullptr)
//	{
//		return;
//	}
//	int rowCount = item->children.count();
//	for (int i = 0; i<rowCount; ++i)
//	{
//		Entity* parentData = mItemList[i];
//		treeItem_checkAllChild_recursion(parentData, check);
//	}
//	if (item->isCheckable())
//	{
//		item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
//	}
//}
//void TreeModel::treeItem_checkAllChild_recursion(Entity * item, bool check)
//{
//	if (item == nullptr)
//	{
//		return;
//	}
//	int rowCount = item->children.count();
//	for (int i = 0; i<rowCount; ++i)
//	{
//		Entity* parentData = mItemList[i];
//		treeItem_checkAllChild_recursion(parentData, check);
//	}
//	if (item->isCheckable())
//	{
//		item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
//	}
//}
//2.2.2 ���ڵ�ݹ鴦��
///
/// \brief �����ӽڵ�ĸı䣬���ĸ��ڵ��ѡ�����
/// \param item
///
//void TreeModel::treeItem_CheckChildChanged(Entity * item)
//{
//	if (nullptr == item)
//	{
//		return;
//	}
//	Qt::CheckState siblingState = checkSibling(item);
//	if (nullptr == item)
//	{
//		return;
//	}
//	if (Qt::PartiallyChecked == siblingState)
//	{
//		if (item->isCheckable() && item->isTristate())
//		{
//			item->setCheckState(Qt::PartiallyChecked);
//		}
//	}
//	else if (Qt::Checked == siblingState)
//	{
//		if (item->isCheckable())
//		{
//			item->setCheckState(Qt::Checked);
//		}
//
//	}
//	else
//	{
//		if (item->isCheckable())
//		{
//			item->setCheckState(Qt::Unchecked);
//		}
//	}
//	treeItem_CheckChildChanged(item);
//}

/// \brief �����ֵܽڵ������������ѡ�з���Qt::Checked������ѡ��Qt::Unchecked,����ȫѡ�з���Qt::PartiallyChecked
/// \param item
/// \return �����ѡ�з���Qt::Checked������ѡ��Qt::Unchecked,����ȫѡ�з���Qt::PartiallyChecked
///s
//Qt::CheckState TreeModel::checkSibling(Entity * item)
//{
//	//��ͨ�����ڵ��ȡ�ֵܽڵ�
//	QStandardItem * parent =item;
//	if (nullptr == parent)
//	{
//		return item->checkState();
//	}
//	int brotherCount = parent->rowCount();
//	int checkedCount(0);
//	int unCheckedCount(0);
//	Qt::CheckState state;
//	for (int i = 0; i<brotherCount; ++i)
//	{
//		QStandardItem* siblingItem = parent->child(i);
//		state = siblingItem->checkState();
//		if (Qt::PartiallyChecked == state)
//		{
//			return Qt::PartiallyChecked;
//		}
//
//		else if (Qt::Unchecked == state)
//		{
//			++unCheckedCount;
//		}
//
//		else
//		{
//			++checkedCount;
//		}
//		if (checkedCount>0 && unCheckedCount>0)
//		{
//			return Qt::PartiallyChecked;
//		}
//	}
//	if (unCheckedCount>0)
//	{
//		return Qt::Unchecked;
//	}
//	return Qt::Checked;
//}
//
entityViewItemList TreeModel::getEntityDataList() const
{
	return mItemList;
}
//ʵ����ק����  /////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
//QAtomicPointer<NewTreeMode> NewTreeMode::m_pInstance = 0;
//QMutex NewTreeMode::m_mutex;
//
//NewTreeMode::NewTreeMode(QObject *parent)
//	: TreeModel(parent)
//{
// 
//}
//
//NewTreeMode::~NewTreeMode()
//{
//
//}
//NewTreeMode *NewTreeMode::instance()
//{
//
//#ifndef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
//	if (!QAtomicPointer::isTestAndSetNative())//����ʱ���
//	{
//		qDebug() << "Error: TestAndSetNative not supported!";
//
//	}
//
//#endif
//	//ʹ��˫�ؼ�⡣
//	/*! testAndSetOrders������֤��ԭ�Ӳ���ǰ�ͺ�ĵ��ڴ����
//	* ���ᱻ��������
//	*/
//	if (m_pInstance.testAndSetOrdered(0, 0))//��һ�μ��
//	{
//		QMutexLocker locker(&m_mutex);//�ӻ�������
//
//		m_pInstance.testAndSetOrdered(0, new NewTreeMode);//�ڶ��μ�⡣
//	}
//	return  m_pInstance;
//}
/////////////////////////////////////////////////////////////////////////////
//
//QAtomicPointer<NewTreeModeView> NewTreeModeView::m_pInstance = 0;
//QMutex NewTreeModeView::m_mutex;
//
//NewTreeModeView::NewTreeModeView(QObject *parent)
//	: TreeModel(parent)
//{
//
//}
//
//NewTreeModeView::~NewTreeModeView()
//{
//
//}
//NewTreeModeView *NewTreeModeView::instance()
//{
//
//#ifndef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
//	if (!QAtomicPointer::isTestAndSetNative())//����ʱ���
//	{
//		qDebug() << "Error: TestAndSetNative not supported!";
//	}
//#endif
//	//ʹ��˫�ؼ�⡣
//	/*! testAndSetOrders������֤��ԭ�Ӳ���ǰ�ͺ�ĵ��ڴ����
//	* ���ᱻ��������
//	*/
//	if (m_pInstance.testAndSetOrdered(0, 0))//��һ�μ��
//	{
//		QMutexLocker locker(&m_mutex);//�ӻ�������
//		m_pInstance.testAndSetOrdered(0, new NewTreeModeView);//�ڶ��μ�⡣
//	}
//	return  m_pInstance;
//}
