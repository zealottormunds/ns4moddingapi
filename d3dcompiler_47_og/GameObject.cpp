#include "GameObject.h"
#include "LuaHook.h"

#include <stdio.h>
#include <iostream>
#include "Scene.h"

using namespace std;
using namespace moddingApi;

int GameObject::gCount = 0;
vector<uintptr_t> GameObject::gList = vector<uintptr_t>();
GameObject GameObject::Null = GameObject("NULL");

void GameObject::Initialize()
{

}

void GameObject::Start()
{
	internalid = GameObject::gCount;
	GameObject::gCount++;
	GameObject* t = this;
	GameObject::gList.push_back((uintptr_t)t);
	destroyOnLoad = true;
}

void GameObject::Update()
{
	if (destroyInTimer > 0)
	{
		destroyInTimer--;
	}
	else if (destroyInTimer == 0)
	{
		//this->enabled = false;
		this->Destroy();
	}

	if (Vector3::cmp(*lastCastDirection, Vector3(transform->rotx, transform->roty, 0)) == false)
	{
		*lastCastDirection = Vector3(transform->rotx, transform->roty, 0);
		LuaHook::fc_ccMoveDirection((char*)name.c_str(), transform->rotx, transform->roty, 0, 0, 0);
	}

	UpdateComponent();
}

void GameObject::UpdateDisabled()
{
	LuaHook::fc_ccDeleteCast((char*)name.c_str());
}

void GameObject::UpdateComponent()
{
	
}

void GameObject::UpdateModel(std::string p, std::string n)
{
	//cout << "Updating model" << endl;

	if (modelPath == p && modelName == n) return;

	modelPath = p;
	modelName = n;

	char* ay = (char*)(modelPath.c_str());
	char* on = (char*)(modelName.c_str());

	if (modelPath != "" && modelName != "")
	{
		LuaHook::fc_ccCreateCastByChunk((char*)name.c_str(), ay, on);
		LuaHook::fc_ccMoveCast((char*)name.c_str(), transform->position.x, transform->position.y, transform->position.z, 0, 0);
	}
}

void GameObject::UpdateAnim(std::string p, std::string n)
{
	if (modelAnmPath == p && modelAnmName == n) return;

	modelAnmPath = p;
	modelAnmName = n;

	if (modelPath != "" && modelAnmPath != "" && modelName != "" && modelAnmName != "")
	{
		LuaHook::fc_ccCreateCastByChunk((char*)name.c_str(), (char*)modelPath.c_str(), (char*)modelName.c_str());
		LuaHook::fc_ccMoveCast((char*)name.c_str(), transform->position.x, transform->position.y, transform->position.z, 0, 0);
		LuaHook::fc_ccSetCastMotion((char*)name.c_str(), (char*)modelAnmPath.c_str(), (char*)modelAnmName.c_str());
	}

	//cout << "GameObject :: Playing " << n << " in " << name << endl;
}

void GameObject::SetPosition(Vector3 pos)
{
	if (transform->position.x == pos.x && transform->position.y == pos.y && transform->position.z == pos.z) return;

	transform->position.x = pos.x;
	transform->position.y = pos.y;
	transform->position.z = pos.z;
	LuaHook::fc_ccMoveCast((char*)name.c_str(), pos.x, pos.y, pos.z, 0, 0);
}

void GameObject::Destroy()
{
	enabled = false;
	cout << "started destroy " << endl;
	UpdateDisabled();

	cout << "updated disable" << endl;

	GameObject* g = this;

	for (int x = componentList.size() - 1; x >= 0; x--)
	{
		RemoveComponent(x);
	}

	cout << "iid " << internalid << endl;
	if (destroyOnLoad)
	{
		GameObject::gList[internalid] = 0;
	}
	else
	{
		Scene::gListStatic[internalid] = 0;
	}

	cout << "Destroyed object " << internalid << "\"" + this->name + "\"" << endl;

	delete g;
}

void GameObject::DontDestroyOnLoad(bool t)
{
	if (t)
	{
		if (destroyOnLoad)
		{
			GameObject::gCount = GameObject::gCount - 1;
			GameObject::gList[internalid] = 0;

			internalid = Scene::gCountStatic;
			Scene::gCountStatic++;
			GameObject * thisObject = this;
			Scene::gListStatic.push_back((uintptr_t)thisObject);
		}
	}
	else
	{
		if (destroyOnLoad == false)
		{
			Scene::gCountStatic = Scene::gCountStatic - 1;
			Scene::gListStatic[internalid] = 0;

			internalid = GameObject::gCount;
			GameObject::gCount++;
			GameObject * thisObject = this;
			GameObject::gList.push_back((uintptr_t)thisObject);
		}
	}
}

void* GameObject::AddComponent(std::string comp)
{
	void* cmp = 0;

	return cmp;
}

uintptr_t GameObject::GetComponent(std::string comp)
{
	uintptr_t cmp = 0;
	int cmpIndex = -1;

	for (int x = 0; x < componentNames.size(); x++)
	{
		if (componentNames[x] == comp)
		{
			cmpIndex = x;
			cmp = componentList[cmpIndex];
			x = componentNames.size();
		}
	}

	return cmp;
}

int GameObject::GetComponentIndex(std::string comp)
{
	int cmpIndex = -1;

	for (int x = 0; x < componentNames.size(); x++)
	{
		if (componentNames[x] == comp)
		{
			cmpIndex = x;
			x = componentNames.size();
		}
	}

	return cmpIndex;
}

void GameObject::RemoveComponent(std::string comp)
{

}

void GameObject::RemoveComponent(int index)
{

}

void GameObject::DeleteAll(bool statics)
{
	for (int x = 0; x < GameObject::gCount; x++)
	{
		GameObject* thisObject = (GameObject*)(GameObject::gList[x]);
		thisObject->Destroy();
	}

	if (statics)
	{
		for (int x = 0; x < Scene::gCountStatic; x++)
		{
			GameObject* thisObject = (GameObject*)(Scene::gListStatic[x]);
			thisObject->Destroy();
		}
	}
}

void GameObject::LoopGameObjects()
{
	// Loop objects
	for (int x = 0; x < GameObject::gCount; x++)
	{
		if (GameObject::gList[x] != 0)
		{
			GameObject* g = (GameObject*)(GameObject::gList[x]);
			if (g->enabled) g->Update();
			else g->UpdateDisabled();
		}
	}

	// Loop static objects
	for (int x = 0; x < Scene::gCountStatic; x++)
	{
		if (Scene::gListStatic[x] != 0)
		{
			GameObject* g = (GameObject*)(Scene::gListStatic[x]);
			if (g->enabled) g->Update();
			else g->UpdateDisabled();
		}
	}

	// Delete null objects
	vector<uintptr_t> newGameList;
	int newGameCount = 0;
	for (int x = 0; x < GameObject::gCount; x++)
	{
		if (GameObject::gList[x] != 0)
		{
			newGameList.push_back(GameObject::gList[x]);
			GameObject * g = (GameObject*)(GameObject::gList[x]);
			g->internalid = newGameCount;
			newGameCount++;
		}
		else
		{
			GameObject * gd = (GameObject*)(GameObject::gList[x]);
			delete gd;
			cout << "Deleted original" << endl;
		}
	}
	GameObject::gList = newGameList;
	GameObject::gCount = newGameCount;

	// Delete static null objects
	for (int x = Scene::gCountStatic - 1; x >= 0; x--)
	{
		if (Scene::gListStatic[x] == 0)
		{
			Scene::gListStatic.erase(Scene::gListStatic.begin() + x);
			Scene::gCountStatic--;

			for (int a = x + 1; a < Scene::gCountStatic; a++)
			{
				GameObject * g = (GameObject*)(Scene::gListStatic[x]);
				g->internalid--;
			}
		}
	}

	//cout << "GameObject :: Loop" << endl;
}

int GameObject::gListGetIndex(string _name)
{
	int ind = -1;

	for (int x = 0; x < GameObject::gList.size(); x++)
	{
		GameObject* thisObject = (GameObject*)(GameObject::gList[x]);
		if (thisObject->name == _name)
		{
			ind = x;
			x = GameObject::gList.size();
		}
	}

	return ind;
}

uintptr_t GameObject::Find(string _name)
{
	for (int x = 0; x < GameObject::gCount; x++)
	{
		GameObject* thisObject = (GameObject*)(GameObject::gList[x]);

		if (thisObject->name == _name)
		{
			return GameObject::gList[x];
		}
	}

	for (int x = 0; x < Scene::gCountStatic; x++)
	{
		GameObject* thisObject = (GameObject*)(Scene::gListStatic[x]);

		if (thisObject->name == _name)
		{
			return Scene::gListStatic[x];
		}
	}

	return (uintptr_t)&GameObject::Null;
}