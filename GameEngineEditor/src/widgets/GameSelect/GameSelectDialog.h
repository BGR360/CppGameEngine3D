#ifndef BENGINE_EDITOR_GAME_SELECT_DIALOG_H
#define BENGINE_EDITOR_GAME_SELECT_DIALOG_H

#include <qt/QtCore/qvector.h>
#include <qt/QtWidgets/qwidget.h>
#include <qt/QtWidgets/qdialog.h>
#include <qt/QtWidgets/qfiledialog.h>
#include <qt/QtGui/qevent.h>

#include <qt/QtCore/qdebug.h>

#define DEFAULT_GAMES_DIR				QDir::root().currentPath()
#define DEFAULT_NEW_GAME_NAME			"Bengine Game"
#define DEFAULT_NEW_GAME_DIR			DEFAULT_GAMES_DIR + QString("/newGame")
#define DEFAULT_NAME_FOR_DEFAULT_SCENE	"Default Scene"

namespace Ui
{
	class GameSelectDialog;
	class NewGameDialog;
}

class QStringListModel;

struct NewGameInfo
{
	bool creationAborted;
	QString gameName;
	QString dir;
	QString defaultSceneName;

	NewGameInfo() :
		creationAborted(false),
		gameName(""),
		dir(""),
		defaultSceneName("")
	{}
};

struct GameInfo
{
	QString name;
	QString filePath;

	GameInfo() :
		name(""),
		filePath("")
	{}
};

inline bool operator==(const GameInfo& left, const GameInfo& right)
{
	return left.name == right.name && left.filePath == right.filePath;
}
inline bool operator!=(const GameInfo& left, const GameInfo& right)
{
	return left.name != right.name || left.filePath != right.filePath;
}

class NewGameDialog : public QDialog
{
	Q_OBJECT
public:
	NewGameDialog(QWidget* parent = 0);
	virtual ~NewGameDialog();

	static NewGameInfo getNewGame(QWidget* parent = 0, 
		const QString& startingDir = "");

	Ui::NewGameDialog* ui();

	QString gameDir() const;
	QString gameName() const;
	NewGameInfo gameInfo() const;

public slots:
	void chooseDir();
	void accept();

private:
	Ui::NewGameDialog* m_ui;

	NewGameInfo m_newGameInfo;

	void connectSlots();
	void createGameFiles();
};

class NewGameFileDialog : public QFileDialog
{
	bool hasYetCentered;
public:
	NewGameFileDialog(QWidget* parent = 0) : QFileDialog(parent), hasYetCentered(false) {}
protected:
	void resizeEvent(QResizeEvent* e)
	{
		centerOverParent();
	}

	void centerOverParent()
	{
		//Center Dialog above parent
		if (parentWidget() != 0 && !hasYetCentered)
		{
			int widthDiff = 320;
			int heightDiff = 160;
			int newPosX = parentWidget()->pos().x() - (widthDiff / 2);
			int newPosY = parentWidget()->pos().y() - (heightDiff / 2);
			move(newPosX, newPosY);

			hasYetCentered = true;
		}
	}
};


class GameSelectDialog : public QDialog
{
	Q_OBJECT
public:
	GameSelectDialog(QWidget* parent = 0);
	virtual ~GameSelectDialog();

	Ui::GameSelectDialog* ui();

	GameInfo selectedGame() const;

	void selectGame(const QString& name, const QString& filePath);
	void selectGame(const GameInfo& gameInfo);

	static GameInfo getGame(QWidget* parent = 0);
	static void setGamesDirectory(const QString& dir);

public slots:
	void done(int r);
	void newGame();
	void openGame();
	void useRecentGame(int index);

private:
	enum : unsigned char { NUM_RECENT_GAMES = 10 };
	const char* const RECENT_GAMES_SETTINGS_KEY = "recentGames";
	const char* const GAME_NAME_SETTINGS_KEY = "gameName";
	const char* const GAME_FILE_PATH_SETTINGS_KEY = "gameFilePath";

	Ui::GameSelectDialog* m_ui;

	QVector<GameInfo> m_recentGames;
	QStringListModel* m_nameModel;
	QStringList* m_nameList;

	GameInfo m_selectedGame;

	void connectSlots();
	void loadSettings();
	void loadRecentGames();
	void saveRecentGames();
	void setupRecentGamesView();
	QString getNameFromGameFile(const QString& filePath);
	void writeDefaultGameFile(QFile* gameFile, const QString& gameName, const QString& sceneName);
	void writeDefaultSceneFile(QFile* sceneFile, const QString& sceneName);
};

#endif //BENGINE_EDITOR_GAME_SELECT_DIALOG_H