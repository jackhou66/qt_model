#include "TreeModel.h"
#include <QtWidgets>

#include "treeitem.h"
TreeModel::TreeModel(QObject *parent)
: QAbstractItemModel(parent)
{
	
	this->m_pEntity = NULL;
	//构造一个根节点，在Qt中根节点的父节点为空，默认不显示，构造一个空节点充当父节点
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
	//* 本示例中只有一列数据
	return 1;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	//* 如果是无效节点则返回空数据
	if (!index.isValid())
	{
		return QVariant();
	}

	//* 尝试获取原始数据
	Entity* d = static_cast<Entity*>(index.internalPointer());
	if (d == NULL)//* 没有原始数据则返回空数据
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole)//* 本例只返回了DisplayRole的数据
	{
		return d->name;
	}
	// check    hjc 
	//if (role == Qt::CheckStateRole && index.column() == 0) //判断显示的对象是checkbox，并且位于第一列
	//{
	//	if (m_checkedList.contains(index))    //在m_checkedList中查找，如果有，显示checkbox被选中
	//	{
	//		return Qt::Checked;
	//	}
	//	else
	//	{
	//		return Qt::Unchecked;             //如果没有显示checkbox没被选中
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
	//	if (childCount>0)                    //判断是否有子节点  dataChanged信号会触发相应的槽函数，并且会调用到data()函数，这样会重新加载这个结点的状态
	//	{
	//		for (int i = 0; i<childCount; i++)
	//		{
	//			QModelIndex child = this->index(i, 0, index); //获得子节点的index
	//			setData(child, value, Qt::CheckStateRole);    //递归，将子节点的checkbox设为选中状态
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
	if (index.column() == 0)   //如果是第一列的结点，则使其有显示checkbox的能力
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
		Entity *item = static_cast<Entity*>(index.internalPointer());//index.internalPointer()  QSortFilterProxyModel内部维护的指针
		if (item!=nullptr)
		{
			return item;
		}
	}
	return m_pEntity;
}
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	////* 看父节点是否有效

	if (!parent.isValid()) //* 无效的父节点(那肯定是分组)
	{
		QModelIndex groupIndex;
		if (mItemList.count() > row) //* 使用有效的数据创建一个节点
		{
			groupIndex = createIndex(row, column, mItemList.at(row));
		}
		return groupIndex;
	}
	else //* 有效的父节点
	{
		//* 获取父节点的数据
		Entity* parentData = static_cast<Entity*>(parent.internalPointer());
		if (parentData != NULL)
		{
			if (parentData->children.count() > row) //* 使用父节点下的对应row的子对象结构创建一个节点
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
	//* 如果是无效的节点则返回无效节点
	if (!index.isValid())
	{
		return QModelIndex();
	}
	Entity* indexData = static_cast<Entity*>(index.internalPointer());
	for (int i = 0; i < mItemList.count(); i++)
	{
		if (mItemList[i] == indexData) //* 如果是父节点（分组）则返回无效父节点（分组没有父节点）
		{
			return QModelIndex();
		}
		else
		{
			//* 试图判断该节点的父节点是不是mItemList[i]
			for (int ii = 0; ii < mItemList[i]->children.count(); ii++)
			{
				if (indexData == mItemList[i]->children[ii]) //* mItemList[i] 成功匹配为indexData的父节点
				{
					//* 使用mItemList[i]作为数据创建一个父节点
					QModelIndex parentIndex = createIndex(i, 0, mItemList[i]);
					return parentIndex;
				}
			}
		}
	}

	//* 未匹配到有效的父节点数据，返回无效节点
	return QModelIndex();
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
	//* 父节点是否有效

	if (!parent.isValid()) //* 无效的父节点（说明是分组）返回父节点个数
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
	layoutChanged(); //* 通知View刷新数据
}

entityViewItemList TreeModel::EntityList()
{
	return mItemList;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	//* 只返回header的DisplayRole数据
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
//		//如果条目是存在复选框的，那么就进行下面的操作
//		Qt::CheckState state = item->checkState(); //获取当前的选择状态
//		if (item->isTristate())
//		{
//			//如果条目是三态的，说明可以对子目录进行全选和全不选的设置
//			if (state != Qt::PartiallyChecked)
//			{
//				//当前是选中状态，需要对其子项目进行全选
//				treeItem_checkAllChild(item, state == Qt::Checked ? true : false);
//			}
//		}
//		else
//		{
//			//说明是两态的，两态会对父级的三态有影响
//			//判断兄弟节点的情况
//			treeItem_CheckChildChanged(item);
//		}
//	}
//}

//重写
QMimeData * TreeModel::mimeData(const QModelIndexList &indexes) const
{ 
 
	//data->setData("drag", "mouse darg");
	//data->setData("team", item(indexes.at(0).row(), 0)->text().toLocal8Bit());
	//QModelIndex index = indexes.at(0);
	QMimeData* mimeD = QAbstractItemModel::mimeData(indexes);				//先获取原始的mimeData;
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
		mimeD->setData("name", encoded);				//将自己需要的数据 存入到MimeData中
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
//设置设备树的根结点
void TreeModel::setRootNode(Entity *node)
{
	//要更新model数据时，先调用beginResetModel,结束时调用endResetModel，所有绑定在Model上的视图都会更新
	this->beginResetModel();
	if (m_pEntity!=nullptr)
	{
		delete m_pEntity;
		m_pEntity = nullptr;
	}
	m_pEntity = node;
	endResetModel();
}
 
//往某个父节点，添加一个子节点，如果parentNode为空，添加到父节点下
bool TreeModel::addTreeNode(Entity* pNode)
{
	if (this->treeNodeHaveEqualInfo(m_pEntity, pNode) > 0)			//如果待加入节点，在根节点中有相同Ip，不允许加入
	{
		//TODO MSG
		delete pNode;												//不加入的节点 析构掉。
		return true;
	}
	this->beginResetModel();
	do
	{
		if (!pNode->parentEntity)						//parentNode为空，直接加载在根节点下
		{
			m_pEntity->children.append(pNode);
			pNode->parentEntity = m_pEntity;
			break;
		}
	} while (0);

	//如果parentNode在现有的树体系中，加入现有树体系，如果不在，加入根节点中
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

//pNode 为要查找节点， childNode 为被查找节点，返回被查找节点的父节点,pNode和childNode之间有层级关系
Entity* TreeModel::findParentNode(Entity* pNode, Entity* childNode)
{
	//if (!pNode)
	//	return NULL;

	//if (pNode->mChildNodes.indexOf(childNode))								//如果子节点在所在的父节点，返回父节点
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

//根据QModelIndex，返回指向其父结点的指针
Entity* TreeModel::nodeFromIndex(const QModelIndex &index) const
{
	if (index.isValid())				//如果是有效结点
		return static_cast<Entity*>(index.internalPointer());
	else
		return m_pEntity;
}
 
///////////////////////////////////////////////////////////////////////////////

///
/// \brief 递归设置所有的子项目为全选或全不选状态
/// \param item 当前项目
/// \param check true时为全选，false时全不选
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
//2.2.2 父节点递归处理
///
/// \brief 根据子节点的改变，更改父节点的选择情况
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

/// \brief 测量兄弟节点的情况，如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
/// \param item
/// \return 如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
///s
//Qt::CheckState TreeModel::checkSibling(Entity * item)
//{
//	//先通过父节点获取兄弟节点
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
//实现拖拽功能  /////////////////////////////////////////////////////////////////////////////////////////////////////
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
//	if (!QAtomicPointer::isTestAndSetNative())//运行时检测
//	{
//		qDebug() << "Error: TestAndSetNative not supported!";
//
//	}
//
//#endif
//	//使用双重检测。
//	/*! testAndSetOrders操作保证在原子操作前和后的的内存访问
//	* 不会被重新排序。
//	*/
//	if (m_pInstance.testAndSetOrdered(0, 0))//第一次检测
//	{
//		QMutexLocker locker(&m_mutex);//加互斥锁。
//
//		m_pInstance.testAndSetOrdered(0, new NewTreeMode);//第二次检测。
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
//	if (!QAtomicPointer::isTestAndSetNative())//运行时检测
//	{
//		qDebug() << "Error: TestAndSetNative not supported!";
//	}
//#endif
//	//使用双重检测。
//	/*! testAndSetOrders操作保证在原子操作前和后的的内存访问
//	* 不会被重新排序。
//	*/
//	if (m_pInstance.testAndSetOrdered(0, 0))//第一次检测
//	{
//		QMutexLocker locker(&m_mutex);//加互斥锁。
//		m_pInstance.testAndSetOrdered(0, new NewTreeModeView);//第二次检测。
//	}
//	return  m_pInstance;
//}
