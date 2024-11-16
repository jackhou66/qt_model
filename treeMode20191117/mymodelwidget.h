#ifndef MYMODELWIDGET_H
#define MYMODELWIDGET_H

#include <QWidget>
#include "ui_mymodelwidget.h"
#include "TreeItemMimeData.h"
#include <QAbstractItemView>
#include "TreeModel.h"
#include <qpushbutton.h>
#include "CommonStruct.h"
#include "XMLFile.h"
#include <QPointer>
#include <QMenu>
class MyModel;

namespace Ui {
	class MyModelWidget;
}
class MyModelWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MyModelWidget(QWidget *parent=0);
	virtual ~MyModelWidget();
public:
	void initReadXml();
	void initUI();
	void initSlot();
public slots:
	//void slotTreeViewPressed(const QModelIndex& index);
	void slotNewTreeModeViewShow();
	void slotCreateXmlFile();
	void slotShowXmlView();
	void getNode();
	void getItem(Entity *item);
	void slotShowContextMenu(const QPoint& pos);
	void slotOnAddAreaMenuTriggered(QAction *action);
	void slotUpdata();
private:
	Entity  *m_pFriendViewItem;
private:
	Ui::MyModelWidget ui;
	entityViewItemList mItemList;	//* 树状结构的原始数据(父节点list)
	QList<QPersistentModelIndex> m_checkedListTreeView;
	//树
	QPointer<TreeModel> m_pTreeOneModel;
	QPointer<TreeModel> m_pTreeTwoModel;
	QPointer<TreeModel> m_pTreeThirdModel;
	//菜单栏
	QMenu *menu;
	QAction* m_pAddaction;
	QAction* m_pAddaction_device;
	QAction* m_pDeleteaction;
	QAction* m_pEditeraction;


};

#endif // MYMODELWIDGET_H
