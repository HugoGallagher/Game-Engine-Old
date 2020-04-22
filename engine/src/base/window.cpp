#include "pch.h"
#include "window.h"

#include <GLFW/glfw3.h>

namespace engine
{
	void window::e_mouse_button_callback(GLFWwindow* window, int b, int a, int m)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		e_mouse_button e(b, a, (float)x, (float)y);
		//logger::quick_log(logger::levels::info, e.print());

		eb.e_mb.emplace_back(e);
	}
	void window::e_mouse_scroll_callback(GLFWwindow* window, double xs, double ys)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		e_mouse_scroll e((float)ys, (float)x, (float)y);
		//logger::quick_log(logger::levels::info, e.print());

		eb.e_ms.emplace_back(e);
	}
	void window::e_mouse_move_callback(GLFWwindow* window, double x, double y)
	{
		e_mouse_move e((float)x, (float)y);
		//logger::quick_log(logger::levels::info, e.print());

		eb.e_mm.emplace_back(e);
	}

	void window::e_keyboard_key_callback(GLFWwindow* window, int k, int s, int a, int m)
	{
		e_keyboard_key e(k, s, a);
		//logger::quick_log(logger::levels::info, e.print());

		eb.e_kk.emplace_back(e);
	}
}