#ifndef UI_BENGINE_EDITOR_H
#define UI_BENGINE_EDITOR_H

#include <qt/QtWidgets/qboxlayout.h>
#include <qt/QtWidgets/qdockwidget.h>
#include <qt/QtWidgets/qlabel.h>
#include <qt/QtWidgets/qsplitter.h>

#include <widgets/GameObjectHierarchy/GameObjectHierarchyWidget.h>
#include <widgets/GameObjectHierarchy/GameObjectHierarchyWidget_ui.h>
#include <widgets/ResourceExplorer/ResourceExplorerWidget.h>
#include <widgets/ResourceExplorer/ResourceExplorerWidget_ui.h>
#include <widgets/SceneView/SceneViewWidget.h>

namespace Ui
{
	class BengineEditor
	{
	public:
		::GameObjectHierarchyWidget* gameObjectHierarchy;
		SceneViewWidget* sceneView;
		::ResourceExplorerWidget* resourceExplorer;

		QDockWidget* dockHierarchy;
		QDockWidget* dockResources;

		void setupUi(QMainWindow* BengineEditor)
		{
			gameObjectHierarchy = new ::GameObjectHierarchyWidget;

			sceneView = new SceneViewWidget;
			resourceExplorer = new ::ResourceExplorerWidget;
			dockHierarchy = new QDockWidget("GameObject Hierarchy");
			dockResources = new QDockWidget("ResourceExplorer");

			dockHierarchy->setAllowedAreas(
				Qt::DockWidgetArea::LeftDockWidgetArea | Qt::DockWidgetArea::RightDockWidgetArea);
			dockHierarchy->setFeatures(
				QDockWidget::DockWidgetMovable);
			dockResources->setAllowedAreas(
				Qt::DockWidgetArea::BottomDockWidgetArea);
			dockResources->setFeatures(
				QDockWidget::DockWidgetMovable);

			dockHierarchy->setWidget(gameObjectHierarchy);
			dockResources->setWidget(resourceExplorer);

			BengineEditor->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockHierarchy);
			BengineEditor->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, dockResources);
			BengineEditor->setCorner(Qt::Corner::BottomLeftCorner, Qt::DockWidgetArea::LeftDockWidgetArea);
			BengineEditor->setCorner(Qt::Corner::TopLeftCorner, Qt::DockWidgetArea::LeftDockWidgetArea);
			BengineEditor->setCorner(Qt::Corner::BottomRightCorner, Qt::DockWidgetArea::RightDockWidgetArea);
			BengineEditor->setCorner(Qt::Corner::TopRightCorner, Qt::DockWidgetArea::RightDockWidgetArea);

			BengineEditor->setCentralWidget(sceneView);
		}
	};
}

#endif //UI_BENGINE_EDITOR_H