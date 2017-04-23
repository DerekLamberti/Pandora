#pragma once

#include <SDL.h>

namespace Pandora
{
	class InputTracker
	{
	public:
		enum MouseButton
		{
			Left = 0,
			Right = 1,
			Middle = 2
		};

		void SetMouseKeyDown(MouseButton keyIdx)
		{
			m_MouseKeys[keyIdx] = true;
		}

		void ResetMouseKeys()
		{
			m_MouseKeys[0] = m_MouseKeys[1] = m_MouseKeys[2] = false;
		}

		bool IsLeftMouseDown() const
		{
			return m_MouseKeys[MouseButton::Left] || (m_MouseMask & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
		}

		bool IsMiddleMouseDown() const
		{
			return m_MouseKeys[MouseButton::Middle] || (m_MouseMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
		}

		bool IsRightMouseDown() const 
		{
			return m_MouseKeys[MouseButton::Right] || (m_MouseMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
		}

		void UpdateMousePos()
		{
			m_MouseMask = SDL_GetMouseState(&m_MouseX, &m_MouseY);
		}

		int GetMouseX() const { return m_MouseX; }
		int GetMouseY() const { return m_MouseY; }

	private:
		bool m_MouseKeys[3];

		int m_MouseX;
		int m_MouseY;
		Uint32 m_MouseMask;
	};

} //namespace Pandora