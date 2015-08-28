#include "GameObjectHierarchyWidget.h"
#include "GameObjectHierarchyWidget_ui.h"

#include <qt/QtWidgets/qmenu.h>
#include <qt/QtWidgets/qtreeview.h>

GameObjectHierarchyWidget::GameObjectHierarchyWidget(QWidget* parent)
	: QWidget(parent),
	m_ui(new Ui::GameObjectHierarchyWidget)
{
	m_ui->setupUi(this);
	setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(createContextMenu(QPoint)));
}

void GameObjectHierarchyWidget::createContextMenu(const QPoint& pos)
{
	QList<QAction*> act = actions();
	QList<QAction*>::iterator i = act.begin();

	QMenu* menu = new QMenu(this);

	for (i; i != act.end(); i++)
	{
		menu->addAction(*i);
	}

	menu->popup(mapToGlobal(pos));
}

GameObjectHierarchyWidget::~GameObjectHierarchyWidget()
{
	delete m_ui;
}