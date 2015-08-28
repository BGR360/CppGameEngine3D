#ifndef BENGINE_RENDERING_ENGINE_H
#define BENGINE_RENDERING_ENGINE_H

#include <Engine.h>

#include <rendering/OpenGL.h>

#include <qt/QtCore/qsize.h>
#include <qt/QtWidgets/qopenglwidget.h>

class QWheelEvent;

namespace Core
{
	class GameObject;
	class Scene;
}
using Core::GameObject;
using Core::Scene;

namespace Rendering
{
	class ENGINE_DLL_EXPORT_IMPORT RenderingEngine : public QOpenGLWidget
	{
		Scene* m_activeScene;

	public:
		RenderingEngine(QWidget* parent = 0);
		virtual ~RenderingEngine();

		void initialize();
		void shutdown();

		float getAspectRatio() const;

		virtual void renderScene(Scene* scene);

	protected:
		void initializeGL();
		void paintEvent();
		void paintGL();

		void wheelEvent(QWheelEvent* e);

		void renderGameObject(GameObject* gameObject);
		void clearBuffers();
	};
}

#endif //BENGINE_RENDERING_ENGINE_H