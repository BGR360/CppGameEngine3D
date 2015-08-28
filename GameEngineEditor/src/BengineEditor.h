#ifndef BENGINE_EDITOR_BENGINE_EDITOR_H
#define BENGINE_EDITOR_BENGINE_EDITOR_H

#include <core/Game.h>

#include <qt/QtCore/qabstractitemmodel.h>
#include <qt/QtWidgets/qmainwindow.h>

#include <widgets/GameSelect/GameSelectDialog.h>

namespace Ui
{
	class BengineEditor;
}

namespace Actions
{
	class BengineEditor;
}

class QMenu;
class QToolBar;
class GameObjectItem;

class BengineEditor : public QMainWindow
{
	Q_OBJECT

public:
	BengineEditor(QWidget* parent = 0);
	virtual ~BengineEditor();

	void createActions();
	void createMenus();
	void createToolbars();
	void createStatusBar();
	void createSettings();
	void connectSlots();

	void printSettings();

	GameObjectItem* getCurrentGameObject();

signals:
	void sceneChanged();

public slots:
	void show();
	void undo();
	void redo();

	void loadGame();
	void pauseGame();
	void resumeGame();
	void updateGame();
	void setupHierarchyView();
	void setupResourceView();

	void newScene();
	void openScene();
	void closeScene();
	void editGameObject();
	void addGameObject();
	void removeGameObject();
	void focusOnGameObject();
	void addResource();
	void removeResource();

	void updateSelectedGameObject(const QModelIndex& index);

protected:
	virtual void keyPressEvent(QKeyEvent* e);
	virtual void resizeEvent(QResizeEvent* e);

private:
	Ui::BengineEditor* ui;
	Actions::BengineEditor* actions;

	QMenu* fileMenu;
	QMenu* editMenu;
	QMenu* gameObjectMenu;
	QMenu* resourcesMenu;

	QToolBar* fileToolbar;
	QToolBar* editToolbar;
	QToolBar* gameObjectToolbar;
	QToolBar* resourcesToolbar;


	GameInfo m_currentGameInfo;
	Core::Game* m_game;
	QPersistentModelIndex m_currentGameObjectSelected;
};

#endif //BENGINE_EDITOR_BENGINE_EDITOR_H