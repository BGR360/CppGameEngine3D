#include <Testing.h>

#include <string>

#include <core/GameObject.h>
#include <core/Scene.h>
#include <core/component/RenderingComponent.h>
#include <rendering/RenderingEngine.h>

using std::string;

using Rendering::RenderingEngine;
using Core::GameObject;
using Core::Scene;
using Core::Component::RenderingComponent;


extern string renderingComponentOutput;

#ifdef RENDERING_TESTS

extern RenderingEngine* globalRenderer;

TEST(RenderingEngine, RenderGameObject)
{
	RenderingEngine* renderer = globalRenderer;

	class TestRenderingComponent : public RenderingComponent
	{
	public:
		virtual void render()
		{
			renderingComponentOutput = "TestRenderingComponent rendered the GameObject!";
		}
	};
}

#endif //RENDERING_TESTS