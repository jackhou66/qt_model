#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QWidget>
#include <QMimeData>
#include <QStandardItem>
#include  <QPersistentModelIndex>
#include "TreeModel.h"

//QTableView   QStandardItemModel      项数据     
//QStandardItem *item   项  存储数据  对齐方式  字体格式    和QItemSelectionModel有关联
//QItemSelectionModel  单元格选择状态   获取模型索引 
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


//实现QStandardItemModel的通用遍历函数
#include <functional>
class QStandardItemModelEx
{
public:
	QStandardItemModelEx(){}
	~QStandardItemModelEx(){}
	///
	/// \brief callback_ergodicFun_ptr 回调函数指针，bool f(QStandardItem*),bool用于决定是否继续，如果为true就继续递归，如果为false就停止递归
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