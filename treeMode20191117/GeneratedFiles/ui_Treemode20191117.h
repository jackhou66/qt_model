/********************************************************************************
** Form generated from reading UI file 'Treemode20191117.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEMODE20191117_H
#define UI_TREEMODE20191117_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <treeviewsearchline.h>

QT_BEGIN_NAMESPACE

class Ui_TreeMode20191117Class
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    TreeViewSearchLine *lineEdit;
    QTreeView *treeView;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSplitter *splitter;
    QTreeView *treeView_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TreeMode20191117Class)
    {
        if (TreeMode20191117Class->objectName().isEmpty())
            TreeMode20191117Class->setObjectName(QStringLiteral("TreeMode20191117Class"));
        TreeMode20191117Class->resize(265, 232);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TreeMode20191117Class->sizePolicy().hasHeightForWidth());
        TreeMode20191117Class->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(TreeMode20191117Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lineEdit = new TreeViewSearchLine(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_3->addWidget(lineEdit);

        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));

        verticalLayout_3->addWidget(treeView);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_3->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_3->addWidget(pushButton_3);


        horizontalLayout->addLayout(verticalLayout_3);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeView_2 = new QTreeView(splitter);
        treeView_2->setObjectName(QStringLiteral("treeView_2"));
        splitter->addWidget(treeView_2);

        horizontalLayout->addWidget(splitter);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pushButton);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);


        horizontalLayout->addLayout(verticalLayout);

        TreeMode20191117Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TreeMode20191117Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 265, 23));
        TreeMode20191117Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TreeMode20191117Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TreeMode20191117Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TreeMode20191117Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TreeMode20191117Class->setStatusBar(statusBar);

        retranslateUi(TreeMode20191117Class);

        QMetaObject::connectSlotsByName(TreeMode20191117Class);
    } // setupUi

    void retranslateUi(QMainWindow *TreeMode20191117Class)
    {
        TreeMode20191117Class->setWindowTitle(QApplication::translate("TreeMode20191117Class", "TreeMode20191117", 0));
        pushButton_2->setText(QApplication::translate("TreeMode20191117Class", "\345\217\226\346\266\210\347\224\237\346\210\220\347\274\226\347\250\213", 0));
        pushButton_3->setText(QApplication::translate("TreeMode20191117Class", "\347\241\256\350\256\244\347\224\237\346\210\220\347\274\226\347\250\213", 0));
        pushButton->setText(QApplication::translate("TreeMode20191117Class", "\345\274\271\345\207\272treeView", 0));
    } // retranslateUi

};

namespace Ui {
    class TreeMode20191117Class: public Ui_TreeMode20191117Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEMODE20191117_H
