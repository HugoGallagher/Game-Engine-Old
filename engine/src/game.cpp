#include "pch.h"

#include "game.h"

#include "base/logger.h"
#include "base/window.h"
#include "base/input.h"

#include "base/maths/types/vector2.h"
#include "base/maths/types/matrix.h"
#include "base/maths/types/matrix4.h"

#include "benchmark.h"

namespace engine
{
	logger pl = logger();
	window w = window(WIDTH, HEIGHT, false, "Engine");
	renderer3 r;

	uint c1, c2;

	float cs[3] = { 142.0f, 73.0f, 205.0f };
	//float cs[3] = { 255.0f, 255.0f, 255.0f };

	game::game() {}

	game::~game() {}

	void game::run()
	{
		r.init(); // Move these lines to init

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					r.create_cube(1, i - 50, j - 50, k + 10 , cs);
				}
			}
		}

		c1 = r.create_cube(10.0f, 0.0f, 0.0f, 0.0f, cs);
		c2 = r.create_cube(100.0f, 0.0f, -100.0f, 3.0f, cs);
		//c2 = r.create_cube(2.0f, -5.0f, 0.0f, 3.0f, cs);

		pl.log(logger::levels::info, "Engine started");

		benchmark bm = benchmark();
		bm.run_benchmark();
		float c_time = 0.0f;
		float p_time = 0.0f;
		while (true)
		{
			delta_time = c_time - p_time;
			p_time = glfwGetTime();

			update();
			draw();
			
			this->handle_events(eb);

			c_time = glfwGetTime();
		}
	}

	void game::update()
	{
		input::update();
		w.update();
		r.update();
		//std::cout << r.c.position.x << ", " << r.c.position.y << ", " << r.c.position.z << std::endl;

		//r.translate_cube(c1, vector3(0.000f, 0.001f, 0.0f));
		//std::cout << delta_time << std::endl;

		//r.rotate_x_cube(c1, 1 * delta_time);
		//r.rotate_y_cube(c1, 1 * delta_time);
		//r.rotate_z_cube(c1, 1 * delta_time);
	}
	void game::draw()
	{
		r.draw();
	}

	void game::handle_events(e_bus& eb)
	{
		#define E_DELETE_IF_HANDLED(x, y) if (x.handled) { eb.y.erase(eb.y.begin() + i); } else { i++; }

		for (int i = 0; i < eb.e_mb.size();)
		{
			e_mouse_button& e = eb.e_mb[i];
			//program_logger.log(logger::info, e.print());
			e.handled = true;
			E_DELETE_IF_HANDLED(e, e_mb)
		}
		for (int i = 0; i < eb.e_ms.size();)
		{
			e_mouse_scroll& e = eb.e_ms[i];
			//program_logger.log(logger::info, e.print());
			e.handled = true;
			E_DELETE_IF_HANDLED(e, e_ms)
		}
		for (int i = 0; i < eb.e_mm.size();)
		{
			e_mouse_move& e = eb.e_mm[i];
			input::update_mousepos(e.x_loc, e.y_loc);
			//r.camera.rotation.x += e.x_loc;
			//r.camera.rotation.y += e.y_loc;
			//program_logger.log(logger::info, e.print());
			e.handled = true;
			E_DELETE_IF_HANDLED(e, e_mm)
		}

		for (int i = 0; i < eb.e_kk.size();)
		{
			e_keyboard_key& e = eb.e_kk[i];
			//program_logger.log(logger::info, e.print());
			e.handled = input::update_keys(e.key_pressed, e.action);
			E_DELETE_IF_HANDLED(e, e_kk)
		}
	}
}