#pragma once
#include "GameObject.h"
#include <vector>

namespace moddingApi
{
	class Scene
	{
	public:
		static bool init;
		static int actualScene;
		static uintptr_t scenePtr;

		static int gCountStatic;
		static std::vector<uintptr_t> gListStatic;

		static std::vector<std::string> SceneNames;
		static void Init();
		static void LoadScene(int sceneid);
		static void LoadScene(std::string scenename);
		static void Update();
	};
}