#ifndef  SEARCHLINE_H
#define SEARCHLINE_H

#include <QLineEdit>
#include <QPushButton>

class TreeViewSearchLine : public QLineEdit
{
	Q_OBJECT
public:
	TreeViewSearchLine(QWidget *parent = 0);
signals:
	void  searchTextToTreeView(const QString &);
public slots:
    void slotSearchBtnClicked();
private:
	QPushButton *searchBtn;
};

#endif // SEARCHLINE_H