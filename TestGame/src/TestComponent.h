#ifndef TESTGAME_TEST_GAME_OBJECT_H
#define TESTGAME_TEST_GAME_OBJECT_H

#include <iostream>
using std::cout;
using std::endl;

#include <core/Game.h>
using namespace Core;

class TestComponent : public GameComponent
{
	Vector3 angularVelocity;
	bool buttonWasDown;

	bool paused;
	bool escHasBeenReleased;

	uint sceneNum;

	ulong frameNumber;

	const float SENSITIVITY = 1.f;
	const float ROTATE_CAMERA = 60.0f;
	const float DAMPER = 10.0f;
	const float CAMERA_SPEED = 2.0f;
	const float FOV_CHANGE = 1.0f;

public:
	TestComponent() {}
	virtual ~TestComponent() {}

	virtual void start()
	{
		getGameObject()->getTransform()->setPosition(Vector3(0, 0, -4));
		angularVelocity = Vector3(0.0f, 0.0f, 0.0f);
		buttonWasDown = false;
		frameNumber = 0;
		paused = false;
		escHasBeenReleased = true;
		sceneNum = 0;
	}

	virtual void update()
	{
		GameClock* clock = getGame()->getClock();
		InputManager* input = getGame()->getInput();

		Transform* transform = getGameObject()->getTransform();

		if (input->isKeyDown(Input::Key::ESCAPE) && escHasBeenReleased)
		{
			paused = !paused;
			escHasBeenReleased = false;
		}

		if (!escHasBeenReleased && !input->isKeyDown(Input::Key::ESCAPE))
		{
			escHasBeenReleased = true;
		}

		if (!paused)
		{
			if (frameNumber == 0)
				input->setMousePos(0.0f, 0.0f);

			input->hideMouse();

			Vector2 mouseDelta = input->getMouseDelta();
			cout << "deltaTime: " << clock->getDelta() << endl;
			cout << "transform->rotation(): x=" << transform->getRotation().x << ", y=" << transform->getRotation().y << ", z=" << transform->getRotation().z << endl;

			Camera* camera = getGame()->getActiveScene()->getActiveCamera();

			if (input->isMouseInWindow())
			{
				//Rotate the camera
				camera->rotateX(SENSITIVITY * ROTATE_CAMERA * -input->getMouseDelta().y);
				camera->rotateY(SENSITIVITY * ROTATE_CAMERA * -input->getMouseDelta().x);
			}

			if (input->isKeyDown(Input::Key::A))
			{
				Vector3 right = Vector3::normalize(camera->getRight());
				camera->setPosition(camera->getPosition() - right * CAMERA_SPEED * clock->getDelta());
			}
			if (input->isKeyDown(Input::Key::D))
			{
				Vector3 right = Vector3::normalize(camera->getRight());
				camera->setPosition(camera->getPosition() + right * CAMERA_SPEED * clock->getDelta());
			}
			if (input->isKeyDown(Input::Key::W))
			{
				Vector3 forward = Vector3::normalize(camera->getForward());
				camera->setPosition(camera->getPosition() + forward * CAMERA_SPEED * clock->getDelta());
			}
			if (input->isKeyDown(Input::Key::S))
			{
				Vector3 forward = Vector3::normalize(camera->getForward());
				camera->setPosition(camera->getPosition() - forward * CAMERA_SPEED * clock->getDelta());
			}
			if (input->isKeyDown(Input::Key::SPACE))
			{
				camera->setPosition(camera->getPosition() + Vector3(0, CAMERA_SPEED * clock->getDelta(), 0));
			}
			if (input->isKeyDown(Input::Key::LEFT_SHIFT))
			{
				camera->setPosition(camera->getPosition() - Vector3(0, CAMERA_SPEED * clock->getDelta(), 0));
			}
			if (input->isKeyDown(Input::Key::F))
			{
				camera->setFov(camera->getFov() - FOV_CHANGE * clock->getDelta());
			}
			if (input->isKeyDown(Input::Key::G))
			{
				camera->setFov(camera->getFov() + FOV_CHANGE * clock->getDelta());
			}
			if (input->isKeyDown(Input::Key::TAB))
			{
				if (sceneNum == 0)
				{
					getGame()->loadScene(1);
				}
				else
				{
					getGame()->loadScene(0);
				}
			}

			input->setMousePos(0.0f, 0.0f);
		}
		else
		{
			input->showMouse();
		}

		frameNumber++;
	}
};

#endif //TESTGAME_TEST_GAME_OBJECT_H