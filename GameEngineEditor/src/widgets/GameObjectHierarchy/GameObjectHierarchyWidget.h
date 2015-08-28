#ifndef BENGINE_EDITOR_GAME_OBJECT_HIERARCHY_WIDGET_H
#define BENGINE_EDITOR_GAME_OBJECT_HIERARCHY_WIDGET_H

#include <qt/QtWidgets/qwidget.h>

namespace Ui
{
	class GameObjectHierarchyWidget;
}

class GameObjectHierarchyWidget : public QWidget
{
	Q_OBJECT

public:
	GameObjectHierarchyWidget(QWidget* parent = 0);
	virtual ~GameObjectHierarchyWidget();

	Ui::GameObjectHierarchyWidget* ui() { return m_ui; }

public slots:
	void createContextMenu(const QPoint& pos);

private:
	Ui::GameObjectHierarchyWidget* m_ui;
};

#endif //BENGINE_EDITOR_GAME_OBJECT_HIERARCHY_WIDGET_H