#pragma once
#include "Mod.h"
#include <vector>

class ModManager
{
private:
	static std::vector<Mod*> modList;
public:
	static std::vector<Mod*> GetModList()
	{
		return modList;
	}

	static void AddMod(Mod* p)
	{
		modList.push_back(p);
	}

	static int GetModIndex(Mod * p)
	{
		int index = -1;

		int modCount = modList.size();
		for (int x = 0; x < modCount; x++)
		{
			if (p == modList[x])
			{
				index = x;
				x = modList.size();
			}
		}

		return index;
	}

	static void RemoveMod(Mod * p)
	{
		int modIndex = GetModIndex(p);
		
		if (modIndex != -1)
		{
			p->Unload();
			modList[modIndex] = 0;
		}
	}
};

class ExtensionManager
{
	struct Extension
	{
		std::string extension = "[null]";
		Plugin* parser;

		Extension(std::string ext, Plugin * p)
		{
			extension = ext;
			parser = p;
		}
	};

private:
	static std::vector<Extension*> extensionList;
public:
	static bool HasExtension(std::string ext)
	{
		bool has = false;

		int extCount = extensionList.size();
		for (int x = 0; x < extCount; x++)
		{
			if (extensionList[x]->extension == ext)
			{
				has = true;
				x = extCount;
			}
		}

		return has;
	}

	static void AddExtension(std::string ext, Plugin * p)
	{
		Extension * e = new Extension(ext, p);
		extensionList.push_back(e);
	}

	static Plugin* GetExtensionParser(std::string ext)
	{
		Plugin * p = nullptr;

		int extCount = extensionList.size();
		for (int x = 0; x < extCount; x++)
		{
			if (extensionList[x]->extension == ext)
			{
				p = extensionList[x]->parser;
				x = extCount;
			}
		}

		return p;
	}
};