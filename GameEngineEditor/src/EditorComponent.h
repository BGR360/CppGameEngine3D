#ifndef BENGINE_EDITOR_EDITOR_COMPONENT_H
#define BENGINE_EDITOR_EDITOR_COMPONENT_H

#include <core/GameObject.h>
using namespace Core;

namespace Rendering
{
	class Camera;
}
using namespace Rendering;

class EditorComponent : public GameComponent
{
public:
	EditorComponent() {}
	virtual ~EditorComponent() {}

	virtual void start();
	virtual void update();

	void setFocus(const Vector3& focus);
	void pause();
	void resume();

private:
	Camera* m_camera;
	Vector3 m_focus;
	bool isMovingCamera;
	bool isResuming;
};

#endif //BENGINE_EDITOR_EDITOR_COMPONENT_H