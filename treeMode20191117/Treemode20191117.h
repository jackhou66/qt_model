#ifndef TREEMODE20191117_H
#define TREEMODE20191117_H

#include <QtWidgets/QMainWindow>
#include "ui_Treemode20191117.h"
#include "mymodelwidget.h"
#include <qpointer.h>
#include "TreeItemMimeData.h"
#include "TreeViewSearchLine.h"
#include <functional>
#include "TreeModel.h"
#include "TreeItem.h"

class TreeMode20191117 : public QMainWindow
{
	Q_OBJECT

public:
	TreeMode20191117(QWidget *parent = 0);
	~TreeMode20191117();
//标准的item
public:
	void initStandardItemModelTreeView();
	void  initStandardItemModelTreeViewSun();
	void treeItemChanged(QStandardItem * item);
	void treeItem_checkAllChild(QStandardItem * item, bool check);
	void treeItem_checkAllChild_recursion(QStandardItem * item, bool check);
	void treeItem_CheckChildChanged(QStandardItem * item);
	Qt::CheckState checkSibling(QStandardItem * item);
	//virtual bool callback_hightLightItem(QStandardItem* item, const QStringList keys);
	//virtual bool is_match_string(const QString str, const QStringList keys);
	//void  getAllModelandItem(QStandardItemModel* model, int ID);
	//void  getAllItem(QStandardItem* item, int ID);


	void getNode(const QString& str);
	void getItem(FriendViewItem *item, const QString& str);
	//继承自基类的abstructitemMode
public:
signals :

public slots:
	void  slotShowNewTreeView();
	void slotTreeViewPressed(const QModelIndex& index);//选中节点取值

	void onSearchButtonclicked(const QString &str);
private:
	Ui::TreeMode20191117Class ui;

	MyModelWidget  *m_pMyModelWidget;

	//继承自标准的itemMode
	QMap<QString, QIcon> m_publicIconMap;
	MyModel	*model;
	QItemSelectionModel  *m_pItemSelectionModel;

	MyModel *m_model2;

	TreeViewSearchLine  *m_pTreeViewSearchLine;
	QModelIndex nonMobileIndex;

	QList<QPersistentModelIndex> m_checkedListTreeView;
	QList<QStandardItem*> itms;

	TreeModel *friendListModel;
	MyTreeItemModel  * m_pMyTreeItemModel;
	//TreeModelView * m_pTreeModelView;
};

#endif // TREEMODE20191117_H
