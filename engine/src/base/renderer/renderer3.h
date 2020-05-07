#pragma once
#include "pch.h"
#include "macros.h"

#include "base/renderer/opengl/gl_program.h"
#include "base/renderer/opengl/gl_program2.h"
#include "base/renderer/opengl/gl_program3.h"
#include "base/renderer/opengl/shader.h"
#include "base/renderer/opengl/framebuffer.h"

#include "base/renderer/camera.h"
#include "base/renderer/space3.h"
#include "base/renderer/shapes/tri.h"
#include "base/renderer/shapes/rect.h"
#include "base/renderer/shapes/cube.h"

#include <glad/glad.h>

namespace engine
{
	class DLL renderer3
	{
	public:
		framebuffer fb;

		camera cam;

		space3 space;

		renderer3() {}

		void init();
		void update();
		void draw();
	};
}
