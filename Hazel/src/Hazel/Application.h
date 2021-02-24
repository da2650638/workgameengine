#pragma once
#include "Core.h"
#include "Event\Event.h"
#include "Window.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		/* Should be defined in the client side. */
		static Application* CreateApplication();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
}