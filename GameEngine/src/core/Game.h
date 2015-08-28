#ifndef BENGINE_GAME_H
#define BENGINE_GAME_H

#include <Engine.h>

#include <string>

#include <qt/QtCore/qmap.h>
#include <qt/QtCore/qstring.h>

#include <core/GameClock.h>
#include <core/Scene.h>
#include <input/InputManager.h>
#include <rendering/RenderingEngine.h>
#include <util/GameUpdater.h>
#include <util/SceneLoader.h>

using std::string;

using Input::InputManager;
using Rendering::RenderingEngine;
using Util::GameUpdater;
using Util::SceneLoader;

namespace Core
{
	class ENGINE_DLL_EXPORT_IMPORT Game;

	//Global function to access the single game instance
	ENGINE_DLL_EXPORT_IMPORT Game* getGame();

	class Game
	{
		string m_name;
		string m_filePath;
		int m_fps;

		GameClock m_clock;
		GameUpdater m_updater;
		InputManager m_input;
		RenderingEngine* m_renderer;
		bool m_isOwnRenderer;
		SceneLoader* m_sceneLoader;

		QMap<uint, string> m_scenes;
		uint m_defaultSceneID;
		uint m_activeSceneID;
		uint m_requestedSceneID;
		Scene* m_activeScene;

	public:
		Game(const string& filePath = "./res/game/game.xml");
		Game(const QString& filePath);
		Game(const char* filePath);
		virtual ~Game();

		void setName(const string& name);
		void setSceneLoader(SceneLoader* loader);
		void setRenderer(RenderingEngine* renderer);
		void setActiveScene(Scene* scene);

		void run();
		void pause();
		void resume();

		void update();
		void calcFps();

		void loadScene(uint sceneID);

		GameClock* getClock();
		InputManager* getInput();
		RenderingEngine* getRenderer();
		Scene* getActiveScene();
		int getFps();

	protected:
		//Override these functions
		virtual void mainLoop();

	private:
		//Don't override these functions
		void initialize();
		void loadFromXml();
		void loadDefaultScene();
		void shutdown();
		void newFrame();
		void render();
		void loadRequestedScene();
	};
}

#endif //BENGINE_GAME_H