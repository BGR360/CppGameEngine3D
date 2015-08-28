#include "GameSelectDialog.h"
#include "GameSelectDialog_ui.h"

#include <qt/QtCore/qdebug.h>
#include <qt/QtCore/qdir.h>
#include <qt/QtCore/qfile.h>
#include <qt/QtWidgets/qmessagebox.h>
#include <qt/QtCore/qsettings.h>
#include <qt/QtCore/qstringlistmodel.h>
#include <qt/QtCore/qxmlstream.h>
#include <qt/QtWidgets/qfiledialog.h>

extern QString DEFAULT_GAME_FILE_CONTENTS(const QString&, const QString&);
extern QString DEFAULT_SCENE_FILE_CONTENTS(const QString&);

NewGameDialog::NewGameDialog(QWidget* parent)
	: QDialog(parent),
	m_ui(new Ui::NewGameDialog)
{
	m_ui->setupUi(this);
	setWindowTitle("Create New Game");

	connectSlots();

	QSettings* settings = new QSettings;
	QString gamesDir = settings->value("gamesDirectory").toString();
	delete settings;

	m_ui->locationLineEdit->setText(gamesDir);
}

Ui::NewGameDialog* NewGameDialog::ui()
{
	return m_ui;
}

NewGameInfo NewGameDialog::getNewGame(QWidget* parent, const QString& startingDir)
{
	NewGameInfo info;

	NewGameDialog* newGameDialog = new NewGameDialog(parent);

	if (startingDir != "")
	{
		newGameDialog->ui()->locationLineEdit->setText(startingDir);
	}
	else
	{
		newGameDialog->ui()->locationLineEdit->setText(QSettings().value("gamesDirectory").toString());
	}

	int result = newGameDialog->exec();

	if (result == DialogCode::Rejected)
	{
		info.creationAborted = true;
	}
	else
	{
		info.creationAborted = false;
	}

	info.gameName = newGameDialog->gameName();
	info.dir = newGameDialog->gameDir();
	info.defaultSceneName = DEFAULT_NAME_FOR_DEFAULT_SCENE;

	return info;
}

QString NewGameDialog::gameDir() const
{
	return m_newGameInfo.dir;
}

QString NewGameDialog::gameName() const
{
	return m_newGameInfo.gameName;
}

NewGameInfo NewGameDialog::gameInfo() const
{
	return m_newGameInfo;
}

void NewGameDialog::connectSlots()
{
	connect(m_ui->browseButton, SIGNAL(clicked()), this, SLOT(chooseDir()));
	connect(m_ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(m_ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void NewGameDialog::chooseDir()
{
	//Open a QFileDialog to choose a location for the new game
	QSettings settings;
	QString rootDir = settings.value("gamesDirectory").toString();

	QString chosenDir;

	NewGameFileDialog* fileDialog = new NewGameFileDialog(this);

	//Start the FileDialog off at the directory specified in our location LineEdit widget
	QString startingDir = m_ui->locationLineEdit->text();
	if (QDir(startingDir).exists())
	{
		fileDialog->setDirectory(startingDir);
	}
	else
	{
		fileDialog->setDirectory(QSettings().value("gamesDirectory").toString());
	}

	fileDialog->setFileMode(QFileDialog::Directory);
	fileDialog->setOption(QFileDialog::ShowDirsOnly, true);
	fileDialog->setViewMode(QFileDialog::Detail);
	fileDialog->setWindowTitle("Choose a Location");

	if (fileDialog->exec())
	{
		chosenDir = fileDialog->selectedFiles()[0];
		m_ui->locationLineEdit->setText(chosenDir);
	}
	else
	{
		chosenDir = "";
	}
}

void NewGameDialog::accept()
{
	//Update our variables and then call done(true)
	m_newGameInfo.gameName = m_ui->nameLineEdit->text();
	m_newGameInfo.dir = m_ui->locationLineEdit->text();

	if (m_newGameInfo.gameName == "")
	{
		m_newGameInfo.gameName = DEFAULT_NEW_GAME_NAME;
	}
	if (m_newGameInfo.dir == "")
	{
		m_newGameInfo.dir = DEFAULT_NEW_GAME_DIR;
	}

	done(DialogCode::Accepted);
}

NewGameDialog::~NewGameDialog()
{
	delete m_ui;
}


//--------------- GameSelectDialog ---------------------

GameSelectDialog::GameSelectDialog(QWidget* parent)
	: QDialog(parent),
	m_ui(new Ui::GameSelectDialog),
	m_nameList(0)
{
	m_ui->setupUi(this);
	setWindowTitle("Select a Game");
	connectSlots();
	loadSettings();
	setupRecentGamesView();
}

GameInfo GameSelectDialog::getGame(QWidget* parent)
{
	GameSelectDialog* dialog = new GameSelectDialog(parent);
	dialog->exec();
	GameInfo ret = dialog->selectedGame();
	delete dialog;
	return ret;
}

void GameSelectDialog::setGamesDirectory(const QString& dir)
{
	QSettings settings;
	settings.setValue("gamesDirectory", dir);
}

Ui::GameSelectDialog* GameSelectDialog::ui()
{
	return m_ui;
}

GameInfo GameSelectDialog::selectedGame() const
{
	return m_selectedGame;
}

void GameSelectDialog::connectSlots()
{
	connect(m_ui->newButton, SIGNAL(clicked()), this, SLOT(newGame()));
	connect(m_ui->openButton, SIGNAL(clicked()), this, SLOT(openGame()));
	connect(m_ui->recentGamesWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(useRecentGame(int)));
}

void GameSelectDialog::loadSettings()
{
	QSettings* settings = new QSettings;
	if (!settings->contains("gamesDirectory"))
	{
		settings->setValue("gamesDirectory", DEFAULT_GAMES_DIR);
	}
	delete settings;

	this->loadRecentGames();
}

void GameSelectDialog::loadRecentGames()
{
	QSettings settings;

	qDebug() << "Loading recentGames";

	m_recentGames.clear();

	//Resize the size of "recentGames" if it differs from NUM_RECENT_GAMES
	unsigned char numSavedRecentGames = settings.value("recentGames/size").toInt();

	if (numSavedRecentGames < NUM_RECENT_GAMES)
	{
		qDebug() << "Resizing recentGames";

		settings.beginWriteArray(RECENT_GAMES_SETTINGS_KEY);
		unsigned char i;
		for (i = numSavedRecentGames; i < NUM_RECENT_GAMES; i++)
		{
			settings.setArrayIndex(i);
			settings.setValue(GAME_NAME_SETTINGS_KEY, "");
			settings.setValue(GAME_FILE_PATH_SETTINGS_KEY, "");
		}
		settings.endArray();
	}

	//Now read from the list of recent games
	qDebug() << "Reading recentGames";
	settings.beginReadArray(RECENT_GAMES_SETTINGS_KEY);
	unsigned char i;
	for (i = 0; i < NUM_RECENT_GAMES; i++)
	{
		settings.setArrayIndex(i);
		QString name = settings.value(GAME_NAME_SETTINGS_KEY).toString();
		QString filePath = settings.value(GAME_FILE_PATH_SETTINGS_KEY).toString();

		if (filePath == "")
		{
			break;
		}
		else
		{
			GameInfo info;
			info.name = name;
			info.filePath = filePath;
			m_recentGames.push_back(info);
		}
	}
	settings.endArray();

	qDebug() << "Size of m_recentGames: " << m_recentGames.size();
}

void GameSelectDialog::setupRecentGamesView()
{
	m_nameModel = new QStringListModel(this);

	if (m_nameList != 0)
	{
		delete m_nameList;
		m_nameList = 0;
	}

	m_ui->recentGamesWidget->setRowCount(m_recentGames.size());
	m_ui->recentGamesWidget->setColumnCount(2);

	for (int i = 0; i < m_recentGames.size(); i++)
	{
		GameInfo& current = m_recentGames[i];
		m_ui->recentGamesWidget->setItem(i, 0,
			new QTableWidgetItem(current.name));
		m_ui->recentGamesWidget->setItem(i, 1,
			new QTableWidgetItem(current.filePath));
	}
}

void GameSelectDialog::saveRecentGames()
{
	QSettings settings;

	qDebug() << "Saving recent games";
	qDebug() << "Size of m_recentgames: " << m_recentGames.size();

	settings.beginWriteArray(RECENT_GAMES_SETTINGS_KEY);

	unsigned char i;
	for (i = 0; i < NUM_RECENT_GAMES; i++)
	{
		settings.setArrayIndex(i);

		GameInfo empty;

		if (m_recentGames.size() > i && m_recentGames[i] != empty)
		{
			settings.setValue(GAME_NAME_SETTINGS_KEY, m_recentGames[i].name);
			settings.setValue(GAME_FILE_PATH_SETTINGS_KEY, m_recentGames[i].filePath);
		}
		else
		{
			settings.setValue(GAME_NAME_SETTINGS_KEY, "");
			settings.setValue(GAME_FILE_PATH_SETTINGS_KEY, "");
		}
	}
	settings.endArray();
}

QString GameSelectDialog::getNameFromGameFile(const QString& filePath)
{
	QXmlStreamReader xml;
	QFile file(filePath);

	QString ret = "";

	if (!file.open(QFile::ReadOnly))
	{
		QMessageBox::warning(this,
			tr("Could not open file"),
			QString(tr("Unable to open file \n")) + filePath,
			QMessageBox::StandardButton::Ok);

		//Return to proper spot
	}
	else
	{
		xml.setDevice(&file);

		while (!(xml.name() == "game" && xml.isStartElement()))
		{
			xml.readNext();
		}

		if (xml.attributes().hasAttribute("name"))
		{
			ret = xml.attributes().value("name").toString();
		}
	}

	return ret;
}

void GameSelectDialog::writeDefaultGameFile(QFile* gameFile, const QString& gameName, const QString& sceneName)
{
	gameFile->resize(0);
	QByteArray data = DEFAULT_GAME_FILE_CONTENTS(gameName, sceneName).toUtf8();
	gameFile->write(data);
}

void GameSelectDialog::writeDefaultSceneFile(QFile* sceneFile, const QString& sceneName)
{
	sceneFile->resize(0);
	QByteArray data = DEFAULT_SCENE_FILE_CONTENTS(sceneName).toUtf8();
	sceneFile->write(data);
}


void GameSelectDialog::done(int r)
{
	//Save needed settings
	this->saveRecentGames();

	QDialog::done(r);
}

void GameSelectDialog::selectGame(const QString& name, const QString& filePath)
{
	GameInfo info;
	info.name = name;
	info.filePath = filePath;
	this->selectGame(info);
}

void GameSelectDialog::selectGame(const GameInfo& gameInfo)
{
	qDebug() << "Game Selected: " << gameInfo.name;

	m_selectedGame = gameInfo;

	int indexOfGame = m_recentGames.indexOf(gameInfo);
	if (indexOfGame == -1)
	{
		//We haven't played this game recently, so add selected game to the list of recent games
		m_recentGames.push_front(gameInfo);

		while (m_recentGames.size() > NUM_RECENT_GAMES)
		{
			m_recentGames.pop_back();
		}
	}
	else if (indexOfGame < m_recentGames.size())
	{
		//We have played this game recently, so make it the most recently played game
		GameInfo temp = m_recentGames.takeAt(indexOfGame);
		m_recentGames.push_front(temp);
	}

	accept();
}

void GameSelectDialog::newGame()
{
	qDebug() << "Create New Game";

	//NewGameDialog
	NewGameInfo gameInfo = NewGameDialog::getNewGame(this);

	if (!gameInfo.creationAborted)
	{
		//Create the .xml files
		qDebug() << "Creating Game named '" << gameInfo.gameName << "' in directory: " << gameInfo.dir;

		QString gameFilePath = gameInfo.dir + QString("/") + gameInfo.gameName + QString(".xml");
		QString sceneFilePath = gameInfo.dir + QString("/scenes/") + gameInfo.defaultSceneName + QString(".xml");

		//Keep prompting for a directory until a valid one is given
		QDir dir(gameInfo.dir);
		while (!dir.exists())
		{
			//The directory the user picked (or typed) does not exist
			QMessageBox::warning(this,
				tr("Invalid Directory"),
				tr("The specified folder does not exist. Please select a different folder."),
				QMessageBox::StandardButton::Ok,
				QMessageBox::StandardButton::Ok);

			gameInfo = NewGameDialog::getNewGame(this);
			dir = QDir(gameInfo.dir);
		}

		//Create a new directory for the game's Scene files
		QDir sceneDir(dir.absolutePath() + QString("/scenes"));
		if (!sceneDir.exists())
		{
			if (!dir.mkdir("scenes"))
			{
				qWarning("Cannot create new directory.");
			}
		}
		else
		{
			//scenes directory already exists, check to see if there is already a game here
			qDebug() << "Found Files:";

			QFileInfoList files = dir.entryInfoList(QDir::Filter::Files);
			QFileInfoList::iterator i = files.begin();
			bool existsGameFile = false;
			for (i; i != files.end(); i++)
			{
				qDebug() << i->baseName() + QString('.') + i->suffix();
				if (i->suffix() == "xml" || i->suffix() == "bgm")
				{
					qDebug() << QString("Scanning ") + i->baseName() + QString('.') + i->suffix();
					//Check the contents to see if it's a real game file
					QXmlStreamReader xml;
					QFile file(i->absolutePath() + QString('/') + i->baseName() + QString('.') + i->suffix());
					qDebug() << i->absolutePath();

					if (file.open(QFile::ReadOnly))
					{
						xml.setDevice(&file);
						qDebug() << "Name: " << xml.name() << " isStart: " << xml.isStartElement();
						while (!(xml.name() == "game" && xml.isStartElement()))
						{
							xml.readNext();
							qDebug() << xml.name();
						}

						if (xml.name() == "game" && xml.isStartElement())
						{
							if (xml.attributes().hasAttribute("name") && xml.attributes().hasAttribute("version"))
							{
								existsGameFile = true;
							}
						}
					}
					else
					{
						qDebug() << "Could not open the exising game file.";
					}
				}
			}

			if (existsGameFile)
			{
				//There is already a game file here
				int response = QMessageBox::question(this,
					tr("Warning"),
					tr("A Game already exists in this folder. Do you want to overwrite it? This cannot be undone."),
					QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::Cancel, QMessageBox::StandardButton::Cancel);

				switch (response)
				{
				case QMessageBox::Yes:
					break;
				case QMessageBox::Cancel:
					this->newGame();
					return;
				default:
					this->newGame();
					return;
				}
			}
		}


		QFile gameFile(gameFilePath);
		if (!gameFile.open(QFile::WriteOnly))
		{
			qWarning("Could not open newly created Game file.");
		}
		else
		{
			//Write the new Game file
			this->writeDefaultGameFile(&gameFile, gameInfo.gameName, sceneFilePath);
			gameFile.close();
		}

		QFile sceneFile(sceneFilePath);
		if (!sceneFile.open(QFile::WriteOnly))
		{
			qWarning("Could not open newly created Scene file.");
		}
		else
		{
			//Write the new Scene file
			this->writeDefaultSceneFile(&sceneFile, gameInfo.defaultSceneName);
			sceneFile.close();
		}

		selectGame(gameInfo.gameName, gameFilePath);
	}
}

void GameSelectDialog::openGame()
{
	qDebug() << "Open Existing Game";

	QSettings settings;
	QString rootDir = settings.value("gamesDirectory").toString();

	QString filePath = QFileDialog::getOpenFileName(this,
		tr("Choose Existing Game File"), rootDir, tr("Game Files (*.xml)"));

	if (filePath != "")
	{
		selectGame(this->getNameFromGameFile(filePath), filePath);
	}
}

void GameSelectDialog::useRecentGame(int index)
{
	if (index < 0)
	{
		QMessageBox::warning(this, "Error", "Index provided for choosing Recent Game is less than 0.", QMessageBox::StandardButton::Ok);
	}
	else if (index > NUM_RECENT_GAMES)
	{
		QMessageBox::warning(this, "Error", "Index provided for choosing Recent Game exceeds the maximum number of Recent Games.", QMessageBox::StandardButton::Ok);
	}
	else
	{
		selectGame(m_recentGames[index]);
	}
}

GameSelectDialog::~GameSelectDialog()
{
	delete m_ui;
	if (m_nameList != 0)
	{
		delete m_nameList;
	}
}