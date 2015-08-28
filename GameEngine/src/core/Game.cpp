#include "Game.h"

#include <iostream>
#include <sstream>

#include <qt/QtCore/qxmlstream.h>
#include <qt/QtCore/qfile.h>
#include <qt/QtGui/qopenglcontext.h>

#include <exceptions/FileException.h>
#include <exceptions/FileNotFoundException.h>
#include <exceptions/InvalidOperationException.h>
#include <util/filesys/FileSystem.h>
#include <util/StringFunctions.h>

using std::cout;
using std::endl;
using std::stringstream;

using Exceptions::FileException;
using Exceptions::FileNotFoundException;
using Exceptions::InvalidOperationException;
using Util::FileSystem;
using Util::qStringToStdString;

namespace Core
{
	//There will be one instance of Game for the whole application. It will be globally accessible.
	Game* GAME = 0;

	Game* getGame()
	{
		return GAME;
	}

	Game::Game(const string& filePath)
		: m_name("Bengine Game"),
		m_filePath(filePath),
		m_fps(0), m_clock(),
		m_updater(this),
		m_renderer(),
		m_sceneLoader(0),
		m_defaultSceneID(0),
		m_activeSceneID(-1),
		m_requestedSceneID(-1),
		m_activeScene(0)
	{
		GAME = this;
	}

	Game::Game(const QString& filePath) : Game(qStringToStdString(filePath)) {}
	Game::Game(const char* filePath) : Game(string(filePath)) {}

	void Game::setName(const string& name)
	{
		m_name = name;
	}

	void Game::setActiveScene(Scene* scene)
	{
		m_activeScene = scene;
	}

	void Game::setSceneLoader(SceneLoader* loader)
	{
		if (!(m_sceneLoader == 0))
		{
			delete m_sceneLoader;
			m_sceneLoader = 0;
		}
		m_sceneLoader = loader;
	}

	void Game::setRenderer(RenderingEngine* renderer)
	{
		m_renderer = renderer;
		m_isOwnRenderer = false;
	}

	void Game::run()
	{
		cout << m_name << "!" << endl;

		this->initialize();

		//Start the GameUpdater to start the infinite game loop and update our fps at 1-second intervals
		m_updater.start();
	}

	void Game::pause()
	{
		m_updater.stop();
	}

	void Game::resume()
	{
		m_updater.start();
	}

	void Game::initialize()
	{
		cout << "Initializing..." << endl;

		//If our systems haven't been specified, initialize them to default values now
		if (m_sceneLoader == 0)
		{
			m_sceneLoader = new SceneLoader;
		}
		if (m_renderer == 0)
		{
			m_renderer = new RenderingEngine;
			m_isOwnRenderer = true;
		}

		m_renderer->setWindowTitle(m_name.c_str());
		m_renderer->initialize();
		m_renderer->makeCurrent();
		
		m_input.attachWidget(m_renderer);

		//Now that renderer is initialized, we can load our default scene (specified in the xml file)
		cout << "Loading game file..." << endl;
		this->loadFromXml();
		cout << "Success!" << endl;

		cout << "Loading default scene..." << endl;
		this->loadDefaultScene();

		if (m_activeScene == 0)
		{
			throw BengineException("Failed to load the default scene.");
		}
		m_activeScene->initialize();
		cout << "Success!" << endl;

		m_clock.start();
	}

	void Game::loadFromXml()
	{
		QXmlStreamReader xml;

		string finalFilePath = FileSystem::getInstance().path(m_filePath);
		QFile xmlFile(finalFilePath.c_str());

		if (!xmlFile.open(QFile::ReadOnly | QFile::Text))
		{
			throw FileNotFoundException(finalFilePath);
		}
		xml.setDevice(&xmlFile);

		//Compile the list of scenes
		if (xml.readNextStartElement()) 
		{
			if (xml.name() == "game" && xml.attributes().value("version") == "1.0")
			{
				while (xml.readNextStartElement())
				{
					if (xml.name() == "systems")
					{
						xml.skipCurrentElement();
					}
					else if (xml.name() == "scenes")
					{
						while (xml.readNextStartElement())
						{
							if (xml.name() == "scene")
							{
								//Add a pair of <uint, string> to represent <sceneID, sceneFilePath>
								uint sceneID = (uint)xml.attributes().value("id").toInt();
								string filePath;
								qStringToStdString(xml.attributes().value("src"), filePath);
								m_scenes[sceneID] = filePath;

								while (!(xml.name() == "scene" && xml.isEndElement()))
								{
									xml.readNext();
								}
							}
							else if (xml.name() == "default")
							{
								//Find out what our default scene is
								m_defaultSceneID = (uint)xml.readElementText().toInt();

								while (!(xml.name() == "default" && xml.isEndElement()))
								{
									xml.readNext();
								}
							}
							else
							{
								xml.skipCurrentElement();
							}
						}

						Q_ASSERT(xml.isEndElement());
						Q_ASSERT(xml.name() == "scenes");
					}
					else
					{
						xml.skipCurrentElement();
					}
				}
			}
			else
			{
				xml.raiseError(QObject::tr("The file is not a game file version 1.0."));
			}
			if (xml.hasError())
			{
				throw FileException(finalFilePath);
			}

			cout << "default scene: " << m_scenes[m_defaultSceneID] << endl;
		}
	}

	void Game::loadDefaultScene()
	{
		this->loadScene(m_defaultSceneID);
	}

	void Game::loadScene(uint sceneID)
	{
		m_requestedSceneID = sceneID;

		//If a scene is already loaded, we must delay the switching of scenes until all GameObjects have finished updating. 
		//Otherwise, we cause undefined behavior.
		if (m_activeScene == 0)
		{
			//If not, we can go ahead and load it now
			this->loadRequestedScene();
		}
	}

	GameClock* Game::getClock() { return &m_clock; }
	InputManager* Game::getInput() { return &m_input; }
	RenderingEngine* Game::getRenderer() { return m_renderer; }
	Scene* Game::getActiveScene()	{ return m_activeScene;	}
	int Game::getFps() { return m_fps; }

	void Game::update()
	{
		//cout << "Update!" << endl;
		this->newFrame();
		m_input.update();
		m_activeScene->update();

		//After we've updated the scene, it's safe to switch scenes if necessary
		if (m_requestedSceneID != m_activeSceneID)
		{
			this->loadRequestedScene();
		}

		this->mainLoop();

		this->render();
	}

	void Game::newFrame()
	{
		m_clock.newFrame();
	}

	void Game::mainLoop() {}

	void Game::render()
	{
		m_renderer->renderScene(m_activeScene);
	}

	void Game::calcFps()
	{
		m_fps = (int)(1.0f / m_clock.getDelta());

		//Update the game's title to show our fps
		stringstream ss;
		ss << m_name << " (" << m_fps << " fps)";
		m_renderer->setWindowTitle(ss.str().c_str());
	}

	void Game::loadRequestedScene()
	{
		Scene* previouslyLoadedScene = m_activeScene;
		uint previouslyLoadedSceneID = m_activeSceneID;

		//If we have this scene, then load the new scene and set it as active
		if (m_scenes.find(m_requestedSceneID) != m_scenes.end())
		{
			//Reset activeScene to 0
			m_activeScene = 0;

			//Need to have OpenGL context current in order to create gpu resources
			m_renderer->makeCurrent();

			m_sceneLoader->loadFromXml(m_scenes[m_requestedSceneID]);
			m_activeScene = m_sceneLoader->getScene();

			m_renderer->doneCurrent();

			//If the new scene failed to load, default back to the previous scene
			if (m_activeScene == 0)
			{
				m_activeScene = previouslyLoadedScene;
				m_activeSceneID = previouslyLoadedSceneID;
			}
			else
			{
				m_activeSceneID = m_requestedSceneID;

				//If we had a scene previously loaded, delete it
				if (previouslyLoadedScene != 0)
				{
					delete previouslyLoadedScene;
				}
			}

			m_activeScene->initialize();
		}
		else
		{
			stringstream message;
			message << "The Scene at index " << m_requestedSceneID << " does not exist.";
			m_requestedSceneID = m_activeSceneID;

			throw BengineException(message.str());
		}
	}

	void Game::shutdown()
	{
		cout << "Shutting Down..." << endl;
		m_updater.stop();
		delete m_sceneLoader;
		if (m_isOwnRenderer && m_renderer != 0)
		{
			delete m_renderer;
		}
		if (m_activeScene != 0)
		{
			delete m_activeScene;
		}

		GAME = 0;
	}

	Game::~Game() 
	{
		this->shutdown();
	}
}