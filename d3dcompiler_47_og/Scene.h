#ifndef SCENE_H 
#define SCENE_H
#pragma once

#include "GameObject.h"
#include <vector>
//#include "Controller_FreeCamera.h"

namespace moddingApi
{
	class Scene
	{
	public:
		static bool debug;
		static bool debugcam;
		//static Controller_FreeCamera * freecam;

		static bool init;
		static int actualScene;
		static bool beginGame;
		static bool loadedFiles;
		static bool startCast;
		static uintptr_t scenePtr;

		static int gCountStatic;
		static std::vector<uintptr_t> gListStatic;

		static std::vector<std::string> SceneNames;
		static void Init();
		static void SetNextScene(int sceneid);
		static void LoadSceneFiles();
		static void LoadScene(int sceneid);
		static void LoadScene(std::string scenename);
		static void Update();
	};
}

#endif