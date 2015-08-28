#ifndef BENGINE_INPUT_MANAGER_H
#define BENGINE_INPUT_MANAGER_H

#include <Engine.h>

#include <math/Vector2.h>
#include <util/Types.h>

//Forward declaration of QWidget class
class QWidget;
class QMouseEvent;
class QWheelEvent;
class QKeyEvent;

using Math::Vector2;

namespace Input
{
	namespace Key
	{
		enum KeyType
		{
			ESCAPE,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
			INSERT,
			SCROLL_LOCK,
			DEL,
			HOME,
			END,
			PRINT_SCREEN,
			PAGE_UP,
			PAGE_DOWN,
			BREAK,
			PAUSE,
			ONE,
			TWO,
			THREE,
			FOUR,
			FIVE,
			SIX,
			SEVEN,
			EIGHT,
			NINE,
			ZERO,
			HYPHEN,
			BACKSPACE,
			TAB, Q, W, E, R, T, Y, U, I, O, P, LEFT_BRACKET, RIGHT_BRACKET, BACKSLASH,
			CAPS_LOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER,
			LEFT_SHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, FORWARD_SLASH,
			LEFT_CONTROL, WINDOWS, LEFT_ALT,
			SPACE,
			RIGHT_ALT, RIGHT_CONTROL,
			LEFT, RIGHT, UP, DOWN,
			NUM_LOCK,
			NUMPAD_FORWARD_SLASH,
			NUMPAD_ASTERISK,
			NUMPAD_HYPHEN,
			NUMPAD_PLUS,
			NUMPAD_ENTER,
			NUMPAD_PERIOD,
			NUMPAD_ZERO,
			NUMPAD_ONE,
			NUMPAD_TWO,
			NUMPAD_THREE,
			NUMPAD_FOUR,
			NUMPAD_FIVE,
			NUMPAD_SIX,
			NUMPAD_SEVEN,
			NUMPAD_EIGHT,
			NUMPAD_NINE,

			NUM_KEYS
		};
	}

	namespace Mouse
	{
		enum ButtonType
		{
			LEFT,
			MIDDLE,
			RIGHT,

			NUM_BUTTONS
		};
	}

	class ENGINE_DLL_EXPORT_IMPORT InputManager
	{
		uchar m_keysDown[Key::NUM_KEYS];
		uchar m_keysPressed[Key::NUM_KEYS];
		uchar m_buttonsDown[Mouse::NUM_BUTTONS];
		uchar m_buttonsPressed[Mouse::NUM_BUTTONS];

		//We need a pointer to the Widget so we can translate global mouse coordinates to widget coordinates
		QWidget* m_widget;

		Vector2 m_prevMousePos;
		Vector2 m_mousePos;
		float m_mouseWheelDelta;
		float m_mouseWheelDeltaLastFrame;

	public:
		InputManager();
		virtual ~InputManager();

		void attachWidget(QWidget* widget);

		void reset();
		void update();

		bool isKeyDown(Key::KeyType key) const;
		bool isKeyPressed(Key::KeyType key) const;
		bool isButtonDown(Mouse::ButtonType button) const;
		bool isButtonPressed(Mouse::ButtonType button) const;

		bool isMouseInWindow() const;

		Vector2 getMousePos() const;
		Vector2 getMouseDelta() const;
		float getMouseWheelDelta() const;

		void setMousePos(const Vector2& pos);
		void setMousePos(float x, float y);

		void showMouse();
		void hideMouse();

		void wheelEvent(QWheelEvent* e);

	private:
		Vector2 calcMousePos();

		bool checkKeyDown(Key::KeyType key) const;
		bool checkButtonDown(Mouse::ButtonType button) const;
	};
}

#endif //BENGINE_INPUT_MANAGER_H