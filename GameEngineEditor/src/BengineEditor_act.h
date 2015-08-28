#ifndef ACTIONS_BENGINE_EDITOR_H
#define ACTIONS_BENGINE_EDITOR_H

#include <qt/QtWidgets/qaction.h>

namespace Actions
{
	class BengineEditor
	{
	public:
		QAction* loadGame;

		QAction* newScene;
		QAction* openScene;
		QAction* closeScene;

		QAction* undo;
		QAction* redo;

		QAction* editGameObject;
		QAction* addGameObject;
		QAction* removeGameObject;
		QAction* focusOnObject;

		QAction* addResource;
		QAction* removeResource;

		void setupActions(QMainWindow* BengineEditor)
		{
			//Create objects
			loadGame = new QAction("Change Game", BengineEditor);

			newScene = new QAction("&New Scene", BengineEditor);
			openScene = new QAction("&Open Scene", BengineEditor);
			closeScene = new QAction("&Close Scene", BengineEditor);

			undo = new QAction("&Undo", BengineEditor);
			redo = new QAction("&Redo", BengineEditor);

			editGameObject = new QAction("Edit", BengineEditor);
			addGameObject = new QAction("Add", BengineEditor);
			removeGameObject = new QAction("Remove", BengineEditor);
			focusOnObject = new QAction("Focus", BengineEditor);

			addResource = new QAction("Add", BengineEditor);
			removeResource = new QAction("Remove", BengineEditor);

			//Set shortcuts
			newScene->setShortcut(QKeySequence::New);
			openScene->setShortcut(QKeySequence::Open);
			closeScene->setShortcut(QKeySequence::Close);
			undo->setShortcut(QKeySequence::Undo);
			redo->setShortcut(QKeySequence::Redo);
			removeGameObject->setShortcut(QKeySequence::Delete);

			//Connect slots
			QObject::connect(loadGame, SIGNAL(triggered()), BengineEditor, SLOT(loadGame()));
			QObject::connect(newScene, SIGNAL(triggered()), BengineEditor, SLOT(newScene()));
			QObject::connect(openScene, SIGNAL(triggered()), BengineEditor, SLOT(openScene()));
			QObject::connect(closeScene, SIGNAL(triggered()), BengineEditor, SLOT(closeScene()));
			QObject::connect(undo, SIGNAL(triggered()), BengineEditor, SLOT(undo()));
			QObject::connect(redo, SIGNAL(triggered()), BengineEditor, SLOT(redo()));
			QObject::connect(editGameObject, SIGNAL(triggered()), BengineEditor, SLOT(editGameObject()));
			QObject::connect(addGameObject, SIGNAL(triggered()), BengineEditor, SLOT(addGameObject()));
			QObject::connect(removeGameObject, SIGNAL(triggered()), BengineEditor, SLOT(removeGameObject()));
			QObject::connect(focusOnObject, SIGNAL(triggered()), BengineEditor, SLOT(focusOnGameObject()));
			QObject::connect(addResource, SIGNAL(triggered()), BengineEditor, SLOT(addResource()));
			QObject::connect(removeResource, SIGNAL(triggered()), BengineEditor, SLOT(removeResource()));
		}
	};
}

#endif //ACTIONS_BENGINE_EDITOR_H