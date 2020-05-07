#pragma once
#include "pch.h"
#include "macros.h"

#include "base/renderer/shapes/shape3.h"

#include "base/renderer/opengl/gl_program.h"
#include "base/renderer/opengl/gl_program3.h"
#include "base/renderer/opengl/shader.h"

#include "base/renderer/camera.h"

#include "base/maths/types/matrix4.h"
#include "base/maths/types/vector4.h"
#include "base/maths/types/vector3.h"

namespace engine
{
	class DLL cube : public shape3
	{
	public:
		//cube(float cs[3]) { colour = { cs[0] / 255, cs[1] / 255, cs[2] / 255, cs[3] / 255, 255 }; }
		//void draw(gl_program3& prog, camera& cam);

		void create_buffer_data(std::vector<void*> params) override;
	};
}