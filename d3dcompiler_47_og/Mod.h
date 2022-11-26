#pragma once
#include <string>
#include <vector>
#include "Plugin.h"

class Mod
{
public:
	std::string title = "";
	std::string author = "";
	std::string description = "";
	std::string path = "";
	int state = 0;

	Mod(std::string _title, std::string _author, std::string _description, std::string path_)
	{
		title = _title;
		author = _author;
		description = _description;
		path = path_;
	}

	std::vector<Plugin*> pluginList;

	void Unload()
	{
		int pluginCount = pluginList.size();
		for (int x = 0; x < pluginCount; x++)
		{
			Plugin* p = pluginList[x];

			if (p) p->Unload();
		}
	}

	void Update()
	{
		int pluginCount = pluginList.size();
		for (int x = 0; x < pluginCount; x++)
		{
			Plugin* p = pluginList[x];
			
			if(p) p->Update();
		}
	}

	void PreRender()
	{
		int pluginCount = pluginList.size();
		for (int x = 0; x < pluginCount; x++)
		{
			Plugin* p = pluginList[x];
			if (p) p->PreRender();
		}
	}

	void PostRender()
	{
		int pluginCount = pluginList.size();
		for (int x = 0; x < pluginCount; x++)
		{
			Plugin* p = pluginList[x];
			if (p) p->PostRender();
		}
	}

	void OnGUI(bool s, __int64 hwnd, __int64 imguiContext)
	{
		int pluginCount = pluginList.size();
		for (int x = 0; x < pluginCount; x++)
		{
			Plugin* p = pluginList[x];
			if (p) p->OnGUI(s, hwnd, imguiContext);
		}
	}
};