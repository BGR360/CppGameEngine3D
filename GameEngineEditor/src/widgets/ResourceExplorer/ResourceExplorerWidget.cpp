#include "ResourceExplorerWidget.h"
#include "ResourceExplorerWidget_ui.h"

ResourceExplorerWidget::ResourceExplorerWidget(QWidget* parent)
	: QWidget(parent),
	m_ui(new Ui::ResourceExplorerWidget)
{
	m_ui->setupUi(this);
}

QSize ResourceExplorerWidget::sizeHint() const
{
	return QSize(400, 200);
}

ResourceExplorerWidget::~ResourceExplorerWidget()
{
	delete m_ui;
}