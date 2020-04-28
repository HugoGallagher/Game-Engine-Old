#pragma once
#include "pch.h"
#include "macros.h"

namespace engine
{
	class linkedlist
	{
	public:
		std::vector<uchar> data;
		std::vector<uint> sizes;

		//template <typename T>
		void add_element(float item)
		{
			//data.reserve(sizeof(data) + sizeof(item));
			//static_cast<uchar>(item);
			//std::copy(&item, &item + sizeof(item), data[sizeof(data) - sizeof(item)]);
			//sizes.insert(sizes.end(), sizeof(item));
		}

		void* get_element(uint index)
		{
			uint offset = 0;

			for (int i = 0; i <= index; i++)
			{
				offset += sizes[i];
			}

			return &data[offset];
		}
	};
}