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
	bool isGroup; //* �Ƿ��Ƿ���(��ʵ����ʹ��children.isEmpty�����)
	QString name; //* ����  
	int id; //* ����  
	QModelIndex parent;              // ���ڵ�index
	FriendViewItem  * parentViewItem;  // ���ڵ�
	QList<FriendViewItem*> children; //* �ӽڵ�  �ӽڵ������
};
typedef QList<FriendViewItem*> FriendViewItemList;

struct NodeInfo
{
	QVector<NodeInfo*> childNodes;   // �ӽڵ�
	QString sData;                   // ��������
	QModelIndex parent;              // ���ڵ�index
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
	Parameter, //����
	NO//�����Ǻ����ڵ�
};
Q_DECLARE_METATYPE(PlantType)
//װ������
enum class DviceType
{
	Radar, //�״�
	RadarJam, //�״�����豸
	communication,//ͨ��
	infrared, //���
	NO
};
struct DeviceInfor
{
	QString DeviceName;
	QString parentName;
	DviceType type; //�豸����
	ArmyType Devicefrom; //�豸������
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
	PlantType  plantType;//��������   ��ɫ1 ��ɫ2
	DviceType devicetype;
	QString  name;              //�����������
	QString Mode2D;
	QString Mode3D;
	QString Pitch;
	QString Lon;
	QString lat;
	QString Alt;
	Parameter  parameter;
	QModelIndex parent;              // ���ڵ�index
	Entity  * parentEntity;  // ���ڵ�
	int number;  //ÿ��Entity�ı��
	QList<Entity*> children; //* �ӽڵ�  �ӽڵ������
};
Q_DECLARE_METATYPE(Entity*)

typedef QList< Entity*> entityViewItemList;

#endif // COMMON_H