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
//	private slots ://��ͷ����¼�
//	void slot_RightClickedOnHeader(const QPoint & pos);
//
//	private slots://���οؼ��Ǳ�ͷ�ĵ���¼�
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
//	long m_nRowOfNeedToDelete;//ɾ���ڵ�����(root�µ��ӽڵ�)
// 
//};
//
//#endif // TREEVIEWMANEGER_H
