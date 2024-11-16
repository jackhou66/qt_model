#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QWidget>
#include <QMimeData>
#include <QStandardItem>
#include  <QPersistentModelIndex>
#include "TreeModel.h"

//QTableView   QStandardItemModel      ������     
//QStandardItem *item   ��  �洢����  ���뷽ʽ  �����ʽ    ��QItemSelectionModel�й���
//QItemSelectionModel  ��Ԫ��ѡ��״̬   ��ȡģ������ 
class MyModel : public QStandardItemModel
{
	Q_OBJECT
public:
	explicit MyModel(QStandardItemModel *parent = 0);
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;
	QStandardItem*  getTopParentItem(QStandardItem* item, QStandardItemModel*model);
	QModelIndex  getTopParentIndex(QModelIndex itemIndex);

	virtual bool callback_hightLightItem(QStandardItem* item, const QStringList keys);
	virtual bool is_match_string(const QString str, const QStringList keys);

	///11.17
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant data(const QModelIndex &index, int role) const;

signals:

	public slots :

private:
	int m_rowCount;
public:
	QList<QPersistentModelIndex> m_checkedList;
};


//ʵ��QStandardItemModel��ͨ�ñ�������
#include <functional>
class QStandardItemModelEx
{
public:
	QStandardItemModelEx(){}
	~QStandardItemModelEx(){}
	///
	/// \brief callback_ergodicFun_ptr �ص�����ָ�룬bool f(QStandardItem*),bool���ھ����Ƿ���������Ϊtrue�ͼ����ݹ飬���Ϊfalse��ֹͣ�ݹ�
	///
	typedef std::function<bool(QStandardItem*)> callback_ergodicFun_ptr;

	//typedef void(*callback_ergodicFun_ptr)(QStandardItem*);
	static void ergodicAllItem(QStandardItemModel* model, callback_ergodicFun_ptr pFun);
	static bool ergodicItem(QStandardItem* item, callback_ergodicFun_ptr pFun);
private:

};



class MyNewModel : public QStandardItemModel
{
	Q_OBJECT
public:
	explicit MyNewModel(QStandardItemModel *parent = 0);
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;
	QStandardItem*  getTopParentItem(QStandardItem* item, QStandardItemModel*model);
	QModelIndex  getTopParentIndex(QModelIndex itemIndex);

	///11.17
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant data(const QModelIndex &index, int role) const;

signals:

	public slots :

private:
	int m_rowCount;
public:
	QList<QPersistentModelIndex> m_checkedList;
};

#endif // MYMODEL_H