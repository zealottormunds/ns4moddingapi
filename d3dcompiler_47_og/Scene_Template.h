#pragma once
#include <vector>
#include "Vector3.h"

namespace moddingApi
{
	class Scene_Template
	{
	public:
		bool isInitialized = false;
		bool objectsInit = false;
		void Start();
		void Update();
		void CreateIntialObjects();

		bool inCutscene = false;
		int actualCutscene = 0;

		void SetCamera(Vector3 pos, Vector3 look, int fov);
		void SetMessage(std::string msg1, std::string msg2);
	};
}