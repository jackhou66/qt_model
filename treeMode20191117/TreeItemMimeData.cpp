#include "TreeItemMimeData.h"

MyModel::MyModel(QStandardItemModel *parent)
: QStandardItemModel(parent)
{
	m_rowCount = 0;
}
 
//��д
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

//��ν�ɼ�������Ŀ¼���Ŀɼ���㸸�ڵ�    Ѱ�ҿɼ�����
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
		if (childCount>0)                    //�ж��Ƿ����ӽڵ�
		{
			for (int i = 0; i<childCount; i++)
			{
				QModelIndex child = this->index(i, 0, index); //����ӽڵ��index
				setData(child, value, Qt::CheckStateRole);    //�ݹ飬���ӽڵ��checkbox��Ϊѡ��״̬
			}
		}
	}
	return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	if (index.column() == 0)   //����ǵ�һ�еĽ�㣬��ʹ������ʾcheckbox������
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}
QVariant MyModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role == Qt::CheckStateRole && index.column() == 0) //�ж���ʾ�Ķ�����checkbox������λ�ڵ�һ��
	{
		if (m_checkedList.contains(index))    //��m_checkedList�в��ң�����У���ʾcheckbox��ѡ��
			return Qt::Checked;
		else
			return Qt::Unchecked;             //���û����ʾcheckboxû��ѡ��
	}
	if (role != Qt::DisplayRole)
		return QVariant();
	QStandardItem *item = static_cast<QStandardItem*>(index.internalPointer());
	return item->data(index.column());
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

//ʵ��QStandardItemModel��ͨ�ñ�������
//����ergodicAllItem���ڱ���������Ŀ��ergodicItem���ڱ�����Ŀ�µ���������Ŀ��
//�ص���������bool���ھ����Ƿ���������Ϊtrue�ͼ������������Ϊfalse��ֹͣ����
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

//�����һ������
//���ӹ�����ͨ���ؼ��ָ�����Ŀ����ʹ��QTreeView��QTableViewʱ������Ŀ�������£���Ҫ����ĳЩ��Ŀ��������������и�����
//��ʱ������Ҫ��������View�����Ŀ���Է��ϵ���Ŀ���и���
//�����ĺ����Ѿ�д�ã�����ȱ�ٵ��ǻص��ĺ��������ڱ����ĺ���ʹ�õĺ���ָ����std::function����˻ص���������дΪȫ�ֺ���Ҳ����дΪ���Ա����
//�ص�����������
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

//��д
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

//��ν�ɼ�������Ŀ¼���Ŀɼ���㸸�ڵ�    Ѱ�ҿɼ�����
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
		if (childCount>0)                    //�ж��Ƿ����ӽڵ�
		{
			for (int i = 0; i<childCount; i++)
			{
				QModelIndex child = this->index(i, 0, index); //����ӽڵ��index
				setData(child, value, Qt::CheckStateRole);    //�ݹ飬���ӽڵ��checkbox��Ϊѡ��״̬
			}
		}
	}
	return false;
}

Qt::ItemFlags MyNewModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	if (index.column() == 0)   //����ǵ�һ�еĽ�㣬��ʹ������ʾcheckbox������
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}
QVariant MyNewModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role == Qt::CheckStateRole && index.column() == 0) //�ж���ʾ�Ķ�����checkbox������λ�ڵ�һ��
	{
		if (m_checkedList.contains(index))    //��m_checkedList�в��ң�����У���ʾcheckbox��ѡ��
			return Qt::Checked;
		else
			return Qt::Unchecked;             //���û����ʾcheckboxû��ѡ��
	}
	if (role != Qt::DisplayRole)
		return QVariant();
	QStandardItem *item = static_cast<QStandardItem*>(index.internalPointer());
	return item->data(index.column());
}