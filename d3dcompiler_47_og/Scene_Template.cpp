#include "LuaHook.h"
#include "GameObject.h"

#include "Scene_Template.h"
#include "Input.h"

using namespace std;
using namespace moddingApi;

void Scene_Template::Start()
{
	cout << "Scene_Template :: Start begin" << endl;

	// Start player
	WorldCollision::Initialize("Scene_Template");

	cout << "Scene_Template :: Init world collision" << endl;

	isInitialized = true;

	LuaHook::fc_ccSetLuaGlobalInt(-1);
	LuaHook::fc_ccSetLuaGlobalString("changeStage");

	cout << "Scene_Template :: Start end" << endl;
}

#include "ccGeneralGameFunctions.h"
void Scene_Template::Update()
{
	if (LuaHook::fc_ccGetCastPointer("pl_torso") != 0 && objectsInit == false)
	{
		objectsInit = true;
		CreateIntialObjects();

		inCutscene = true;
		actualCutscene = 0;
	}

	if (inCutscene)
	{
		switch (actualCutscene)
		{
		case 0:
			// Start cutscene
			break;
		}
	}

	GameObject::LoopGameObjects();
	Input::UpdateKeys();
}

#include "InteractiveMain.h"
#include "Interactive_Examine.h"
void Scene_Template::CreateIntialObjects()
{
	GameObject* o = new GameObject("o", Vector3(0, 0, 0), "");
	o->Start();
	o->UpdateModel("data/zt/stage/001_fortress.xfbin", "st00bod4");

	cout << "Scene_Template :: Initialized objects" << endl;
}

void Scene_Template::SetCamera(Vector3 pos, Vector3 look, int fov)
{
	LuaHook::fc_ccSetCameraByCoord(
		pos.x,
		pos.y,
		pos.z,
		look.x,
		look.y,
		look.z,
		fov, 0);
}

void Scene_Template::SetMessage(std::string msg1, std::string msg2)
{
	void* message1 = (void*)(new vector<std::string>());
	void* message2 = (void*)(new vector<std::string>());

	((vector<std::string>*)message1)->push_back(msg1);
	((vector<std::string>*)message2)->push_back(msg2);

	//PlayerScript* pl = (PlayerScript*)(PlayerScript::pl);
	//pl->StartInteraction((uintptr_t)message1, (uintptr_t)message2);
}