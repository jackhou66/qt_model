#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QObject>
#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

class MyTreeView:public QTreeView
{
    Q_OBJECT
public:
    MyTreeView(QWidget *parent = nullptr);
    ~ MyTreeView();
public:
    void initView();
private:

    QMap<QString,QIcon> m_publicIconMap;
};

#endif // MYTREEVIEW_H
