#pragma once

#ifdef HZ_PLATFORM_WINDOWS

int main(int argc, char **argv)
{
	/* EntryPoint Step 1: Init the log module. */
	Hazel::Log::Init();
	HZ_CORE_DEBUG("Welcome to Hazel Application1.");
	int var = 5;
	HZ_APP_DEBUG("var = {0}", var);
	Hazel::Application *app = Hazel::Application::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif