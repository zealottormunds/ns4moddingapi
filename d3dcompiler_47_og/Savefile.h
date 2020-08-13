#ifndef SAVEFILE_H 
#define SAVEFILE_H
#pragma once

namespace moddingApi
{
	class Savefile
	{
	public:
		static bool isRpgMode;
		static std::string GetRootPath();
		static bool FileExists(std::string path);
		static std::string username;
		static int ryo;
		static int maxhealth;
		static int health;
		static int maxchakra;
		static int chakra;
		static int maxsub;
		static int sub;

		static int torsocount;
		static int bottomcount;
		static int actualtorso;
		static int actualbottom;

		static void Save();
		static void Load();
	};
}

#endif