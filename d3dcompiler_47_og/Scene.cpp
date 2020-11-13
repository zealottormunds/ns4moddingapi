#include "Scene.h"
#include "Scene_Template.h"

using namespace std;
using namespace moddingApi;

bool Scene::init = false;
int Scene::actualScene = -1;
uintptr_t Scene::scenePtr = 0;
vector<string> Scene::SceneNames = vector<string>();

int Scene::gCountStatic = 0;
vector<uintptr_t> Scene::gListStatic = vector<uintptr_t>();

void Scene::Init()
{
	Scene::SceneNames.push_back("Scene_Template");
	Scene::init = true;

	cout << "Scene :: Init scene names" << endl;
}

void Scene::LoadScene(int sceneid)
{
	Scene::actualScene = sceneid;
	void* scene;

	switch (sceneid)
	{
	default:
		cout << "Scene :: Scene id not found" << endl;
		return;
	case 0:
		GameObject::DeleteAll();
		scene = (void*)(new Scene_Template());
		Scene::scenePtr = (uintptr_t)scene;
		break;
	}

	cout << "Scene :: Loaded scene " << sceneid << endl;
}

void Scene::LoadScene(string scenename)
{
	for (int x = 0; x < Scene::SceneNames.size(); x++)
	{
		if (scenename == Scene::SceneNames[x])
		{
			LoadScene(x);
			return;
		}
	}

	cout << "Scene :: Scene name not found" << endl;
}

void Scene::Update()
{
	if (Scene::scenePtr == 0) cout << "Scene :: No scene loaded" << endl;

	void* scene;

	switch (Scene::actualScene)
	{
	default:
		cout << "Scene :: No scene loaded" << endl;
		break;
	case 0:
		scene = (void*)(Scene::scenePtr);
		if(((Scene_Template*)scene)->isInitialized == false) ((Scene_Template*)scene)->Start();
		else ((Scene_Template*)scene)->Update();
		break;
	}

	//cout << "Scene :: Update finished" << endl;
}