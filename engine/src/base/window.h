#pragma once

#include "pch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "macros.h"

#include "base/events/event.h"
#include "base/events/e_mouse.h"
#include "base/events/e_keyboard.h"
#include "base/events/e_bus.h"

#include "base/logger.h"

namespace engine
{
	class DLL window
	{
		GLFWwindow* _window;

		unsigned int _width, _height;
		bool _vsync = false;
		const char* _title;
	public:
		//typedef void(window::*e_callback_function)(event&);
		//e_callback_function e_callback;

		//std::function<void(event&)> e_callback;

		window(unsigned int w, unsigned int h, bool v, const char* t) : _width(w), _height(h), _vsync(v), _title(t)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

			glfwInit();

			_window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
			glfwMakeContextCurrent(_window);
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			glfwSetMouseButtonCallback(_window, &engine::window::e_mouse_button_callback);
			glfwSetScrollCallback(_window, engine::window::e_mouse_scroll_callback);
			glfwSetCursorPosCallback(_window, engine::window::e_mouse_move_callback);

			glfwSetKeyCallback(_window, engine::window::e_keyboard_key_callback);

			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		}

		//~window() {}

		void update()
		{
			glfwSwapBuffers(_window);
			glfwPollEvents();
		}

		unsigned int get_width() const { return _width; }
		unsigned int get_height() const { return _height; }
		bool vsync_enabled() const { return _vsync; }

		static void e_mouse_button_callback(GLFWwindow* window, int b, int a, int m);
		static void e_mouse_scroll_callback(GLFWwindow* window, double xs, double ys);
		static void e_mouse_move_callback(GLFWwindow* window, double x, double y);

		static void e_keyboard_key_callback(GLFWwindow* window, int k, int s, int a, int m);
	};
}