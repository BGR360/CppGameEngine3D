#ifndef BENGINE_EDITOR_SCENE_VIEW_WIDGET_H
#define BENGINE_EDITOR_SCENE_VIEW_WIDGET_H

#include <rendering/RenderingEngine.h>
using Rendering::RenderingEngine;

class SceneViewWidget : public RenderingEngine
{
	Q_OBJECT

public:
	SceneViewWidget(QWidget* parent = 0);
	virtual ~SceneViewWidget();

	QSize sizeHint() const;

	static const double AREA_RATIO;
	static const double ASPECT_RATIO;

signals:
	void mouseEntered();
	void mouseLeft();

public slots:
	void updateSize();

protected:
	void enterEvent(QEvent* e);
	void leaveEvent(QEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseDoubleClickEvent(QMouseEvent* e);
	void resizeEvent(QResizeEvent* e);
};

#endif //BENGINE_EDITOR_SCENE_VIEW_WIDGET_H