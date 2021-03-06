#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Event/ApplicationEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("({0}):{1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	unsigned int WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}
	unsigned int WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}
	void WindowsWindow::SetVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enable;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title; m_Data.Width = props.Width; m_Data.Height = props.Height;

		HZ_CORE_DEBUG("Creating window( {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *((WindowData*)glfwGetWindowUserPointer(window));
			data.Width = width; data.Height = height;
			
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
		{
			WindowData& data = *((WindowData*)glfwGetWindowUserPointer(window));

			WindowClosedEvent event;
			data.EventCallback(event);
		});
		
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *((WindowData*)glfwGetWindowUserPointer(window));
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event1(key, 0);
					data.EventCallback(event1);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event2(key);
					data.EventCallback(event2);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event3(key, 1);
					data.EventCallback(event3);
					break;
				}
				default:
					break;
			}

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *((WindowData*)glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				default:
					break;
			}

		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *((WindowData*)glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(xOffset, yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window,[](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *((WindowData*)glfwGetWindowUserPointer(window));

			MouseMovedEvent event(xPos, yPos);
			data.EventCallback(event);
		});

		SetVSync(true);
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}