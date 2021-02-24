#include "hzpch.h"
#include <Hazel.h>

/* 因为本机器vs2015的项目引用添加失败，因此使用更改SandboxApp附加库目录以及附加依赖项的形式来实现静态链接Hazel项目的Lib文件 */
/* 并将Hazel项目添加为Sandbox项目的依赖项 */
/* 现在换成vs2019就好了 */
class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::Application::CreateApplication()
{
	return new Sandbox();
}

