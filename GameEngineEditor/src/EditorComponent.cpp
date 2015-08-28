#include "EditorComponent.h"

#include <qt/QtCore/qdebug.h>

#include <core/Game.h>
#include <input/InputManager.h>
#include <rendering/Camera.h>

#define CAMERA_START_POS Vector3(10, 5, 10)
#define CAMERA_START_TARGET Vector3(0, 0, 0)
#define CAMERA_ROTATE_SPEED 85.0f
#define CAMERA_MOVE_SPEED 5.3f
#define CAMERA_ZOOM_SPEED 0.15f
#define CAMERA_TO_FOCUS_THRESHOLD 0.000000001f

void EditorComponent::start()
{
	m_camera = new Camera;

	m_camera->setPosition(CAMERA_START_POS);
	m_camera->setTarget(CAMERA_START_TARGET);

	Scene* scene = getGame()->getActiveScene();
	scene->setActiveCamera(m_camera);

	m_focus = Vector3(0, 0, 0);
	isMovingCamera = false;
	isResuming = false;
}

void EditorComponent::pause()
{

}

void EditorComponent::resume()
{
	isResuming = true;
}

void EditorComponent::update()
{
	InputManager* input = getGame()->getInput();
	GameClock* time = getGame()->getClock();

	if (input->isMouseInWindow() || isMovingCamera)
	{
		if (isResuming)
		{
			input->reset();
		}

		if (input->isButtonDown(Input::Mouse::LEFT))
		{
			isMovingCamera = true;

			Vector2 delta = input->getMouseDelta();

			Vector3 relativePos = m_camera->getPosition() - m_focus;
			Vector3 right = Vector3::cross(m_camera->getUp(), relativePos);

			Matrix3x3 rotateY = Matrix3x3::rotate(-delta.x * CAMERA_ROTATE_SPEED, Vector3(0, 1, 0));
			Matrix3x3 rotateX = Matrix3x3::rotate(-delta.y * CAMERA_ROTATE_SPEED, right);
			Matrix3x3 rotate = rotateY * rotateX;

			Vector3 rotatedPos = rotate * relativePos;
			m_camera->setPosition(m_focus + rotatedPos);
		}
		else
		{
			isMovingCamera = false;
		}

		if (input->isButtonDown(Input::Mouse::MIDDLE))
		{
			Vector2 delta = input->getMouseDelta();
			Vector3 relativePos = m_camera->getPosition() - m_focus;
			Vector3 right = Vector3::cross(m_camera->getUp(), relativePos);
			Vector3 up = Vector3::cross(relativePos, right);

			Vector3 deltaPos = right.normalized() * -delta.x * CAMERA_MOVE_SPEED;
			deltaPos += up.normalized() * delta.y * CAMERA_MOVE_SPEED;
			m_focus += deltaPos;
			m_camera->setPosition(m_camera->getPosition() + deltaPos);
		}

		if (!isMovingCamera)
		{
			float wheelDelta = input->getMouseWheelDelta();

			//qDebug() << "wheelDelta: " << wheelDelta;

			Vector3 forward = Vector3::normalize(m_camera->getForward());
			Vector3 toFocus = m_focus - m_camera->getPosition();
			Vector3 deltaCamera = forward * wheelDelta * CAMERA_ZOOM_SPEED;

			float distanceToFocus = toFocus.magnitude();
			float deltaCameraDistance = deltaCamera.magnitude();

			if (Vector3::dot(toFocus, deltaCamera) < 0 || distanceToFocus > deltaCameraDistance)
			{
				//Move the camera normally
				m_camera->setPosition(m_camera->getPosition() + deltaCamera);
			}
			else
			{
				//Move the camera half the distance to the target (if not too close)
				if (distanceToFocus < CAMERA_TO_FOCUS_THRESHOLD)
				{
					float halfway = distanceToFocus / 2;
					Vector3 moveCamera = halfway * forward;
					m_camera->setPosition(m_camera->getPosition() + moveCamera);
				}
			}
		}

		m_camera->setTarget(m_focus);
	}

	isResuming = false;
}

void EditorComponent::setFocus(const Vector3& focus)
{
	Vector3 toCamera = m_camera->getPosition() - m_focus;
	m_focus = focus;
	m_camera->setPosition(m_focus + toCamera);
}