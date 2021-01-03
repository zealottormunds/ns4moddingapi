#ifndef INTERFACE_TEXT_H 
#define INTERFACE_TEXT_H
#pragma once

#include <vector>
#include "Vector3.h"

namespace moddingApi
{
	class Interface_Text
	{
	public:
		Interface_Text(std::string id, std::string str, Vector3 pos, bool show = true, bool rpivot = false, bool dpivot = false)
			: textId(id), text(str), position(pos), rightPivot(rpivot), downPivot(dpivot)
		{
			if (show) ShowText();
		}

		std::string textId = "";
		std::string text = "";

		bool visible = false;
		Vector3 position;

		bool rightPivot = false;
		bool downPivot = false;

		int lineLength = 18;
		float horizontalSpacing = 16;
		float verticalSpacing = 28;

		void ShowText();
		void HideText();
		void DeleteText();
	};
}

#endif