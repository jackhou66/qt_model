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
	//mainLayout->setContentsMargins(8,8,8,8);//这里设置的8个长度是图标左边的宽度，这样图标就不会紧挨着搜索框的边框了。
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
//setTextMargins(13+8+2,0,0,0);   这里13是图标的宽度，8是布局的left margin，也就是上面设置的那个，2是额外的留白，主要是为了美观。

//这里用到的搜索图标大小为13*13，所以那个搜索按钮设置为固定大小13*13，代码中的