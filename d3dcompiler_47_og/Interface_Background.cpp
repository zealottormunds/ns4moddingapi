#include <stdio.h>
#include "Interface_Background.h"
#include "LuaHook.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace moddingApi;

void Interface_Background::Show()
{
	cout << "Interface_Background :: Show" << endl;

	LuaHook::fc_ccCreateSprite((char*)imgid.c_str(), (char*)xfbin.c_str(), (char*)sprite.c_str());
	float posx = position.x;
	float posy = position.y;
	LuaHook::fc_ccSetSpritePosition((char*)imgid.c_str(), posx, posy);

	visible = true;
}

void Interface_Background::Hide()
{
	std::string thisname = imgid;
	LuaHook::fc_ccDeleteSprite((char*)thisname.c_str());

	visible = false;
}

void Interface_Background::Delete()
{
	if (visible)
	{
		Hide();
	}

	delete this;
}