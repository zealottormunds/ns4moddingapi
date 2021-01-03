#include <stdio.h>
#include "Interface_Text.h"
#include "LuaHook.h"
#include "ccGameProperties.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace moddingApi;

void Interface_Text::ShowText()
{
	//cout << "Interface_Text :: Show Text" << endl;

	int textlen = text.length();
	int resx = ccGameProperties::GetProperty("ResolutionX");

	bool cont = true;
	int actualLine = 0;
	int lastx = position.x;

	for (int x = 0; x < textlen; x++)
	{
		cont = true;
		std::string letter = "";
		letter.push_back(text.at(x));

		int linenum = (int)(x / lineLength);

		std::string thisname = textId;
		thisname = textId + to_string(x);

	std:string path = "";
		char actual = text.at(x);
		if (actual >= 0x61 && actual <= 0x6E) path = "data/zt/ui/font/font_an_s.xfbin";
		else if (actual >= 0x6F && actual <= 0x7A) path = "data/zt/ui/font/font_oz_s.xfbin";
		else if (actual >= 0x41 && actual <= 0x4E) path = "data/zt/ui/font/font_an.xfbin";
		else if (actual >= 0x4F && actual <= 0x5A) path = "data/zt/ui/font/font_oz.xfbin";
		else if (actual >= 0x30 && actual <= 0x39) path = "data/zt/ui/font/font_number.xfbin";
		else
		{
			path = "data/zt/ui/font/font_symbol.xfbin";

			switch (text.at(x))
			{
			case ',':
				letter = "comma";
				break;
			case '.':
				letter = "dot";
				break;
			case ':':
				letter = "doubledot";
				break;
			case '!':
				letter = "exclamat";
				break;
			case '-':
				letter = "hyphen";
				break;
			case '(':
				letter = "parleft";
				break;
			case ')':
				letter = "parright";
				break;
			case '>':
				letter = "ptrleft";
				break;
			case '<':
				letter = "ptrright";
				break;
			case '?':
				letter = "question";
				break;
			case '/':
				letter = "slash";
				break;
			case '%':
				letter = "per";
				break;
			case '_':
				letter = "underscore";
				break;
			case '\n':
				lastx = position.x;
				actualLine = actualLine + 1;
				cont = false;
				break;
			}
		}

		if (cont)
		{
			LuaHook::fc_ccCreateSprite((char*)thisname.c_str(), (char*)path.c_str(), (char*)letter.c_str());

			float posx = 0;
			float posy = 0;

			if (lineLength != -1)
			{
				if (rightPivot == false) posx = position.x + (horizontalSpacing * (x % lineLength));
				else posx = (resx - position.x - (horizontalSpacing * lineLength)) + (horizontalSpacing * (x % lineLength));
				posy = position.y + (verticalSpacing * linenum);
			}
			else
			{
				posx = lastx;
				lastx = lastx + horizontalSpacing;
				posy = position.y + (verticalSpacing * actualLine);
			}

			LuaHook::fc_ccSetSpritePosition((char*)thisname.c_str(), posx, posy);
		}
	}

	visible = true;
}

void Interface_Text::HideText()
{
	int textlen = Interface_Text::text.length();

	for (int x = 0; x < textlen; x++)
	{
		if (visible)
		{
			std::string thisname = textId;
			thisname = textId + to_string(x);
			LuaHook::fc_ccDeleteSprite((char*)thisname.c_str());
		}
	}

	visible = false;
}

void Interface_Text::DeleteText()
{
	if (visible)
	{
		HideText();
	}

	delete this;
}