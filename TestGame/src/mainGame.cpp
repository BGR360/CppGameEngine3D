#include <iostream>
using std::cout;
using std::endl;

#include <qt/QtWidgets/qapplication.h>

#include <core/Game.h>
#include <exceptions/BengineException.h>

using Core::Game;
using Exceptions::BengineException;

#include "TestRenderingEngine.h"
#include "TestScene.h"
#include "TestSceneLoader.h"

//TODO: remove dependency on Qt5Cored.lib (or all dependency on Qt libs)

int main(int argc, char* argv[])
{
	int errorCode = 0;

	try
	{
		QApplication application(argc, argv);

		//Create and run our test game
		Game testGame("./res/game/testGame.xml");
		testGame.setName("Test Game");

		testGame.setSceneLoader(new TestSceneLoader);

		testGame.run();

		//Run Qt Application
		errorCode = application.exec();
	}
	catch (BengineException& e)
	{
		cout << "Caught: " << e.what() << ": " << e.message() << endl;
		system("pause");
	}
	catch (exception& e)
	{
		cout << "Caught: " << e.what() << endl;
		system("pause");
	}
	catch (...)
	{
		cout << "Caught: Unexpected exception." << endl;
	}

	return errorCode;
}