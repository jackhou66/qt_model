#ifndef TREEUSERMODEL_H
#define TREEUSERMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "TreeItem.h"
#include <QMimeData>
#include <QPersistentModelIndex>

#include <QListView>
#include <QMutex>
#include <QMutexLocker>
#include <QAtomicPointer>
#include  "CommonStruct.h"
class TreeItem;


class TreeUserMode : public QAbstractItemModel//QStandardItemModel   QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TreeUserMode(QObject *parent = nullptr);
	virtual ~TreeUserMode();
	//* 用来提供View header部分的数据
	virtual QVariant	headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	//* 返回列数
	virtual int	columnCount(const QModelIndex & parent = QModelIndex()) const;

	//* 获取节点的数据
	virtual QVariant  data(const QModelIndex & index, int role = Qt::DisplayRole) const;

	//* 获取某一个节点
	virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

	//* 获取某一个节点的parent
	virtual QModelIndex	parent(const QModelIndex & index) const;

	//* 返回行数
	virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;

	//* 设置原始数据
	void setEntityList(const entityViewItemList& li);

	//* 返回原始数据
	entityViewItemList EntityList();

	QModelIndex  getTopParentIndex(QModelIndex itemIndex);

	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Entity * getItem(const QModelIndex &index) const;//
 
	void treeItem_checkAllChild_recursion(Entity * item, bool check);
	 
	Qt::CheckState checkSibling(Entity * item);


	//关于拖动属性设置
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;

	bool insertItem(const QModelIndex &parent, Entity * item);//
	void setRootNode(Entity *node);

	//新添加的拖动添加函数
	bool  addTreeNode(Entity* pNode);
	Entity*  findParentNode(Entity* pNode, Entity* childNode);
	int  treeNodeHaveEqualInfo(Entity* parentNode, Entity* pAddChildNode);
	Entity*  nodeFromIndex(const QModelIndex &index) const;

public:
	entityViewItemList mItemList; //* 树状结构的原始数据(父节点list)
	QList<QPersistentModelIndex> m_checkedList;
private:

	Entity  *m_pEntity;
	int m_rowCount;
};

//



class MyNewTreeModeView :public TreeUserMode
{
	Q_OBJECT

public:
	explicit MyNewTreeModeView(QObject *parent = nullptr);
	virtual ~MyNewTreeModeView();
public:
	static MyNewTreeModeView *instance();
private:
	static QAtomicPointer<MyNewTreeModeView> m_pInstance;
	static QMutex  m_mutex;
};

//for (int i = 0; i < 3; i++)
//{
//	Entity* gi = new Entity;
//	gi->armyType = (ArmyType)1;
//	gi->plantType = (PlantType)1;
//	gi->devicetype = (DviceType)1;
//	for (int ii = 0; ii < 1; ii++)
//	{
//		Entity* ci = new Entity;
//		ci->EntityId = "1";
//		ci->armyType = (ArmyType)3;
//		ci->plantType = (PlantType)3;
//		ci->devicetype = (DviceType)3;
//		//ci->parameter.ParameterId = "1";
//		//ci->parameter.devicetype = (DviceType)2;
//		//ci->parameter.Azimuth = "22";
//		for (int k = 0; k<1; k++)
//		{
//			Entity*di = new Entity;
//			di->EntityId = "2";
//			di->armyType = (ArmyType)4;
//			di->plantType = (PlantType)4;
//			di->devicetype = (DviceType)4;
//			//if (k==1)
//			//{
//			//	di->parameter.ParameterId = "44";
//			//	di->parameter.devicetype = (DviceType)1;
//			//	di->parameter.Azimuth = "88";
//			//}
//			for (int p = 0; p< 1; p++)
//			{
//				Entity*ee = new Entity;
//				ee->EntityId = "2";
//				ee->armyType = (ArmyType)5;
//				ee->plantType = (PlantType)5;
//				ee->devicetype = (DviceType)5;
//				for (int h = 0; h< 1; h++)
//				{
//					Entity*ff = new Entity;
//					ff->EntityId = "2";
//					ff->armyType = (ArmyType)6;
//					ff->plantType = (PlantType)6;
//					ff->devicetype = (DviceType)6;
//					for (int w = 0; w< 1; w++)
//					{
//						Entity*ww = new Entity;
//						ww->EntityId = "2";
//						ww->armyType = (ArmyType)7;
//						ww->plantType = (PlantType)7;
//						ww->devicetype = (DviceType)7;
//						ff->children << ww;
//					}
//					ee->children << ff;
//				}
//				di->children << ee;
//			}
//			//ci->parentEntity= di;
//			ci->children << di;
//		}
//		//gi->parentEntity = ci;
//		gi->children << ci;
//	}
//	fli << gi;
//}

#endif// TREEUSERMODEL_H