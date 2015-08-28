#include <iostream>

#include <Testing.h>

#include <qt/QtWidgets/qapplication.h>

#include <exceptions\BengineException.h>
#include <rendering/RenderingEngine.h>

using std::cout;
using std::endl;

using Exceptions::BengineException;
using Rendering::RenderingEngine;


//Global Variables (sorry)
RenderingEngine* globalRenderer;	//Gotta use this for the RenderingEngineTests
string renderingComponentOutput;


int main(int argc, char* argv[])
{
	int errorCode = 0;

	try
	{
		QApplication application(argc, argv);

		cout << "Bengine Tests!" << endl;

#ifdef RENDERING_TESTS
		//This allows us to do testing on OpenGL related stuff
		RenderingEngine renderer;
		globalRenderer = &renderer;
		renderer.initialize();
#endif //RENDERING_TESTS

		::testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();

#ifdef RENDERING_TESTS
		errorCode = application.exec();

		//Testing if RenderingEngine worked
		string expectedOutput = "TestRenderingComponent rendered the GameObject!";
		if (renderingComponentOutput != expectedOutput)
		{
			cout << "TEST FAILED: RenderingEngine.RenderGameObject\n"
				<< "renderingComponentOutput is\n"
				<< renderingComponentOutput << "\n"
				<< "instead of\n"
				<< expectedOutput << endl;
		}
#endif //RENDERING_TESTS

		system("pause");
	}
	catch (BengineException& e)
	{
		cout << "Caught: " << e.what() << ": " << e.message() << endl;
		system("pause");
	}
	catch (exception& e)
	{
		cout << "Caught: " << e.what() << ": " << endl;
		system("pause");
	}
	
	return errorCode;
}