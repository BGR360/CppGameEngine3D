#include "GameUpdater.h"

#include <core/Game.h>

namespace Util
{
	GameUpdater::GameUpdater(Game* game) : m_game(game)
	{
		connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
		connect(&m_fpsTimer, SIGNAL(timeout()), this, SLOT(updateFps()));
	}

	void GameUpdater::start()
	{
		m_updateTimer.start(0);
		m_fpsTimer.start(1000);
	}

	void GameUpdater::stop()
	{
		m_updateTimer.stop();
		m_updateTimer.stop();
	}

	void GameUpdater::updateGame()
	{
		m_game->update();
	}

	void GameUpdater::updateFps()
	{
		m_game->calcFps();
	}

	GameUpdater::~GameUpdater() {}
}