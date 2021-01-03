#ifndef UI_BACKGROUND_H 
#define UI_BACKGROUND_H
#pragma once

#include <vector>
#include "Vector3.h"

namespace moddingApi
{
	class Interface_Background
	{
	public:
		Interface_Background(std::string id, std::string file, std::string tex, Vector3 pos, bool show = true) : imgid(id), xfbin(file), sprite(tex), position(pos)
		{
			if(show) Show();
		}

		std::string imgid = "";
		std::string xfbin;
		std::string sprite;

		bool visible = false;
		Vector3 position;

		void Show();
		void Hide();
		void Delete();
	};
}

#endif