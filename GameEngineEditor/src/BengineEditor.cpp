#include "BengineEditor.h"
#include "BengineEditor_ui.h"
#include "BengineEditor_act.h"

#include "ModelTest.h"

#include <qt/QtCore/qcoreapplication.h>
#include <qt/QtCore/qdebug.h>
#include <qt/QtCore/qsettings.h>
#include <qt/QtWidgets/qdialog.h>
#include <qt/QtWidgets/qfiledialog.h>
#include <qt/QtGui/qopenglcontext.h>
#include <qt/QtWidgets/qopenglwidget.h>
#include <qt/QtWidgets/qmenu.h>
#include <qt/QtWidgets/qmenubar.h>
#include <qt/QtWidgets/qstatusbar.h>
#include <qt/QtWidgets/qtoolbar.h>

#include <widgets/GameObjectEditDialog/GameObjectEditDialog.h>

#include <modelview/SceneGraphModel.h>
#include <modelview/EditorScene.h>
#include <modelview/EditorSceneLoader.h>
#include <EditorComponent.h>

using namespace Core;

BengineEditor::BengineEditor(QWidget* parent)
	: QMainWindow(parent),
	ui(new Ui::BengineEditor),
	actions(new Actions::BengineEditor),
	m_game(0)
{
	ui->setupUi(this);

	createActions();
	createSettings();
	createMenus();
	createToolbars();
	createStatusBar();
	connectSlots();

	setFocusPolicy(Qt::StrongFocus);
}

void BengineEditor::createActions()
{
	actions->setupActions(this);

	//Attach actions to buttons
	ui->gameObjectHierarchy->ui()->editButton->setAction(actions->editGameObject);
	ui->gameObjectHierarchy->ui()->addButton->setAction(actions->addGameObject);
	ui->gameObjectHierarchy->ui()->removeButton->setAction(actions->removeGameObject);

	ui->resourceExplorer->ui()->addButton->setAction(actions->addResource);
	ui->resourceExplorer->ui()->removeButton->setAction(actions->removeResource);

	//Add actions to widgets' context menus
	ui->gameObjectHierarchy->addAction(actions->editGameObject);
	ui->gameObjectHierarchy->addAction(actions->addGameObject);
	ui->gameObjectHierarchy->addAction(actions->removeGameObject);

	ui->resourceExplorer->addAction(actions->addResource);
	ui->resourceExplorer->addAction(actions->removeResource);
}

void BengineEditor::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	editMenu = menuBar()->addMenu(tr("&Edit"));
	gameObjectMenu = menuBar()->addMenu(tr("&GameObject"));
	resourcesMenu = menuBar()->addMenu(tr("Re&sources"));

	fileMenu->addAction(actions->newScene);
	fileMenu->addAction(actions->openScene);
	fileMenu->addAction(actions->closeScene);
	fileMenu->addAction(actions->loadGame);

	editMenu->addAction(actions->undo);
	editMenu->addAction(actions->redo);

	gameObjectMenu->addAction(actions->addGameObject);
	gameObjectMenu->addAction(actions->editGameObject);
	gameObjectMenu->addAction(actions->removeGameObject);
	gameObjectMenu->addSeparator();
	gameObjectMenu->addAction(actions->focusOnObject);

	resourcesMenu->addAction(actions->addResource);
	resourcesMenu->addAction(actions->removeResource);
}

void BengineEditor::createToolbars()
{
	fileToolbar = addToolBar("File");
	editToolbar = addToolBar("Edit");
	gameObjectToolbar = addToolBar("GameObject");
	resourcesToolbar = addToolBar("Resources");
	
	fileToolbar->addActions(fileMenu->actions());
	editToolbar->addActions(editMenu->actions());
	gameObjectToolbar->addActions(gameObjectMenu->actions());
	resourcesToolbar->addActions(resourcesMenu->actions());
}

void BengineEditor::createStatusBar()
{
	statusBar()->setBackgroundRole(QPalette::Dark);
	statusBar()->showMessage("Ready");
}

void BengineEditor::createSettings()
{
	QCoreApplication::setOrganizationName("Bengine Ltd.");
	QCoreApplication::setApplicationName("Bengine Editor");

	QSettings settings;
	if (!settings.contains("rootDirectory"))
	{
		settings.setValue("rootDirectory", "./../TestGame/res/game/");
	}
}

void BengineEditor::connectSlots()
{
	QTreeView* hierarchy = ui->gameObjectHierarchy->ui()->treeView;
	connect(hierarchy, SIGNAL(activated(QModelIndex)), this, SLOT(updateSelectedGameObject(QModelIndex)));
	connect(hierarchy, SIGNAL(pressed(QModelIndex)), this, SLOT(updateSelectedGameObject(QModelIndex)));

	connect(this, SIGNAL(sceneChanged()), this, SLOT(updateGame()));

	SceneViewWidget* sceneView = ui->sceneView;
	connect(sceneView, SIGNAL(mouseEntered()), this, SLOT(resumeGame()));
	connect(sceneView, SIGNAL(mouseLeft()), this, SLOT(pauseGame()));
}

void BengineEditor::printSettings()
{
	QSettings settings;
	QStringList keys = settings.allKeys();

	qDebug() << "Settings:";

	QStringList::iterator i = keys.begin();
	for (i; i != keys.end(); i++)
	{
		qDebug() << *i << " = " << settings.value(*i).toString();
	}
}

GameObjectItem* BengineEditor::getCurrentGameObject()
{
	SceneGraphModel* model = static_cast<SceneGraphModel*>(ui->gameObjectHierarchy->ui()->treeView->model());
	GameObjectItem* currentSelected = model->getItem(m_currentGameObjectSelected);
	return currentSelected;
}


void BengineEditor::show()
{
	QMainWindow::show();

	this->loadGame();
}

void BengineEditor::undo()
{
	qDebug() << "Undo.";
}

void BengineEditor::redo()
{
	qDebug() << "Redo.";
}

void BengineEditor::loadGame()
{
	m_currentGameInfo = GameSelectDialog::getGame(this);

	if (m_currentGameInfo.filePath != "")
	{
		statusBar()->showMessage(
			QString("Loading Game '") + m_currentGameInfo.name + QString("' from file ") + m_currentGameInfo.filePath);

		//Create a Bengine game from the specified file path in GameInfo
		m_game = new Game(m_currentGameInfo.filePath);
		m_game->setSceneLoader(new EditorSceneLoader);
		m_game->setRenderer(ui->sceneView);
		m_game->run();

		statusBar()->showMessage("Ready");

		pauseGame();
		updateGame();

		this->setupHierarchyView();
		this->setupResourceView();
	}
	else
	{
		statusBar()->showMessage("No Game selected", 3000);
	}
}

void BengineEditor::pauseGame()
{
	if (m_game)
	{
		m_game->pause();
		m_game->getInput()->reset();
	}
}
void BengineEditor::resumeGame()
{
	if (m_game)
	{
		//Resume the EditorComponent
		EditorScene* scene = static_cast<EditorScene*>(m_game->getActiveScene());
		GameObjectItem* root = 0;
		if (scene)
		{
			root = static_cast<GameObjectItem*>(scene->getRoot());
		}
		if (root)
		{
			EditorComponent* component = root->getComponent<EditorComponent>();
			component->resume();
		}
		else
		{
			qDebug() << "Couldn't get to root object";
		}

		//Then resume the game
		m_game->resume();
	}
}
void BengineEditor::updateGame()
{
	if (m_game)
	{
		m_game->update();
		m_game->update();
	}
}

void BengineEditor::setupHierarchyView()
{
	EditorScene* activeScene = dynamic_cast<EditorScene*>(m_game->getActiveScene());

	if (activeScene != 0)
	{
		statusBar()->showMessage("Setting Up GameObject Hierarchy");

		SceneGraphModel* sceneGraphHierarchy = new SceneGraphModel(dynamic_cast<GameObjectItem*>(activeScene->getRoot()), this);
		ui->gameObjectHierarchy->ui()->treeView->setModel(sceneGraphHierarchy);

		new ModelTest(sceneGraphHierarchy, this);
	}
	else
	{
		statusBar()->showMessage("There is no active scene");
	}

}

void BengineEditor::setupResourceView()
{
	//TODO implement
}


void BengineEditor::newScene()
{
	qDebug() << "New Scene.";
}

void BengineEditor::openScene()
{
	qDebug() << "Open Scene.";

	QSettings settings;
	QString rootDir = settings.value("rootDirectory").toString();

	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Scene file"), rootDir, tr("Scene Files (*.xml *.bscn *.scn)"));

	statusBar()->showMessage(QString("Opening file \n%1").arg(fileName));
}

void BengineEditor::closeScene()
{
	qDebug() << "Close Scene.";
}

void BengineEditor::editGameObject()
{
	qDebug() << "Edit GameObject.";

	GameObjectItem* currentSelected = getCurrentGameObject();

	if (currentSelected)
	{
		GameObjectEditDialog* dialog = new GameObjectEditDialog(currentSelected, this);
		dialog->show();

		connect(dialog, SIGNAL(gameObjectChanged()), this, SLOT(updateGame()));
	}

	emit sceneChanged();
}

void BengineEditor::addGameObject()
{
	qDebug() << "Add GameObject.";
	QTreeView* treeView = ui->gameObjectHierarchy->ui()->treeView;
	SceneGraphModel* model = static_cast<SceneGraphModel*>(treeView->model());

	model->insertRow(model->rowCount(m_currentGameObjectSelected), m_currentGameObjectSelected);
	treeView->setExpanded(m_currentGameObjectSelected, true);

	emit sceneChanged();
}

void BengineEditor::removeGameObject()
{
	qDebug() << "Remove GameObject.";
	QTreeView* treeView = ui->gameObjectHierarchy->ui()->treeView;
	SceneGraphModel* model = static_cast<SceneGraphModel*>(treeView->model());
	
	if (m_currentGameObjectSelected.isValid())
	{
		GameObjectItem* currentGameObject = getCurrentGameObject();
		if (currentGameObject)
		{
			model->removeRow(currentGameObject->row(), model->parent(m_currentGameObjectSelected));
			treeView->setExpanded(m_currentGameObjectSelected, true);
		}
	}

	emit sceneChanged();
}

void BengineEditor::focusOnGameObject()
{
	qDebug() << "Focusing!!";

	GameObjectItem* currentSelected = getCurrentGameObject();
	EditorScene* scene = static_cast<EditorScene*>(m_game->getActiveScene());
	GameObjectItem* root = static_cast<GameObjectItem*>(scene->getRoot());

	if (currentSelected)
	{
		EditorComponent* component = root->getComponent<EditorComponent>();
		component->setFocus(currentSelected->getTransform()->getPosition());
	}
	else
	{
		qDebug() << "Couldn't get to currentSelected";
	}
}

void BengineEditor::addResource()
{
	qDebug() << "Add Resource.";

	emit sceneChanged();
}

void BengineEditor::removeResource()
{
	qDebug() << "Remove Resource.";

	emit sceneChanged();
}

void BengineEditor::updateSelectedGameObject(const QModelIndex& index)
{
	m_currentGameObjectSelected = index;

	QTreeView* hierarchy = ui->gameObjectHierarchy->ui()->treeView;
	SceneGraphModel* model = static_cast<SceneGraphModel*>(hierarchy->model());
	GameObject* currentObject = model->getItem(m_currentGameObjectSelected);

	QModelIndex parent = model->parent(index);

	statusBar()->showMessage(
		QString("Selected GameObject with id ") + QVariant(currentObject->getID()).toString()
		+ QString(" at index: row=") + QVariant(index.row()).toString() + QString(", col=") + QVariant(index.column()).toString()
		+ QString(" with parent: row=") + QVariant(parent.row()).toString() + QString(", col=") + QVariant(parent.column()).toString()
		+ QString(". Name is: ") + (static_cast<GameObjectItem*>(currentObject))->getName()
		+ QString(". rowCount=") + QVariant(model->rowCount(index)).toString());
}


void BengineEditor::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key::Key_F && !e->isAutoRepeat() && e->modifiers() == Qt::KeyboardModifier::NoModifier)
	{
		actions->focusOnObject->trigger();
	}
	else
	{
		QMainWindow::keyPressEvent(e);
	}
}

void BengineEditor::resizeEvent(QResizeEvent* e)
{
	QMainWindow::resizeEvent(e);
	SceneViewWidget* sceneView = ui->sceneView;
	sceneView->updateSize();
}



BengineEditor::~BengineEditor()
{
	delete ui;
	delete actions;
}