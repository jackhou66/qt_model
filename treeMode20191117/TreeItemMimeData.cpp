#include "TreeItemMimeData.h"

MyModel::MyModel(QStandardItemModel *parent)
: QStandardItemModel(parent)
{
	m_rowCount = 0;
}
 
//重写
QMimeData * MyModel::mimeData(const QModelIndexList &indexes) const
{
	if (indexes.count()<=0)
	{
		return 0;
	}
	QMimeData *data = new(std::nothrow) QMimeData;
	data->setData("drag","mouse darg");
	data->setData("team", item(indexes.at(0).row(), 0)->text().toLocal8Bit());
	data->setData("team_code", item(indexes.at(0).row(), 1)->text().toLocal8Bit());
	return data;
}
bool MyModel::dropMimeData(const QMimeData *data, Qt::DropAction action, 
																				int row, int column, const QModelIndex &parent)
{
	QString st = QString::fromLocal8Bit(data->data("team"));
	QString st1 = QString::fromLocal8Bit(data->data("team_code"));
	this->setItem(m_rowCount,0,new QStandardItem(st));
	this->setItem(m_rowCount, 1, new QStandardItem(st1));
	m_rowCount++;
	return true;
}
QStringList MyModel::mimeTypes() const
{
	QStringList  types;
	types << "drag";
	return types;
}

//所谓可见顶层是目录树的可见最顶层父节点    寻找可见顶层
QStandardItem* MyModel::getTopParentItem(QStandardItem* item, QStandardItemModel*model)
{
	QStandardItem* secondItem = item;
	while (item->parent() != 0)
	{
		secondItem = item->parent();
		item = secondItem;
	}
	if (secondItem->index().column() != 0)
	{
		QStandardItemModel* mode = static_cast<QStandardItemModel*>(model);
		secondItem = mode->itemFromIndex(secondItem->index().sibling(secondItem->index().row(), 0));
	}
	return secondItem;
}
QModelIndex MyModel::getTopParentIndex(QModelIndex itemIndex)
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


bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role == Qt::CheckStateRole && index.column() == 0)
	{
		if (value == Qt::Unchecked)
		{
			m_checkedList.removeOne(index);
			emit(dataChanged(index, index));
		}
		else if (value == Qt::Checked)
		{
			m_checkedList.append(index);
			emit(dataChanged(index, index));
		}
		int childCount = rowCount(index);
		if (childCount>0)                    //判断是否有子节点
		{
			for (int i = 0; i<childCount; i++)
			{
				QModelIndex child = this->index(i, 0, index); //获得子节点的index
				setData(child, value, Qt::CheckStateRole);    //递归，将子节点的checkbox设为选中状态
			}
		}
	}
	return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	if (index.column() == 0)   //如果是第一列的结点，则使其有显示checkbox的能力
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}
QVariant MyModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role == Qt::CheckStateRole && index.column() == 0) //判断显示的对象是checkbox，并且位于第一列
	{
		if (m_checkedList.contains(index))    //在m_checkedList中查找，如果有，显示checkbox被选中
			return Qt::Checked;
		else
			return Qt::Unchecked;             //如果没有显示checkbox没被选中
	}
	if (role != Qt::DisplayRole)
		return QVariant();
	QStandardItem *item = static_cast<QStandardItem*>(index.internalPointer());
	return item->data(index.column());
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

//实现QStandardItemModel的通用遍历函数
//函数ergodicAllItem用于遍历所有项目，ergodicItem用于遍历项目下的所有子项目。
//回调函数返回bool用于决定是否继续，如果为true就继续遍历，如果为false就停止遍历
////////////////////////////////////////////////////////////////////////////////////////////////////////

void QStandardItemModelEx::ergodicAllItem(QStandardItemModel* model, callback_ergodicFun_ptr pFun)
{
	int rows = model->rowCount();
	int column = model->columnCount();
	for (int i = 0; i<rows; ++i)
	{
		for (int j = 0; j<column; ++j)
		{
			QStandardItem* item = model->item(i, j);
			if (item)
			{
				if (!ergodicItem(item, pFun))
				{
					return;
				}
			}
		}
	}
}

bool QStandardItemModelEx::ergodicItem(QStandardItem* item, callback_ergodicFun_ptr pFun)
{
	int rows = item->rowCount();
	int column = item->columnCount();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			QStandardItem* childItem = item->child(i, j);
			if (childItem)
			{
				if (!ergodicItem(childItem, pFun))
				{
					return false;
				}
			}
		}
	}
	return pFun(item);
}

//下面举一个例子
//例子功能是通过关键字高亮条目。在使用QTreeView或QTableView时，在条目多的情况下，需要搜索某些条目，对搜索结果进行高亮，
//这时，就需要遍历整个View里的条目，对符合的条目进行高亮
//遍历的函数已经写好，现在缺少的是回调的函数，由于遍历的函数使用的函数指针是std::function，因此回调函数即可写为全局函数也可以写为类成员函数
//回调函数声明：
bool MyModel::is_match_string(const QString str, const QStringList keys)
{
	for (auto strtemp : keys)
	{
		if (str == strtemp)
		{
			return true;
		}			
	}
	return false;
}
bool MyModel::callback_hightLightItem(QStandardItem* item, const QStringList keys)
{
	QString str = item->text();
	if (is_match_string(str, keys))
	{
		item->setData(QVariant(QColor(237, 100, 100, 180)), Qt::BackgroundRole);
	}
	else
	{
		item->setData(QVariant(), Qt::BackgroundRole);
	}
	return true;
}



////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

MyNewModel::MyNewModel(QStandardItemModel *parent)
	: QStandardItemModel(parent)
{
	m_rowCount = 0;
}

//重写
QMimeData * MyNewModel::mimeData(const QModelIndexList &indexes) const
{
	if (indexes.count() <= 0)
	{
		return 0;
	}
	QMimeData *data = new(std::nothrow) QMimeData;
	data->setData("drag", "mouse darg");
	data->setData("team", item(indexes.at(0).row(), 0)->text().toLocal8Bit());
	data->setData("team_code", item(indexes.at(0).row(), 1)->text().toLocal8Bit());
	return data;
}
bool MyNewModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
	int row, int column, const QModelIndex &parent)
{
	QString st = QString::fromLocal8Bit(data->data("team"));
	QString st1 = QString::fromLocal8Bit(data->data("team_code"));
	this->setItem(m_rowCount, 0, new QStandardItem(st));
	this->setItem(m_rowCount, 1, new QStandardItem(st1));
	m_rowCount++;
	return true;
}
QStringList MyNewModel::mimeTypes() const
{
	QStringList  types;
	types << "drag";
	return types;
}

//所谓可见顶层是目录树的可见最顶层父节点    寻找可见顶层
QStandardItem* MyNewModel::getTopParentItem(QStandardItem* item, QStandardItemModel*model)
{
	QStandardItem* secondItem = item;
	while (item->parent() != 0)
	{
		secondItem = item->parent();
		item = secondItem;
	}
	if (secondItem->index().column() != 0)
	{
		QStandardItemModel* mode = static_cast<QStandardItemModel*>(model);
		secondItem = mode->itemFromIndex(secondItem->index().sibling(secondItem->index().row(), 0));
	}
	return secondItem;
}
QModelIndex MyNewModel::getTopParentIndex(QModelIndex itemIndex)
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


bool MyNewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role == Qt::CheckStateRole && index.column() == 0)
	{
		if (value == Qt::Unchecked)
		{
			m_checkedList.removeOne(index);
			emit(dataChanged(index, index));
		}
		else if (value == Qt::Checked)
		{
			m_checkedList.append(index);
			emit(dataChanged(index, index));
		}
		int childCount = rowCount(index);
		if (childCount>0)                    //判断是否有子节点
		{
			for (int i = 0; i<childCount; i++)
			{
				QModelIndex child = this->index(i, 0, index); //获得子节点的index
				setData(child, value, Qt::CheckStateRole);    //递归，将子节点的checkbox设为选中状态
			}
		}
	}
	return false;
}

Qt::ItemFlags MyNewModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	if (index.column() == 0)   //如果是第一列的结点，则使其有显示checkbox的能力
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}
QVariant MyNewModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role == Qt::CheckStateRole && index.column() == 0) //判断显示的对象是checkbox，并且位于第一列
	{
		if (m_checkedList.contains(index))    //在m_checkedList中查找，如果有，显示checkbox被选中
			return Qt::Checked;
		else
			return Qt::Unchecked;             //如果没有显示checkbox没被选中
	}
	if (role != Qt::DisplayRole)
		return QVariant();
	QStandardItem *item = static_cast<QStandardItem*>(index.internalPointer());
	return item->data(index.column());
}