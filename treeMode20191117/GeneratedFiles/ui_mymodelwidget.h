/********************************************************************************
** Form generated from reading UI file 'mymodelwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMODELWIDGET_H
#define UI_MYMODELWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyModelWidget
{
public:
    QHBoxLayout *horizontalLayout_6;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QTreeView *treeView_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *newTreeModeBtn;
    QSplitter *splitter_3;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QTreeView *treeView_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *newTreeModeViewBtn;
    QSplitter *splitter_4;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_5;
    QTreeView *treeView_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *createXmlBtn;

    void setupUi(QWidget *MyModelWidget)
    {
        if (MyModelWidget->objectName().isEmpty())
            MyModelWidget->setObjectName(QStringLiteral("MyModelWidget"));
        MyModelWidget->resize(573, 337);
        horizontalLayout_6 = new QHBoxLayout(MyModelWidget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        splitter_2 = new QSplitter(MyModelWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        treeView_2 = new QTreeView(layoutWidget);
        treeView_2->setObjectName(QStringLiteral("treeView_2"));
        treeView_2->setProperty("showDropIndicator", QVariant(false));
        treeView_2->setSelectionBehavior(QAbstractItemView::SelectItems);

        verticalLayout_2->addWidget(treeView_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        newTreeModeBtn = new QPushButton(layoutWidget);
        newTreeModeBtn->setObjectName(QStringLiteral("newTreeModeBtn"));

        horizontalLayout_2->addWidget(newTreeModeBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        splitter_2->addWidget(layoutWidget);

        horizontalLayout_6->addWidget(splitter_2);

        splitter_3 = new QSplitter(MyModelWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        layoutWidget_2 = new QWidget(splitter_3);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        treeView_3 = new QTreeView(layoutWidget_2);
        treeView_3->setObjectName(QStringLiteral("treeView_3"));
        treeView_3->setDragEnabled(true);
        treeView_3->setDragDropOverwriteMode(true);
        treeView_3->setDragDropMode(QAbstractItemView::DragDrop);
        treeView_3->setSelectionMode(QAbstractItemView::SingleSelection);
        treeView_3->setSelectionBehavior(QAbstractItemView::SelectItems);

        verticalLayout_3->addWidget(treeView_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        newTreeModeViewBtn = new QPushButton(layoutWidget_2);
        newTreeModeViewBtn->setObjectName(QStringLiteral("newTreeModeViewBtn"));

        horizontalLayout_3->addWidget(newTreeModeViewBtn);


        verticalLayout_3->addLayout(horizontalLayout_3);

        splitter_3->addWidget(layoutWidget_2);

        horizontalLayout_6->addWidget(splitter_3);

        splitter_4 = new QSplitter(MyModelWidget);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setOrientation(Qt::Horizontal);
        layoutWidget_3 = new QWidget(splitter_4);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        verticalLayout_5 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        treeView_5 = new QTreeView(layoutWidget_3);
        treeView_5->setObjectName(QStringLiteral("treeView_5"));
        treeView_5->setDragEnabled(true);
        treeView_5->setDragDropMode(QAbstractItemView::DropOnly);
        treeView_5->setSelectionMode(QAbstractItemView::SingleSelection);
        treeView_5->setSelectionBehavior(QAbstractItemView::SelectItems);

        verticalLayout_5->addWidget(treeView_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        createXmlBtn = new QPushButton(layoutWidget_3);
        createXmlBtn->setObjectName(QStringLiteral("createXmlBtn"));

        horizontalLayout_5->addWidget(createXmlBtn);


        verticalLayout_5->addLayout(horizontalLayout_5);

        splitter_4->addWidget(layoutWidget_3);

        horizontalLayout_6->addWidget(splitter_4);


        retranslateUi(MyModelWidget);

        QMetaObject::connectSlotsByName(MyModelWidget);
    } // setupUi

    void retranslateUi(QWidget *MyModelWidget)
    {
        MyModelWidget->setWindowTitle(QApplication::translate("MyModelWidget", "MyModelWidget", 0));
        newTreeModeBtn->setText(QApplication::translate("MyModelWidget", "\344\270\213\344\270\200\346\255\245", 0));
        newTreeModeViewBtn->setText(QApplication::translate("MyModelWidget", "\344\270\213\344\270\200\346\255\245", 0));
        createXmlBtn->setText(QApplication::translate("MyModelWidget", "\347\224\237\346\210\220XML", 0));
    } // retranslateUi

};

namespace Ui {
    class MyModelWidget: public Ui_MyModelWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMODELWIDGET_H
