#include "Scene.h"
#include "Input.h"

#include <iostream>

using namespace std;
using namespace moddingApi;

bool Scene::debug = true;
bool Scene::debugcam = false;

bool Scene::init = false;
int Scene::actualScene = 0; // Initial game scene
bool Scene::beginGame = false;
bool Scene::loadedFiles = false;
bool Scene::startCast = false;
uintptr_t Scene::scenePtr = 0;
vector<string> Scene::SceneNames = vector<string>();

int Scene::gCountStatic = 0;
vector<uintptr_t> Scene::gListStatic = vector<uintptr_t>();

void Scene::Init()
{
	Scene::init = true;

	cout << "Scene :: Init scene names" << endl;
}

void Scene::SetNextScene(int sceneid)
{
	Scene::actualScene = sceneid;
}

void Scene::LoadSceneFiles()
{
	startCast = false;

	if (Scene::init == false) Init();

	Scene::loadedFiles = false;
	Scene::beginGame = false;

	void* scene;

	switch (Scene::actualScene)
	{
	default:
		cout << "Scene :: Scene id not found" << endl;
		break;
	}
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
	bool isInitScene = false;

	switch (Scene::actualScene)
	{
		default:
		cout << "Scene :: No scene loaded" << endl;
		break;
	}

	if (isInitScene)
	{
		if (Input::GetKeyDown(VK_F1) && debug)
		{
			debugcam = !debugcam;
		}

		if (debugcam)
		{
			//if(freecam != NULL) freecam->Loop();
		}
	}

	//cout << "Scene :: Update finished" << endl;
}