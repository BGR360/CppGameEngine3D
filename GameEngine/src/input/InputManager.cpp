#include "InputManager.h"

#include <Windows.h>
#include <iostream>

#include <qt/QtGui/qcursor.h>
#include <qt/QtGui/QMouseEvent>
#include <qt/QtWidgets/qwidget.h>

#include <exceptions/InvalidOperationException.h>

using std::cout;
using std::endl;

using Exceptions::InvalidOperationException;

namespace Input
{
	InputManager::InputManager() : m_widget(0)
	{
		this->reset();
	}

	void InputManager::attachWidget(QWidget* widget)
	{
		m_widget = widget;
	}

	void InputManager::reset()
	{
		for (uint i = 0; i < (uint)Key::NUM_KEYS; i++)
		{
			m_keysDown[i] = 0;
			m_keysPressed[i] = 0;
		}
		for (uint i = 0; i < (uint)Mouse::NUM_BUTTONS; i++)
		{
			m_buttonsDown[i] = 0;
			m_buttonsPressed[i] = 0;
		}
		m_mouseWheelDelta = 0.0f;
		m_mouseWheelDeltaLastFrame = 0.0f;
		m_mousePos = Vector2();
		m_prevMousePos = Vector2();
	}

	void InputManager::update()
	{
		//Update mousePosition and prevMousePosition
		m_prevMousePos = m_mousePos;
		m_mousePos = calcMousePos();

		m_mouseWheelDeltaLastFrame = m_mouseWheelDelta;
		m_mouseWheelDelta = 0.0f;

		//Update all the keys
		for (uint i = 0; i < (uint)Key::NUM_KEYS; i++)
		{
			bool keyDown = checkKeyDown((Key::KeyType)i);
			if (keyDown)
			{
				if (!m_keysPressed[i])
				{
					m_keysPressed[i] = 1;
				}
				else
				{
					m_keysPressed[i] = 0;
				}

				m_keysDown[i] = 1;
			}
			else
			{
				m_keysDown[i] = 0;
			}
		}

		for (uint i = 0; i < (uint)Mouse::NUM_BUTTONS; i++)
		{
			bool buttonDown = checkButtonDown((Mouse::ButtonType)i);
			if (buttonDown)
			{
				if (!m_buttonsPressed[i])
				{
					m_buttonsPressed[i] = 1;
				}
				else
				{
					m_buttonsPressed[i] = 0;
				}

				m_buttonsDown[i] = 1;
			}
			else
			{
				m_buttonsDown[i] = 0;
			}
		}
	}

	bool InputManager::isKeyDown(Key::KeyType key) const
	{
		return m_keysDown[key];
	}

	bool InputManager::isKeyPressed(Key::KeyType key) const
	{
		return m_keysPressed[key];
	}

	bool InputManager::isButtonDown(Mouse::ButtonType button) const
	{
		return m_buttonsDown[button];
	}

	bool InputManager::isButtonPressed(Mouse::ButtonType button) const
	{
		return m_buttonsPressed[button];
	}

	bool InputManager::isMouseInWindow() const
	{
		if (m_widget == 0)
		{
			throw InvalidOperationException("isMouseInWindow", "InputManager", "It has not been given a QWidget to work with");
		}
		else
		{
			QPoint widgetPos = m_widget->mapFromGlobal(QCursor::pos());

			return m_widget->visibleRegion().contains(widgetPos)
				&& m_widget->isActiveWindow()
				&& widgetPos.x() < m_widget->width()
				&& widgetPos.x() > 0
				&& widgetPos.y() < m_widget->height()
				&& widgetPos.y() > 0;
		}
	}

	Vector2 InputManager::getMousePos() const
	{
		return m_mousePos;
	}

	Vector2 InputManager::getMouseDelta() const
	{
		return m_mousePos - m_prevMousePos;
	}

	float InputManager::getMouseWheelDelta() const
	{
		return m_mouseWheelDeltaLastFrame;
	}

	Vector2 InputManager::calcMousePos()
	{
		if (m_widget == 0)
		{
			throw InvalidOperationException("calcMousePosition", "InputManager", "It has not been given a QWidget to work with");
		}
		else
		{
			//Use QCursor::pos() to calculate mouse position
			QPoint widgetPos = m_widget->mapFromGlobal(QCursor::pos());

			float x = (float)(widgetPos.x()) / (m_widget->width() / 2) - 1.0f;
			float y = (float)(widgetPos.y()) / (m_widget->height() / 2) - 1.0f;

			return Vector2(x, y);
		}
		return Vector2();
	}

	bool InputManager::checkKeyDown(Key::KeyType key) const
	{
		using namespace Key;

		switch (key)
		{
		case ESCAPE:
			return GetAsyncKeyState(VK_ESCAPE);
		case F1:
			return GetAsyncKeyState(VK_F1);
		case F2:
			return GetAsyncKeyState(VK_F2);
		case F3:
			return GetAsyncKeyState(VK_F3);
		case F4:
			return GetAsyncKeyState(VK_F4);
		case F5:
			return GetAsyncKeyState(VK_F5);
		case F6:
			return GetAsyncKeyState(VK_F6);
		case F7:
			return GetAsyncKeyState(VK_F7);
		case F8:
			return GetAsyncKeyState(VK_F8);
		case F9:
			return GetAsyncKeyState(VK_F9);
		case F10:
			return GetAsyncKeyState(VK_F10);
		case F11:
			return GetAsyncKeyState(VK_F11);
		case F12:
			return GetAsyncKeyState(VK_F12);
		case INSERT:
			return GetAsyncKeyState(VK_INSERT);
		case SCROLL_LOCK:
			return GetAsyncKeyState(VK_SCROLL);
		case DEL:
			return GetAsyncKeyState(VK_DELETE);
		case HOME:
			return GetAsyncKeyState(VK_HOME);
		case END:
			return GetAsyncKeyState(VK_END);
		case PRINT_SCREEN:
			return GetAsyncKeyState(VK_SNAPSHOT);
		case PAGE_UP:
			return GetAsyncKeyState(VK_PRIOR);
		case PAGE_DOWN:
			return GetAsyncKeyState(VK_NEXT);
		case BREAK:
			return GetAsyncKeyState(VK_CANCEL);
		case PAUSE:
			return GetAsyncKeyState(VK_PAUSE);
		case ONE:
			return GetAsyncKeyState('1');
		case TWO:
			return GetAsyncKeyState('2');
		case THREE:
			return GetAsyncKeyState('3');
		case FOUR:
			return GetAsyncKeyState('4');
		case FIVE:
			return GetAsyncKeyState('5');
		case SIX:
			return GetAsyncKeyState('6');
		case SEVEN:
			return GetAsyncKeyState('7');
		case EIGHT:
			return GetAsyncKeyState('8');
		case NINE:
			return GetAsyncKeyState('9');
		case ZERO:
			return GetAsyncKeyState('0');
		case HYPHEN:
			return GetAsyncKeyState(VK_SUBTRACT);
		case BACKSPACE:
			return GetAsyncKeyState(VK_BACK);
		case TAB:
			return GetAsyncKeyState(VK_TAB);
		case Q:
			return GetAsyncKeyState('Q');
		case W:
			return GetAsyncKeyState('W');
		case E:
			return GetAsyncKeyState('E');
		case R:
			return GetAsyncKeyState('R');
		case T:
			return GetAsyncKeyState('T');
		case Y:
			return GetAsyncKeyState('Y');
		case U:
			return GetAsyncKeyState('U');
		case I:
			return GetAsyncKeyState('I');
		case O:
			return GetAsyncKeyState('O');
		case P:
			return GetAsyncKeyState('P');
		case LEFT_BRACKET:
			return GetAsyncKeyState('[');
		case RIGHT_BRACKET:
			return GetAsyncKeyState(']');
		case BACKSLASH:
			return GetAsyncKeyState('\\');
		case CAPS_LOCK:
			return GetAsyncKeyState(VK_CAPITAL);
		case A:
			return GetAsyncKeyState('A');
		case S:
			return GetAsyncKeyState('S');
		case D:
			return GetAsyncKeyState('D');
		case F:
			return GetAsyncKeyState('F');
		case G:
			return GetAsyncKeyState('G');
		case H:
			return GetAsyncKeyState('H');
		case J:
			return GetAsyncKeyState('J');
		case K:
			return GetAsyncKeyState('K');
		case L:
			return GetAsyncKeyState('L');
		case SEMICOLON:
			return GetAsyncKeyState(';');
		case APOSTROPHE:
			return GetAsyncKeyState('\'');
		case ENTER:
			return GetAsyncKeyState(VK_RETURN);
		case LEFT_SHIFT:
			return GetAsyncKeyState(VK_LSHIFT);
		case Z:
			return GetAsyncKeyState('Z');
		case X:
			return GetAsyncKeyState('X');
		case C:
			return GetAsyncKeyState('C');
		case V:
			return GetAsyncKeyState('V');
		case B:
			return GetAsyncKeyState('B');
		case N:
			return GetAsyncKeyState('N');
		case M:
			return GetAsyncKeyState('M');
		case COMMA:
			return GetAsyncKeyState(',');
		case PERIOD:
			return GetAsyncKeyState('.');
		case FORWARD_SLASH:
			return GetAsyncKeyState('/');
		case LEFT_CONTROL:
			return GetAsyncKeyState(VK_LCONTROL);
		case WINDOWS:
			return GetAsyncKeyState(VK_LWIN) || GetAsyncKeyState(VK_RWIN);
		case LEFT_ALT:
			return GetAsyncKeyState(VK_LMENU);
		case SPACE:
			return GetAsyncKeyState(VK_SPACE);
		case RIGHT_ALT:
			return GetAsyncKeyState(VK_RMENU);
		case RIGHT_CONTROL:
			return GetAsyncKeyState(VK_RCONTROL);
		case LEFT:
			return GetAsyncKeyState(VK_LEFT);
		case RIGHT:
			return GetAsyncKeyState(VK_RIGHT);
		case UP:
			return GetAsyncKeyState(VK_UP);
		case DOWN:
			return GetAsyncKeyState(VK_DOWN);
		case NUM_LOCK:
			return GetAsyncKeyState(VK_NUMLOCK);
		case NUMPAD_FORWARD_SLASH:
			return GetAsyncKeyState(VK_DIVIDE);
		case NUMPAD_ASTERISK:
			return GetAsyncKeyState(VK_MULTIPLY);
		case NUMPAD_HYPHEN:
			return GetAsyncKeyState(VK_SUBTRACT);
		case NUMPAD_PLUS:
			return GetAsyncKeyState(VK_ADD);
		case NUMPAD_ENTER:
			return GetAsyncKeyState(VK_RETURN);
		case NUMPAD_PERIOD:
			return GetAsyncKeyState(VK_SEPARATOR);
		case NUMPAD_ZERO:
			return GetAsyncKeyState(VK_NUMPAD0);
		case NUMPAD_ONE:
			return GetAsyncKeyState(VK_NUMPAD1);
		case NUMPAD_TWO:
			return GetAsyncKeyState(VK_NUMPAD2);
		case NUMPAD_THREE:
			return GetAsyncKeyState(VK_NUMPAD3);
		case NUMPAD_FOUR:
			return GetAsyncKeyState(VK_NUMPAD4);
		case NUMPAD_FIVE:
			return GetAsyncKeyState(VK_NUMPAD5);
		case NUMPAD_SIX:
			return GetAsyncKeyState(VK_NUMPAD6);
		case NUMPAD_SEVEN:
			return GetAsyncKeyState(VK_NUMPAD7);
		case NUMPAD_EIGHT:
			return GetAsyncKeyState(VK_NUMPAD8);
		case NUMPAD_NINE:
			return GetAsyncKeyState(VK_NUMPAD9);
		default:
			return false;
		}
		return false;
	}

	bool InputManager::checkButtonDown(Mouse::ButtonType button) const
	{
		using namespace Mouse;

		switch (button)
		{
		case LEFT:
			return GetAsyncKeyState(VK_LBUTTON);
		case RIGHT:
			return GetAsyncKeyState(VK_RBUTTON);
		case MIDDLE:
			return GetAsyncKeyState(VK_MBUTTON);
		default:
			return false;
		}
		return false;
	}

	void InputManager::setMousePos(const Vector2& pos)
	{
		this->setMousePos(pos.x, pos.y);
	}

	void InputManager::setMousePos(float x, float y)
	{
		if (m_widget != 0)
		{
			int newX = (int)(((x + 1.0f) / 2.0f) * m_widget->width());
			int newY = (int)(((y + 1.0f) / 2.0f) * m_widget->height());

			QCursor::setPos(m_widget->mapToGlobal(QPoint(newX, newY)));

			m_prevMousePos = Vector2(x, y);
			m_mousePos = Vector2(x, y);
		}
		else
		{
			throw InvalidOperationException("setMousePos", "InputManager", "It has not been given a QWidget to work with");
		}
	}

	void InputManager::showMouse()
	{
		m_widget->setCursor(QCursor(Qt::ArrowCursor));
	}

	void InputManager::hideMouse()
	{
		m_widget->setCursor(QCursor(Qt::BlankCursor));
	}

	void InputManager::wheelEvent(QWheelEvent* e)
	{
		m_mouseWheelDelta = (float)((e->angleDelta() / 8).y());
	}

	InputManager::~InputManager()
	{

	}
}