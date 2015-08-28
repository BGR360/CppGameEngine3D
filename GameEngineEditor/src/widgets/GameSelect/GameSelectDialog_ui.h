#ifndef UI_GAME_SELECT_DIALOG_H
#define UI_GAME_SELECT_DIALOG_H

#include <qt/QtWidgets/qwidget.h>
#include <qt/QtWidgets/qboxlayout.h>
#include <qt/QtWidgets/qformlayout.h>
#include <qt/QtWidgets/qheaderview.h>
#include <qt/QtWidgets/qlabel.h>
#include <qt/QtWidgets/qlineedit.h>
#include <qt/QtWidgets/qpushbutton.h>
#include <qt/QtWidgets/qlayoutitem.h>
#include <qt/QtWidgets/qtablewidget.h>
#include <qt/QtWidgets/qtableview.h>

namespace Ui
{
	class GameSelectDialog
	{
	public:
		QVBoxLayout* mainLayout;
		QTableWidget* recentGamesWidget;
		QHBoxLayout* buttonLayout;
		QPushButton* newButton;
		QPushButton* openButton;
		QLabel* recentGamesLabel;

		void setupUi(QWidget* parent)
		{
			mainLayout = new QVBoxLayout;
			recentGamesWidget = new QTableWidget(parent);
			buttonLayout = new QHBoxLayout;
			newButton = new QPushButton("New Game");
			openButton = new QPushButton("Open Existing");
			recentGamesLabel = new QLabel("Recent Games");

			mainLayout->addLayout(buttonLayout);
			mainLayout->addWidget(recentGamesLabel);
			mainLayout->addWidget(recentGamesWidget);

			buttonLayout->addWidget(newButton);
			buttonLayout->addWidget(openButton);

			recentGamesWidget->horizontalHeader()->setVisible(false);
			recentGamesWidget->verticalHeader()->setVisible(false);
			recentGamesWidget->setDragEnabled(false);
			recentGamesWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
			recentGamesWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
			recentGamesWidget->setSelectionMode(QAbstractItemView::SingleSelection);
			recentGamesWidget->setSortingEnabled(false);

			parent->setLayout(mainLayout);
		}
	};

	class NewGameDialog
	{
	public:
		QVBoxLayout* mainLayout;
		QFormLayout* formLayout;
		QLineEdit* nameLineEdit;
		QHBoxLayout* locationLayout;
		QLabel* locationLabel;
		QLineEdit* locationLineEdit;
		QPushButton* browseButton;
		QHBoxLayout* bottomLayout;
		QHBoxLayout* buttonsLayout;
		QSpacerItem* spacer;
		QPushButton* okButton;
		QPushButton* cancelButton;

		void setupUi(QWidget* parent)
		{
			mainLayout = new QVBoxLayout;
			formLayout = new QFormLayout;
			nameLineEdit = new QLineEdit("New Game");
			locationLayout = new QHBoxLayout;
			locationLabel = new QLabel("Location:");
			locationLineEdit = new QLineEdit;
			browseButton = new QPushButton("...");
			bottomLayout = new QHBoxLayout;
			buttonsLayout = new QHBoxLayout;
			//spacer = new QSpacerItem;
			okButton = new QPushButton("Ok");
			cancelButton = new QPushButton("Cancel");

			mainLayout->addLayout(formLayout);
			mainLayout->addLayout(bottomLayout);

			formLayout->addRow("Game Name:", nameLineEdit);
			formLayout->addRow(locationLayout);

			locationLayout->addWidget(locationLabel);
			locationLayout->addWidget(locationLineEdit);
			locationLayout->addWidget(browseButton);

			locationLineEdit->setBaseSize(175, 20);
			browseButton->setFixedWidth(23);

			bottomLayout->addLayout(buttonsLayout);
			bottomLayout->setAlignment(buttonsLayout, Qt::AlignHCenter);

			buttonsLayout->addWidget(okButton);
			buttonsLayout->addWidget(cancelButton);

			okButton->setFixedSize(121, 23);
			cancelButton->setFixedSize(121, 23);
			browseButton->setToolTip("Browse...");

			parent->setLayout(mainLayout);
			parent->resize(550, 130);
		}
	};
}

#endif //UI_GAME_SELECT_DIALOG_H