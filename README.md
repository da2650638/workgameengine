# workgameengine
---------------------
2021年2月24日开发日志
1Application类中添加void OnEvent(Event & e)并实现。
2在Application类中设置window的EventCallbackFn(void(Event&))实例为OnEvent(Event&)方法。
3添加宏定义#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1) / #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
4WindowsWindow类中的Init方法中设置GLFW的回调函数。glfwSetWindowSizeCallback/glfwSetWindowCloseCallback/key/MouseButton/MouseScroll/MouseMove
