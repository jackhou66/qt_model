#ifndef COMMON_H
#define COMMON_H
#include <QVariant>
#include <QMetaType>

#define SAFE_DELETE(ptr)\
	if (ptr!=nullptr)\
		{  \
		delete ptr;\
		ptr = nullptr;\
		}\

#define NULL_PTR(ptr)\
if (ptr == nullptr)\
		{  \
		return ; \
		}\

#include <QStandardItem>
struct FriendViewItem : public QStandardItem
{
	bool isGroup; //* 是否是分组(其实可以使用children.isEmpty来替代)
	QString name; //* 名字  
	int id; //* 名字  
	QModelIndex parent;              // 父节点index
	FriendViewItem  * parentViewItem;  // 父节点
	QList<FriendViewItem*> children; //* 子节点  子节点的梳理
};
typedef QList<FriendViewItem*> FriendViewItemList;

struct NodeInfo
{
	QVector<NodeInfo*> childNodes;   // 子节点
	QString sData;                   // 自身数据
	QModelIndex parent;              // 父节点index
	NodeInfo(QString s, QModelIndex parentIdx) :parent(parentIdx), sData(s){}
};

//typedef QList<NodeInfo*> FriendNodeInfoList;
/////////////////////////////////////////////
enum class ArmyType
{
	RED,
	BLUES,
	WRITE,
	NO
};
Q_DECLARE_METATYPE(ArmyType)
enum  class PlantType
{
	PLANT,
	DEVICE,
	Parameter, //参数
	NO//可能是红蓝节点
};
Q_DECLARE_METATYPE(PlantType)
//装备类型
enum class DviceType
{
	Radar, //雷达
	RadarJam, //雷达干扰设备
	communication,//通信
	infrared, //光电
	NO
};
struct DeviceInfor
{
	QString DeviceName;
	QString parentName;
	DviceType type; //设备类型
	ArmyType Devicefrom; //设备红兰方
};
Q_DECLARE_METATYPE(DeviceInfor)

struct Parameter
{
	QString  ParameterId;
	DviceType  devicetype;
	//QString  Scantype;
	QString  name;
	QString  Azimuth;
	QString  Pitch;
	QString  speed;
	QString Length;
};

struct Entity
{
	QString EntityId;
	ArmyType armyType; 
	QString  isGroup;
	PlantType  plantType;//决定红蓝   红色1 蓝色2
	DviceType devicetype;
	QString  name;              //额外添加数据
	QString Mode2D;
	QString Mode3D;
	QString Pitch;
	QString Lon;
	QString lat;
	QString Alt;
	Parameter  parameter;
	QModelIndex parent;              // 父节点index
	Entity  * parentEntity;  // 父节点
	int number;  //每个Entity的编号
	QList<Entity*> children; //* 子节点  子节点的梳理
};
Q_DECLARE_METATYPE(Entity*)

typedef QList< Entity*> entityViewItemList;

#endif // COMMON_H