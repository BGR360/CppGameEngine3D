#ifndef BENGINE_GAME_UPDATER_H
#define BENGINE_GAME_UPDATER_H

#include <Engine.h>

#include <qt/QtCore/qtimer.h>

namespace Core
{
	class Game;
}

using Core::Game;

namespace Util
{
	class GameUpdater : public QObject
	{
		Q_OBJECT

		Game* m_game;
		QTimer m_updateTimer;
		QTimer m_fpsTimer;

	public:
		GameUpdater(Game* game);
		virtual ~GameUpdater();

		void start();
		void stop();

	public slots:
		void updateGame();
		void updateFps();
	};
}

#endif //BENGINE_GAME_UPDATER_H