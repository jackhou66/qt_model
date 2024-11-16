#include "TreeViewSearchLine.h"

#include <QHBoxLayout>

TreeViewSearchLine::TreeViewSearchLine(QWidget *parent)
	:QLineEdit(parent)
{
	QHBoxLayout *mainLayout = new QHBoxLayout;
	searchBtn = new QPushButton;
	searchBtn->setFixedSize(13, 13);
	searchBtn->setCursor(Qt::PointingHandCursor);
	searchBtn->setToolTip(tr("search"));
	searchBtn->setStyleSheet("QPushButton{border-image:url(C:/Users/user/Desktop/searchpic.png);""background:transparent;cursor:pointer;}");
	setPlaceholderText(tr("search"));
	mainLayout->addWidget(searchBtn);
	mainLayout->addStretch();
	//mainLayout->setContentsMargins(8,8,8,8);//�������õ�8��������ͼ����ߵĿ�ȣ�����ͼ��Ͳ��������������ı߿��ˡ�
	mainLayout->setContentsMargins(8, 0, 0, 0);
	setTextMargins(13+8+2, 0, 0, 0);
	setContentsMargins(0, 0, 0, 0);
	setLayout(mainLayout);
	setStyleSheet("height:29px;border:1px solid #eaeaea;border-radius:5px;");

	connect(searchBtn, &QPushButton::clicked, this, &TreeViewSearchLine::slotSearchBtnClicked);

	//connect(this, &QLineEdit::editingFinished, this, &TreeViewSearchLine::searchBtnClicked);
}
void TreeViewSearchLine::slotSearchBtnClicked()
{
	QString str = this->text();
	emit searchTextToTreeView(str);
}
//setTextMargins(13+8+2,0,0,0);   ����13��ͼ��Ŀ�ȣ�8�ǲ��ֵ�left margin��Ҳ�����������õ��Ǹ���2�Ƕ�������ף���Ҫ��Ϊ�����ۡ�

//�����õ�������ͼ���СΪ13*13�������Ǹ�������ť����Ϊ�̶���С13*13�������е�