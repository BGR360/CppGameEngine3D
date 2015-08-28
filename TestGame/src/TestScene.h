#ifndef TESTGAME_TEST_SCENE_H
#define TESTGAME_TEST_SCENE_H

#include <iostream>

#include <core/GameObject.h>
#include <core/Scene.h>
#include <math/Matrix4x4.h>
#include <math/Vector3.h>
#include <rendering/ShaderProgram.h>

using Core::Game;
using Core::GameObject;
using Core::Scene;
using Math::Matrix4x4;
using Math::Vector3;

using std::cout;
using std::endl;

class TestScene : public Scene
{
	Vector3 color;

	float fadeDirection;

public:
	virtual void update()
	{
		Scene::update();

		cout << "TestScene Update!" << endl;

		ResourceManager* res = getResourceManager();

		ShaderProgram* shader = res->getShader("Test Shader");

		//Texture* bricks = res->getTexture("Bricks");
		Texture* cobblestone = res->getTexture("Cobblestone");
		//Texture* greenMarble = res->getTexture("Green Marble");

		color += fadeDirection * Vector3(.01, .01, .01);

		if (color.x < 0)
		{
			color = Vector3(0, 0, 0);
			fadeDirection = -fadeDirection;
		}
		if (color.x > 1)
		{
			color = Vector3(1, 1, 1);
			fadeDirection = -fadeDirection;
		}

		//shader->setUniform("color", color);
		shader->setUniform("tex", cobblestone);
		//shader->setUniform("projectionMatrix", Matrix4x4::perspective(fov, aspectRatio, zNear, zFar));
	}
};

#endif //TESTGAME_TEST_SCENE_H