#pragma once
#include "pch.h"
#include "macros.h"
#include "globals.h"

#include "base/input.h"
#include "base/maths/maths.h"

#include "base/maths/types/matrix4.h"
#include "base/maths/types/vector4.h"
#include "base/maths/types/vector3.h"
#include "base/maths/types/vector2.h"

namespace engine
{
	class camera
	{
	public:
		vector3 UP = vector3(0, 1, 0);

		float speed = 10.0f;
		float delta_speed = 0.0f;
		vector4 velocity;
		vector2 rotation = vector2(0, 0);
		vector3 position;
		matrix4 p_matrix, v_matrix;

		void init();
		void update();
	};
}