#include "hzpch.h"
#include <Hazel.h>

/* ��Ϊ������vs2015����Ŀ�������ʧ�ܣ����ʹ�ø���SandboxApp���ӿ�Ŀ¼�Լ��������������ʽ��ʵ�־�̬����Hazel��Ŀ��Lib�ļ� */
/* ����Hazel��Ŀ���ΪSandbox��Ŀ�������� */
/* ���ڻ���vs2019�ͺ��� */
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

