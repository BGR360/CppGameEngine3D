#ifndef UI_GAME_OBJECT_HIERARCHY_WIDGET_H
#define UI_GAME_OBJECT_HIERARCHY_WIDGET_H

#include <qt/QtWidgets/qwidget.h>
#include <qt/QtWidgets/qboxlayout.h>
#include <qt/QtWidgets/qgridlayout.h>
#include <qt/QtWidgets/qheaderview.h>
#include <qt/QtWidgets/qlabel.h>
#include <qt/QtWidgets/qpushbutton.h>
#include <qt/QtWidgets/qtreewidget.h>

#include <widgets/ActionButton/ActionButton.h>

namespace Ui
{
	class GameObjectHierarchyWidget
	{
	public:
		QTreeView* treeView;
		ActionButton* editButton;
		ActionButton* addButton;
		ActionButton* removeButton;

		QVBoxLayout* mainLayout;
		QGridLayout* buttonLayout;

		void setupUi(QWidget* parent)
		{
			treeView = new QTreeView;
			editButton = new ActionButton("Edit");
			addButton = new ActionButton("Add");
			removeButton = new ActionButton("Remove");

			mainLayout = new QVBoxLayout;
			buttonLayout = new QGridLayout;

			mainLayout->addWidget(treeView);
			mainLayout->addLayout(buttonLayout);
			mainLayout->setMargin(5);

			buttonLayout->addWidget(editButton, 0, 0, 1, 0);
			buttonLayout->addWidget(addButton, 1, 0);
			buttonLayout->addWidget(removeButton, 1, 1);
			buttonLayout->setMargin(0);

			treeView->header()->hide();
			treeView->setIndentation(10);
			treeView->setDragDropMode(QTreeView::DragDropMode::DragDrop);
			treeView->setDragDropOverwriteMode(false);
			treeView->setDropIndicatorShown(true);
			treeView->setItemsExpandable(true);
			treeView->setExpandsOnDoubleClick(false);
			treeView->setStyleSheet(styleSheet2);
			
			parent->setLayout(mainLayout);
		}

		const QString styleSheet0 = 
			"QTreeView {"
			"    show-decoration-selected: 1;"
			"}"

			"QTreeView::item {"
			"     border: 1px solid #d9d9d9;"
			"    border-top-color: transparent;"
			"    border-bottom-color: transparent;"
			"}"

			"QTreeView::item:hover {"
			"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
			"    border: 1px solid #bfcde4;"
			"}"

			"QTreeView::item:selected {"
			"    border: 1px solid #567dbc;"
			"}"

			"QTreeView::item:selected:active{"
			"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);"
			"}"

			"QTreeView::item:selected:!active {"
			"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);"
			"}";

		const QString styleSheet1 =
			"QTreeView::branch { background: palette(base); }" 
			"QTreeView::branch:has-siblings:!adjoins-item { background: cyan; }"
			"QTreeView::branch:has-siblings:adjoins-item { background: red; }"
			"QTreeView::branch:!has-children:!has-siblings:adjoins-item { background: blue; }"
			"QTreeView::branch:closed:has-children:has-siblings { background: pink; }"
			"QTreeView::branch:has-children:!has-siblings:closed { background: gray; }"
			"QTreeView::branch:open:has-children:has-siblings { background: magenta; }"
			"QTreeView::branch:open:has-children:!has-siblings { background: green; }";

		const QString styleSheet2 =
			"QTreeView::branch { background: palette(base); }"
			"QTreeView::branch:open { border-image: none; image: url(C:/Users/BGR/Documents/Visual Studio 2013/Projects/GameEngine/GameEngineEditor/res/icons/branch-open.png); }"
			"QTreeView::branch:closed:adjoins-item { border-image: none; image: url(C:/Users/BGR/Documents/Visual Studio 2013/Projects/GameEngine/GameEngineEditor/res/icons/branch-closed.png); }";
	};
}

#endif //UI_GAME_OBJECT_HIERARCHY_WIDGET_H