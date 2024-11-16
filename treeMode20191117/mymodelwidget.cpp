#include "mymodelwidget.h"
#include <QStringList>
#include "TreeUserMode.h"
MyModelWidget::MyModelWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUI();
	initSlot();
}

MyModelWidget::~MyModelWidget()
{
	SAFE_DELETE(m_pAddaction);
	SAFE_DELETE(m_pDeleteaction);
	SAFE_DELETE(m_pEditeraction);
	SAFE_DELETE(menu);

	SAFE_DELETE(m_pTreeThirdModel);
	SAFE_DELETE(m_pTreeTwoModel);
	SAFE_DELETE(m_pTreeOneModel);
}
void  MyModelWidget::initUI()
{
	m_pTreeOneModel = new(std::nothrow) TreeModel;
	m_pTreeTwoModel = new(std::nothrow) TreeModel;
	m_pTreeThirdModel = new(std::nothrow) TreeModel;
	showMinimized();
	this->setWindowState(Qt::WindowMinimized);
	this->resize(600,300);
	//初始化第一个treeView
	/*
	取值和显示的时候，得用QMap做成翻译的键值对，需要单独写个类
	*/
	entityViewItemList fli;
	for (int i = 0; i < 2; i++)
	{
		Entity* gi = new Entity;
		gi->armyType = (ArmyType)1;
		gi->plantType = (PlantType)1;
		gi->devicetype = (DviceType)1;
		if (i==0)
		{
			gi->name =tr("Red");
			for (int m = 0; m< 2; m++)
			{
				Entity*ff = new Entity;
				ff->EntityId = "2";
				ff->name = tr("Red_soder");
				ff->armyType = (ArmyType)0;
				ff->plantType = (PlantType)1;
				ff->devicetype = (DviceType)1;
				ff->parameter.ParameterId = "1";
				ff->parameter.devicetype = (DviceType)2;
				ff->parameter.Azimuth = "22";
				ff->parameter.name = "777";
				gi->children << ff;
			}
		}
		if (i == 1)
		{
			gi->name =tr("Blue");
			gi->EntityId = "1";
			gi->isGroup =true;
			for (int ii = 0; ii < 1; ii++)
			{
				Entity* ci = new Entity;
				ci->EntityId = "2";
				ci->name = tr("Blue_soder_1");
				ci->armyType = (ArmyType)1;
				ci->plantType = (PlantType)2;
				ci->devicetype = (DviceType)1;
				ci->parameter.ParameterId = "1";
				ci->parameter.devicetype = (DviceType)2;
				ci->parameter.Azimuth = "22";
				for (int k = 0; k<1; k++)
				{
					Entity*di = new Entity;
					di->EntityId = "3";
					di->name = tr("Blue_soder_2");
					di->armyType = (ArmyType)1;
					di->plantType = (PlantType)2;
					di->devicetype = (DviceType)4;
					if (k == 1)
					{
						di->parameter.ParameterId = "44";
						di->parameter.devicetype = (DviceType)1;
						di->parameter.Azimuth = "88";
					}
					for (int p= 0; p < 1; p++)
					{
						Entity*ee = new Entity;
						ee->EntityId = "4";
						ee->name =tr("Blue_Red_soder_1");
						ee->armyType = (ArmyType)1;
						ee->plantType = (PlantType)2;
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
	//m_pTreeOneModel->setEntityList(fli);
	ui.treeView_2->setModel(m_pTreeOneModel);
	ui.treeView_2->setDragEnabled(true);

	ui.treeView_2->viewport()->setAcceptDrops(true);
	ui.treeView_2->setDropIndicatorShown(true);
	ui.treeView_2->setDragDropMode(QAbstractItemView::DragDrop);
    //ui.treeView_2->setAlternatingRowColors(true);
	//ui.treeView_2->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
	//ui.treeView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
	//ui.treeView_2->resizeColumnToContents(1); //列宽自适应调整
	//ui.treeView_2->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
	//NewTreeMode::instance()->modelReset();

	//右键菜单
	ui.treeView_3->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.treeView_3, &QWidget::customContextMenuRequested, this, &MyModelWidget::slotShowContextMenu);
}

void  MyModelWidget::slotShowContextMenu(const QPoint& pos)
{
	//创建右键菜单
	menu = new QMenu(this);
	connect(menu, &QMenu::triggered, this, &MyModelWidget::slotOnAddAreaMenuTriggered);

	m_pAddaction = new QAction(menu);
	m_pAddaction->setObjectName("m_pAddaction ");
	m_pAddaction->setIcon(QIcon(":/image/add.png"));
	m_pAddaction->setText(tr("add_sun"));
	menu->addAction(m_pAddaction);

	m_pAddaction_device = new QAction(menu);
	m_pAddaction_device->setObjectName("m_pAddaction ");
	m_pAddaction_device->setIcon(QIcon(":/image/add.png"));
	m_pAddaction_device->setText(tr("add_sun_device"));
	menu->addAction(m_pAddaction_device);


	m_pDeleteaction = new QAction(menu);
	m_pDeleteaction->setObjectName("m_pDeleteaction ");
	m_pDeleteaction->setText(tr("delete_sun"));
	menu->addAction(m_pDeleteaction);
	m_pEditeraction = new QAction(menu);
	//m_pEditeraction->setObjectName("m_pEditeraction ");
	//m_pEditeraction->setText(tr("editer_sun"));
	//menu->addAction(m_pEditeraction);
	menu->exec(ui.treeView_3->mapToGlobal(pos));
}

void MyModelWidget::slotOnAddAreaMenuTriggered(QAction *action)
{
	if (action == m_pAddaction)
	{ 
		//插入子节点   此时添加的是一个空节点
		QModelIndex    index   = ui.treeView_3->currentIndex();
		entityViewItemList treelist;
		Entity* parentData = static_cast<Entity*>(index.internalPointer());
		Entity* parentDataTemp = new Entity;
		m_pTreeTwoModel->setupModelData(m_pTreeTwoModel->getEntityDataList(), index, parentDataTemp);
	}
	else if (action == m_pDeleteaction)
	{ 
		QModelIndex  index = ui.treeView_3->currentIndex();
		entityViewItemList treelist;
		Entity* parentData = static_cast<Entity*>(index.internalPointer());
		Entity* parentDataTemp = new Entity;
		m_pTreeTwoModel->deleteModelData(m_pTreeTwoModel->getEntityDataList(), index, parentDataTemp);
	}
	else if (action == m_pAddaction_device)
	{

	}
}
//初始化读取xml
void MyModelWidget::initReadXml()
{
	//m_pMyModelWidget = new(std::nothrow) MyModelWidget(this);
	//m_pMyModelWidget->show();
	//LOG4CPLUS_INFO(MyLogger::getInstance()->logger, "pushButton_3 is clicked");
	//XMLFile xmlFile("D:/hjc/QtcnFile/tableViewTest/TableViewTest/TableViewTest/StuInfo.xml");
	//xmlFile.ReadXML();
	////获取节点声明
	//string version;
	//string encoding;
	//string standalone;
	//xmlFile.ReadDeclaration(version, encoding, standalone);
	//LOG4CPLUS_INFO(MyLogger::getInstance()->logger, version.c_str());
	//LOG4CPLUS_INFO(MyLogger::getInstance()->logger, encoding.c_str());
	//LOG4CPLUS_INFO(MyLogger::getInstance()->logger, standalone.c_str());
	//string nodeName = "Student";
	////获取节点文本值
	//const char *strText = new char[20];
	//xmlFile.GetNodeText(nodeName, strText);
	//cout << strText << endl;
	//LOG4CPLUS_INFO(MyLogger::getInstance()->logger, strText);
	////获取节点属性值
	//map<string, string> mapAttr;
	//xmlFile.GetNodeAttribute(nodeName, mapAttr);
	//for (auto it = mapAttr.begin(); it != mapAttr.end(); ++it)
	//{
	//	ui->lineEdit_3->setText((it->first).c_str());
	//	LOG4CPLUS_INFO(MyLogger::getInstance()->logger, (it->first).c_str());
	//	LOG4CPLUS_INFO(MyLogger::getInstance()->logger, (it->second).c_str());
	//}
}
void MyModelWidget::initSlot()
{
	//点击下一步的时候
	connect(ui.newTreeModeBtn, &QPushButton::clicked, this, &MyModelWidget::slotNewTreeModeViewShow);

	//生产3个treeView页面按钮
	connect(ui.newTreeModeViewBtn, &QPushButton::clicked, this, &MyModelWidget::slotShowXmlView);

	//生产xml按钮
	connect(ui.createXmlBtn, &QPushButton::clicked, this, &MyModelWidget::slotCreateXmlFile);

}
//生成XML文件 
void MyModelWidget::slotCreateXmlFile()
{
	//
	XMLFile xmlFile("StuInfo.xml");
	mItemList = m_pTreeThirdModel->getEntityDataList();
	xmlFile.createXML(mItemList);
}
void MyModelWidget::slotNewTreeModeViewShow()
{
	entityViewItemList fli;
	for (int i = 0; i < 2; i++)
	{
		Entity* gi = new Entity;
		gi->armyType = (ArmyType)1;
		gi->plantType = (PlantType)1;
		gi->devicetype = (DviceType)0;
		if (i == 0)
		{
			gi->name = tr("Red");
			gi->isGroup = "isgroup";
			for (int m = 0; m < 2; m++)
			{
				Entity*ff = new Entity;
				ff->EntityId = "2";
				ff->name = tr("Red_soder");
				ff->armyType = (ArmyType)0;
				ff->plantType = (PlantType)0;
				ff->devicetype = (DviceType)1;
				ff->parameter.ParameterId = "1";
				ff->parameter.devicetype = (DviceType)2;
				ff->parameter.Azimuth = "22";
				ff->isGroup = "nogroup";
				gi->children << ff;
			}
		}
		else
		{
			gi->isGroup = "isgroup";
			gi->name = tr("Blue");
			gi->EntityId = "1";
			for (int ii = 0; ii < 1; ii++)
			{
				Entity* ci = new Entity;
				ci->EntityId = "2";
				ci->isGroup = "nogroup";
				ci->name = tr("Blue_soder_1");
				ci->armyType = (ArmyType)1;
				ci->plantType = (PlantType)0;
				ci->devicetype = (DviceType)1;
				ci->parameter.ParameterId = "1";
				ci->parameter.devicetype = (DviceType)2;
				ci->parameter.Azimuth = "22";
				for (int k = 0; k<1; k++)
				{
					Entity*di = new Entity;
					di->EntityId = "3";
					di->isGroup = "nogroup";
					di->name = tr("Blue_Dvice_1");
					di->armyType = (ArmyType)1;
					di->plantType = (PlantType)1;
					di->devicetype = (DviceType)4;
					di->parameter.ParameterId = "44";
					di->parameter.devicetype = (DviceType)1;
					di->parameter.Azimuth = "88";
					di->parameter.name = tr("Blue_Device_2");
					for (int p = 0; p < 1; p++)
					{
						Entity*ee = new Entity;
						ee->EntityId = "4";
						ee->isGroup = "nogroup";
						ee->name = tr("Blue_Red_soder_1");
						ee->armyType = (ArmyType)1;
						ee->plantType = (PlantType)0;
						ee->devicetype = (DviceType)5;
						for (int h = 0;h < 1; h++)
						{
								Entity*hh = new Entity;
								hh->EntityId = "4";
								hh->isGroup = "nogroup";
								hh->name = tr("Blue_lian");
								hh->armyType = (ArmyType)1;
								hh->plantType = (PlantType)0;
								hh->devicetype = (DviceType)5;
								ee->children.append(hh);
						}
						di->children.append(ee);
					}
					ci->children.append(di);
				}
				gi->children.append(ci);
			}

		}
		fli << gi;
	}
	m_pTreeTwoModel->setEntityList(fli);
	ui.treeView_3->setModel(m_pTreeTwoModel);
	ui.treeView_3->setDragDropMode(QAbstractItemView::DragDrop);
	ui.treeView_3->setUniformRowHeights(true);

	connect(m_pTreeTwoModel, &TreeModel::dataChange, this, &MyModelWidget::slotUpdata);

}
void  MyModelWidget::slotUpdata()
{
	m_pTreeTwoModel->setEntityList(m_pTreeTwoModel->getEntityDataList());
}
//遍历第2棵树   初始化第3棵树
void MyModelWidget::slotShowXmlView()
{
	entityViewItemList fliDemo = m_pTreeTwoModel->getEntityDataList();
	m_pTreeThirdModel->setEntityList(fliDemo);
	ui.treeView_5->setModel(m_pTreeThirdModel);
	ui.treeView_5->setDragDropMode(QAbstractItemView::DropOnly);
}
void  MyModelWidget::getNode()
{
	 
//		Entity *d = NewTreeModeView::instance()->item(i);
		/*mItemList.push_back(d);
		getItem(NewTreeModeView::instance()->mItemList[i]);*/
	QModelIndex groupIndex;
	for (int i = 0; i <ui.treeView_5->model()->rowCount(); i++)
	{
		groupIndex = ui.treeView_5->model()->index(i, 0);
		Entity* d = static_cast<Entity*>(groupIndex.internalPointer());
		mItemList.push_back(d);
		getItem(d);
	}
}
void MyModelWidget::getItem(Entity *item)
{
	Q_ASSERT(item);
	QModelIndex groupIndex;
	if (item->children.size() > 0)
	{
		for (int i = 0; i < item->children.count(); i++)
		{
			Entity* d = (item->children.at(i));
			getItem(d);
		}

	}
}