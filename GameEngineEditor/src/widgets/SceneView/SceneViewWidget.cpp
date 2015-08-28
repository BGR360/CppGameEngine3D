#include "SceneViewWidget.h"

#include <qt/QtCore/qdebug.h>

const double SceneViewWidget::AREA_RATIO = 0.4f;
const double SceneViewWidget::ASPECT_RATIO = 1.6f;

SceneViewWidget::SceneViewWidget(QWidget* parent)
	: RenderingEngine(parent)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void SceneViewWidget::updateSize()
{
	updateGeometry();
}

QSize SceneViewWidget::sizeHint() const
{
	QSize windowSize = window()->size();
	int windowArea = windowSize.width() * windowSize.height();
	double thisArea = (double)windowArea * AREA_RATIO;
	double height = sqrt(thisArea / ASPECT_RATIO);
	double width = ASPECT_RATIO * height;

	return QSize((int)width, (int)height);
}

void SceneViewWidget::enterEvent(QEvent* e)
{
	if (isActiveWindow())
	{
		setFocus();
	}
	emit mouseEntered();
}

void SceneViewWidget::leaveEvent(QEvent* e)
{
	if (isActiveWindow())
	{
		clearFocus();
	}
	emit mouseLeft();
}

void SceneViewWidget::mouseMoveEvent(QMouseEvent* e)
{
	RenderingEngine::mouseMoveEvent(e);
}

void SceneViewWidget::mousePressEvent(QMouseEvent* e)
{
	RenderingEngine::mousePressEvent(e);
}

void SceneViewWidget::mouseReleaseEvent(QMouseEvent* e)
{
	RenderingEngine::mouseReleaseEvent(e);
}

void SceneViewWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
	RenderingEngine::mouseDoubleClickEvent(e);
}

void SceneViewWidget::resizeEvent(QResizeEvent* e)
{
	RenderingEngine::resizeEvent(e);
}

SceneViewWidget::~SceneViewWidget()
{

}