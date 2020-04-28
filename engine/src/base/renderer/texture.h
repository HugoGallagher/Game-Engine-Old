#pragma once
#include "pch.h"
#include "macros.h"

#include "glad/glad.h"

namespace engine
{
	class texture
	{
	public:
		uint id;
		int w, h, c;
		uchar* data;

		//~texture() { stbi_image_free(data); }

		void load();
		void unload();

		void bind();
	};
}