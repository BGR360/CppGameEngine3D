#ifndef UI_RESOURCE_EXPLORER_WIDGET_H
#define UI_RESOURCE_EXPLORER_WIDGET_H

#include <qt/QtWidgets/qwidget.h>
#include <qt/QtWidgets/qboxlayout.h>
#include <qt/QtWidgets/qgridlayout.h>
#include <qt/QtWidgets/qlabel.h>
#include <qt/QtWidgets/qlistview.h>
#include <qt/QtWidgets/qpushbutton.h>
#include <qt/QtWidgets/qsplitter.h>

#include <widgets/ActionButton/ActionButton.h>

namespace Ui
{
	class ResourceExplorerWidget
	{
	public:
		class LeftView : public QListView
		{
			QSize sizeHint() const
			{
				return QSize(150, 219);
			}
		};

		QVBoxLayout* mainLayout;
		QSplitter* splitter;
		LeftView* leftView;
		QWidget* rightWidget;
		QVBoxLayout* rightLayout;
		QListView* rightView;
		QHBoxLayout* buttonLayout;
		ActionButton* addButton;
		ActionButton* removeButton;


		void setupUi(QWidget* parent)
		{
			mainLayout = new QVBoxLayout;
			splitter = new QSplitter(Qt::Horizontal);
			
			leftView = new LeftView;
			rightWidget = new QWidget;
			rightLayout = new QVBoxLayout;
			buttonLayout = new QHBoxLayout;
			addButton = new ActionButton("Add");
			removeButton = new ActionButton("Remove");
			rightView = new QListView;

			mainLayout->addWidget(splitter);
			mainLayout->setMargin(0);

			splitter->addWidget(leftView);
			splitter->addWidget(rightWidget);

			rightLayout->addWidget(rightView);
			rightLayout->addLayout(buttonLayout);
			rightLayout->setMargin(0);

			rightWidget->setLayout(rightLayout);

			buttonLayout->addWidget(addButton);
			buttonLayout->addWidget(removeButton);
			buttonLayout->setMargin(0);

			parent->setLayout(mainLayout);
		}
	};
}

#endif //UI_RESOURCE_EXPLORER_WIDGET_H