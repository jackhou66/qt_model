//#include "treeviewmaneger.h"
//
//TreeViewManeger::TreeViewManeger(QWidget *parent)
//	: QTreeView(parent), m_nRowOfNeedToDelete(-1)
//{
//	//
//	m_ActionAddDepartment = new QAction("Add Department", this);
//	connect(m_ActionAddDepartment, &QAction::triggered, this, &TreeViewManeger::slot_AddDepartment);
//
//	m_ActionDeleteDepartment = new QAction("DEL Department", this);
//	connect(m_ActionDeleteDepartment, &QAction::triggered, this, &TreeViewManeger::slot_DeleteDepartment);
//
//	m_ActionEditCompanyName = new QAction("Edit", this);
//	connect(m_ActionEditCompanyName, &QAction::triggered, this, &TreeViewManeger::slot_EditCompanyName);
//
//	m_ActionAddGroup = new QAction("Add Group", this); 
//	connect(m_ActionAddGroup, &QAction::triggered, this, &TreeViewManeger::slot_AddGroup);
//
//	m_ActionDeleteGroup = new QAction("Del Group", this);
//	connect(m_ActionDeleteGroup, &QAction::triggered, this, &TreeViewManeger::slot_DeleteGroup);
// 
//}
//
//TreeViewManeger::~TreeViewManeger()
//{
//
//}
////------------------------------------------------------------------------------------------------------------
////组操作
//void TreeViewManeger::slot_AddGroup()
//{
//	QStandardItem* itemChild = new QStandardItem("文件夹1");
//	//m_Item->appendRow(itemChild);
//	//this->expandAll();
//}
//void TreeViewManeger::slot_DeleteGroup()
//{
//	/*if (m_ModelIndex.isValid())
//	{
//		m_pModel->removeRow(m_nRowOfNeedToDelete, m_ModelIndex);
//	}
//*/
//	this->expandAll();
//}
//
//
////------------------------------------------------------------------------------------------------------------
////部门操作
//void TreeViewManeger::slot_AddDepartment()
//{
//	QStandardItem* itemChild = new QStandardItem("文件夹1");
//	//m_pModel->appendRow(itemChild);
//	this->expandAll();
//}
//void TreeViewManeger::slot_DeleteDepartment()
//{
//	//m_pModel->removeRow(m_nRowOfNeedToDelete);
//	this->expandAll();
//}
//
////鼠标点击空白处,清除选中项
//void TreeViewManeger::mousePressEvent(QMouseEvent *event)
//{
//	QModelIndex index = this->indexAt(event->pos());
//	if (!index.isValid())
//	{
//		this->clearSelection();
//	}
//	else{
//		return QTreeView::mousePressEvent(event);
//	}
//}
////------------------------------------------------------------------------------------------------------------
////右击操作
//void TreeViewManeger::slot_RightClickedOnHeader(const QPoint & pos)
//{
//	QMenu menu;
//	//menu.addAction(m_ActionEditCompanyName);
//	menu.addAction(m_ActionAddDepartment);
//	menu.exec(QCursor::pos());
//}
////void TreeViewManeger::slot_RightClickedOnTreeView(const QPoint & pos)
////{
//	//QModelIndex ModelIndex = this->indexAt(pos);
//	//if (ModelIndex.isValid()){
//	//	const QAbstractItemModel* pAbstractItemModel = ModelIndex.model();
//	//	if (pAbstractItemModel){
//	//		const QStandardItemModel* pStandardItemModel = dynamic_cast<const QStandardItemModel*>(pAbstractItemModel);
//	//		if (pStandardItemModel){
//	//			m_Item = pStandardItemModel->itemFromIndex(ModelIndex);
//	//		}
//	//	}
//
//	//	long nLevel = 0;
//	//	QModelIndex parentModelIndex = ModelIndex;
//	//	for (;;){
//	//		if (!parentModelIndex.isValid()){//判断当前QModelIndex是否有效
//	//			break;
//	//		}
//
//	//		nLevel++;
//	//		parentModelIndex = parentModelIndex.parent();//获取父级的QModelIndex
//	//	}
//
//	//	m_ModelIndex = ModelIndex.parent();
//	//	m_nRowOfNeedToDelete = ModelIndex.row();
//	//	if (nLevel <= m_nLevel && nLevel == 1){
//	//		QMenu menu;
//	//		menu.addAction(m_ActionAddGroup);
//	//		menu.addAction(m_ActionDeleteDepartment);
//	//		menu.exec(QCursor::pos());
//	//	}
//	//	if (nLevel <= m_nLevel && nLevel == 2){
//	//		QMenu menu;
//	//		menu.addAction(m_ActionDeleteGroup);
//	//		menu.exec(QCursor::pos());
//	//	}
//	//}
////}
// 