#ifndef BENGINE_EDITOR_RESOURCE_EXPLORER_WIDGET_H
#define BENGINE_EDITOR_RESOURCE_EXPLORER_WIDGET_H

#include <qt/QtWidgets/qwidget.h>

namespace Ui
{
	class ResourceExplorerWidget;
}

class ResourceExplorerWidget : public QWidget
{
public:
	ResourceExplorerWidget(QWidget* parent = 0);
	virtual ~ResourceExplorerWidget();

	Ui::ResourceExplorerWidget* ui() { return m_ui; }

	QSize sizeHint() const;

private:
	Ui::ResourceExplorerWidget* m_ui;
};

#endif //BENGINE_EDITOR_RESOURCE_EXPLORER_WIDGET_H