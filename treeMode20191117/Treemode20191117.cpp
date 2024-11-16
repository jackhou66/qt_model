#include "Treemode20191117.h"
#include <QtWidgets/QApplication>
#include  <QDesktopWidget>
#include  <QPushButton>
#include <qDebug>

TreeMode20191117::TreeMode20191117(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//this->setMaximumSize(QSize(QApplication::desktop()->width(), QApplication::desktop()->height()));
	//Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint
	//this->setWindowState(Qt::WindowMaximized);
	showMinimized();
	this->setWindowState(Qt::WindowMinimized);
	this->resize(400, 400);
	//弹出 view  MyModelWidget  *m_pMyModelWidget;
	connect(ui.pushButton, &QPushButton::clicked, this, &TreeMode20191117::slotShowNewTreeView);

	connect(ui.pushButton_3, &QPushButton::clicked, this, &TreeMode20191117::slotShowNewTreeView);

	//搜索按钮

	m_pTreeViewSearchLine = new(std::nothrow) TreeViewSearchLine(this);
	m_pTreeViewSearchLine->hide();
	connect(ui.lineEdit, &TreeViewSearchLine::searchTextToTreeView, this, &TreeMode20191117::onSearchButtonclicked);
	//ui.comboBox->

	//继承自  class MyModel : public QStandardItemModel    11.17 晚上
	initStandardItemModelTreeView();
	initStandardItemModelTreeViewSun();
	entityViewItemList fli;
	for (int i = 0; i < 2; i++)
	{
		Entity* gi = new Entity;
		gi->armyType = (ArmyType)1;
		gi->plantType = (PlantType)1;
		gi->devicetype = (DviceType)1;

		if (i == 0)
		{
			gi->name = tr("Red");
			for (int m = 0; m< 2; m++)
			{
				Entity*ff = new Entity;
				ff->EntityId = "2";
				ff->name = tr("Red_soder");
				ff->armyType = (ArmyType)1;
				ff->plantType = (PlantType)1;
				ff->devicetype = (DviceType)1;
				ff->parameter.ParameterId = "1";
				ff->parameter.devicetype = (DviceType)2;
				ff->parameter.Azimuth = "22";
				ff->parameter.name = "777";
				gi->children << ff;
			}
		}
		else
		{
			gi->name = tr("Blue");
			gi->EntityId = "1";
			for (int ii = 0; ii < 1; ii++)
			{
				Entity* ci = new Entity;
				ci->EntityId = "2";
				ci->name = tr("Blue_soder_1");
				ci->armyType = (ArmyType)1;
				ci->plantType = (PlantType)1;
				ci->devicetype = (DviceType)1;
				ci->parameter.ParameterId = "1";
				ci->parameter.devicetype = (DviceType)2;
				ci->parameter.Azimuth = "22";
				for (int k = 0; k<1; k++)
				{
					Entity*di = new Entity;
					di->EntityId = "3";
					di->name = tr("Blue_soder_2");
					di->armyType = (ArmyType)4;
					di->plantType = (PlantType)4;
					di->devicetype = (DviceType)4;
					if (k == 1)
					{
						di->parameter.ParameterId = "44";
						di->parameter.devicetype = (DviceType)1;
						di->parameter.Azimuth = "88";
					}
					for (int p = 0; p < 1; p++)
					{
						Entity*ee = new Entity;
						ee->EntityId = "4";
						ee->name = tr("Blue_Red_soder_1");
						ee->armyType = (ArmyType)5;
						ee->plantType = (PlantType)5;
						ee->devicetype = (DviceType)5;
						di->children << ee;
					}
					ci->children << di;
				}
				gi->children << ci;
			}

		}
		fli << gi;
	}
	m_pMyTreeItemModel = new MyTreeItemModel(ui.treeView, fli);
	ui.treeView->setModel(m_pMyTreeItemModel);
	ui.treeView->setDragDropMode(QAbstractItemView::DragDrop);

	ui.treeView_2->setModel(m_pMyTreeItemModel);
	ui.treeView_2->setDragDropMode(QAbstractItemView::DropOnly);
}

TreeMode20191117::~TreeMode20191117()
{

}
//展示第二个treeView  11.17
void  TreeMode20191117::slotShowNewTreeView()
{
	FriendViewItemList mItemList;
	m_pMyModelWidget = new MyModelWidget(); \
	this->hide();
	m_pMyModelWidget->show();
}

//继承自标准的itemMode
void  TreeMode20191117::initStandardItemModelTreeView()
{
	 
}
//继承自标准的itemMode 的可拖动副本
void  TreeMode20191117::initStandardItemModelTreeViewSun()
{
	//m_model2 = new MyModel;
	//m_model2->setColumnCount(2);
	//m_model2->setHorizontalHeaderItem(0, new QStandardItem("team"));
	//m_model2->setHorizontalHeaderItem(1, new QStandardItem("team_code"));
	//ui.treeView_2->setModel(m_model2);
	//ui.treeView_2->setDragDropMode(QAbstractItemView::DropOnly);
}
void TreeMode20191117::treeItemChanged(QStandardItem * item)
{
	if (item == nullptr)
	{
		return;
	}
	if (item->isCheckable())
	{
		//如果条目是存在复选框的，那么就进行下面的操作
		Qt::CheckState state = item->checkState(); //获取当前的选择状态
		if (item->isTristate())
		{
			//如果条目是三态的，说明可以对子目录进行全选和全不选的设置
			if (state != Qt::PartiallyChecked)
			{
				//当前是选中状态，需要对其子项目进行全选
				treeItem_checkAllChild(item, state == Qt::Checked ? true : false);
			}
		}
		else
		{
			//说明是两态的，两态会对父级的三态有影响
			//判断兄弟节点的情况
			treeItem_CheckChildChanged(item);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

///
/// \brief 递归设置所有的子项目为全选或全不选状态
/// \param item 当前项目
/// \param check true时为全选，false时全不选
///
void TreeMode20191117::treeItem_checkAllChild(QStandardItem * item, bool check)
{
	if (item == nullptr)
	{
		return;
	}
	int rowCount = item->rowCount();
	for (int i = 0; i<rowCount; ++i)
	{
		QStandardItem* childItems = item->child(i);
		treeItem_checkAllChild_recursion(childItems, check);
	}
	if (item->isCheckable())
	{
		item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
	}
}
void TreeMode20191117::treeItem_checkAllChild_recursion(QStandardItem * item, bool check)
{
	if (item == nullptr)
	{
		return;
	}
	int rowCount = item->rowCount();
	for (int i = 0; i<rowCount; ++i)
	{
		QStandardItem* childItems = item->child(i);
		treeItem_checkAllChild_recursion(childItems, check);
	}
	if (item->isCheckable())
	{
		item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
	}
}


//2.2.2 父节点递归处理


///
/// \brief 根据子节点的改变，更改父节点的选择情况
/// \param item
///
void TreeMode20191117::treeItem_CheckChildChanged(QStandardItem * item)
{
	if (nullptr == item)
	{
		return;
	}
	Qt::CheckState siblingState = checkSibling(item);
	QStandardItem * parentItem = item->parent();
	if (nullptr == parentItem)
		return;
	if (Qt::PartiallyChecked == siblingState)
	{
		if (parentItem->isCheckable() && parentItem->isTristate())
		{
			parentItem->setCheckState(Qt::PartiallyChecked);
		}
	}
	else if (Qt::Checked == siblingState)
	{
		if (parentItem->isCheckable())
		{
			parentItem->setCheckState(Qt::Checked);
		}

	}
	else
	{
		if (parentItem->isCheckable())
		{
			parentItem->setCheckState(Qt::Unchecked);
		}
	}
	treeItem_CheckChildChanged(parentItem);
}

/// \brief 测量兄弟节点的情况，如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
/// \param item
/// \return 如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
///
Qt::CheckState TreeMode20191117::checkSibling(QStandardItem * item)
{
	//先通过父节点获取兄弟节点
	QStandardItem * parent = item->parent();
	if (nullptr == parent)
	{
		return item->checkState();
	}
	int brotherCount = parent->rowCount();
	int checkedCount(0);
	int unCheckedCount(0);
	Qt::CheckState state;
	for (int i = 0; i<brotherCount; ++i)
	{
		QStandardItem* siblingItem = parent->child(i);
		state = siblingItem->checkState();
		if (Qt::PartiallyChecked == state)
		{
			return Qt::PartiallyChecked;
		}

		else if (Qt::Unchecked == state)
		{
			++unCheckedCount;
		}

		else
		{
			++checkedCount;
		}
		if (checkedCount>0 && unCheckedCount>0)
		{
			return Qt::PartiallyChecked;
		}
	}
	if (unCheckedCount>0)
	{
		return Qt::Unchecked;
	}
	return Qt::Checked;
}
void TreeMode20191117::slotTreeViewPressed(const QModelIndex& index)
{
	//ui.treeView->resizeColumnToContents(index.row());
  //  FriendViewItem* d = static_cast<FriendViewItem*>(index.internalPointer());
	//if (d != nullptr)//* 没有原始数据则返回空数据
	//{
	//	QString selectionText1 =d->name;
	//}
}
void TreeMode20191117::onSearchButtonclicked(const QString &str)//树上的搜索按钮
{
	qDebug() << str;
	if (str.isEmpty())
	{
		return;
	}
	//QStringList keyWords= str.split(QString(""));
	getNode(str);
	
//	QStandardItemModelEx::ergodicAllItem(qobject_cast<QStandardItemModel*>(ui.treeView->model()), std::bind(callback_hightLightItem, this,std::placeholders::_1, keyWords));
	//对于callback_hightLightItem是全局函数的情况下
}

//void TreeView::contextMenuEvent(QContextMenuEvent *event) // 添加选中节点弹出菜单项
//{
//	QMenu *pMenu = new QMenu(ui.treeView_);
//	QAction* buildItem = pMenu->addAction(tr("build"));
//	pMenu->exec(QCursor::pos());
//}
//此处是遍历子节点的

//遍历节点
void  TreeMode20191117::getNode(const QString& str)
{
	//QModelIndex groupIndex;
	//for (int i = 0; i < ui.treeView->model()->rowCount(); i++)
	//{
	//	if (friendListModel->mItemList.count()<0) //* 使用有效的数据创建一个节点
	//	{
	//		return;
	//	}
	//	FriendViewItem* d = friendListModel->mItemList[i];
	//	if (d)
	//	{
	//		nonMobileIndex = d->parent;
	//		if (str == d->name)
	//		{
	//			friendListModel->setData(nonMobileIndex, QVariant(QColor(Qt::red)), Qt::BackgroundColorRole);
	//			qDebug() << "ok " << str;
	//			qDebug() << "item = " << d->name<< str;
	//		}
	//		else
	//		{
	//			friendListModel->setData(nonMobileIndex,QVariant(), Qt::BackgroundRole);
	//		}
	//	}
	//	getItem(friendListModel->mItemList[i], str);
	//}
}
void TreeMode20191117::getItem(FriendViewItem *item, const QString& str)
{
	/*Q_ASSERT(item);
 	if (item->children.size()>0)
	{
		for (int i = 0; i < item->children.count(); i++)
		{
			FriendViewItem* d = friendListModel->mItemList[i];
			if (d!=nullptr)
			{
				nonMobileIndex = d->parent;
				if (str == d->name)
				{
					model->setData(nonMobileIndex, QVariant(QColor(255, 0, 0)), Qt::BackgroundColorRole);
					qDebug() << "ok " << str;
					qDebug() << "item = " << d->name << str;
				}
				else
				{
					friendListModel->setData(nonMobileIndex, QVariant(), Qt::BackgroundRole);
				}
			}
			getItem(d, str);
		}
	}*/
}
//bool TreeMode20191117::is_match_string(const QString str, const QStringList keys)
//{
//	for (auto strtemp : keys)
//	{
//		if (str == strtemp)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//bool TreeMode20191117::callback_hightLightItem(QStandardItem* item, const QStringList keys)
//{
//	QString str = item->text();
//	if (is_match_string(str, keys))
//	{
//		item->setData(QVariant(QColor(237, 100, 100, 180)), Qt::BackgroundRole);
//	}
//	else
//	{
//		item->setData(QVariant(), Qt::BackgroundRole);
//	}
//	return true;
//}
//void TreeMode20191117::getAllModelandItem(QStandardItemModel* model, int ID)
//{
//	int rows = model->rowCount();//1
//	int column = model->columnCount();//1
//	for (int i = 0; i<rows; ++i)
//	{
//		for (int j = 0; j<column; ++j)
//		{
//			QStandardItem* item = model->item(i, j);//1 1
//			if (item)
//			{
//				QVariant x1 = item->data();
//				if (x1.toInt() == ID)
//				{
//					nonMobileIndex = item->index();
//					ui.treeView->setCurrentIndex(nonMobileIndex);
//					break;
//				}
//				getAllItem(item, ID);
//
//			}
//		}
//	}
//}


//void TreeMode20191117::getAllItem(QStandardItem* item, int ID)
//{
//	int rows = model->rowCount();
//	for (int i = 0; i<rows; ++i)
//	{
//		QStandardItem* childItem = item->child(i, 0);
//		if (childItem)
//		{
//			QVariant x1 = childItem->data();
//			int az = x1.toInt();
//			QString name1 = childItem->text();
//			qDebug() << az << name1 << endl;
//			if (x1.toInt() == ID)
//			{
//				nonMobileIndex = childItem->index();
//				ui.treeView->setCurrentIndex(nonMobileIndex);
//				qDebug() << "ztttttt" << name1 << endl;
//			}
//			//ergodicItem(childItem, ID);
//
//		}
//
//
//	}

//}