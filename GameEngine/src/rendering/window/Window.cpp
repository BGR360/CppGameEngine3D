#include "Window.h"

namespace Rendering
{
	Window::Window()
		: m_name("Window"), m_width(800), m_height(600)
	{}

	Window::Window(string name, int width, int height)
		: m_name(name), m_width(width), m_height(height)
	{}

	void Window::setName(string name)
	{
		m_name = name;
	}

	void Window::setWidth(int width)
	{
		m_width = width;
	}

	void Window::setHeight(int height)
	{
		m_height = height;
	}

	string Window::getName() const
	{
		return m_name;
	}

	int Window::getWidth() const
	{
		return m_width;
	}

	int Window::getHeight() const
	{
		return m_height;
	}

	Window::~Window()
	{}
}