//#ifndef TREEVIEWMANEGER_H
//#define TREEVIEWMANEGER_H
//#include <QMenu>
//#include <QAction>
//#include <QWidget>
//#include <QTreeView>
//#include <QLineEdit>
//#include <QHBoxLayout>
//#include <QHeaderView>
//#include <QMouseEvent>
//#include <QTreeWidgetItem>
//#include <QStandardItemModel>
//
//#include <QObject>
//
//class TreeViewManeger : public QTreeView
//{
//	Q_OBJECT
//
//public:
//	explicit TreeViewManeger(QWidget *parent);
//	virtual ~TreeViewManeger();
//
//private slots:
//
//	void slot_AddGroup();
//	void slot_DeleteGroup();
//	void slot_AddDepartment();
//	void slot_DeleteDepartment();
//	void slot_EditCompanyName();
//
//private slots:
//	void slot_ClickedOnTreeView(const QModelIndex & index);
//	void slot_DoubleClickedOnTreeView(const QModelIndex & index);
//
//private:
//	private slots ://表头点击事件
//	void slot_RightClickedOnHeader(const QPoint & pos);
//
//	private slots://树形控件非表头的点击事件
//	//void slot_RightClickedOnTreeView(const QPoint & pos);
//
//	private slots:
//	//void slot_ClickedOnTreeView(const QModelIndex & index);
//	//void slot_DoubleClickedOnTreeView(const QModelIndex & index);
//
//private:
//	void mousePressEvent(QMouseEvent *event);
// 
//private:
//	QAction* m_ActionEditCompanyName;
//	QAction* m_ActionAddDepartment;
//	QAction* m_ActionDeleteDepartment;
//	QAction* m_ActionAddGroup;
//	QAction* m_ActionDeleteGroup;
//
//private:
//	long m_nRowOfNeedToDelete;//删除节点所用(root下的子节点)
// 
//};
//
//#endif // TREEVIEWMANEGER_H
