#include <math.h>
#include <iostream>
#include <stdio.h>
#include "GameObject.h"

#include "LuaHook.h"
#include "Scene.h"

#include "EntityMain.h"
#include "Entity_Fireball.h"

using namespace std;
using namespace moddingApi;

int GameObject::gCount = 0;
vector<uintptr_t> GameObject::gList = vector<uintptr_t>();
GameObject GameObject::Null = GameObject("NULL");

void GameObject::Start()
{
	internalid = GameObject::gCount;
	GameObject::gCount++;
	GameObject* t = this;
	GameObject::gList.push_back((uintptr_t)t);
	destroyOnLoad = true;
}

#include "BoxCollider.h"
#include "Input.h"
void GameObject::Update()
{
	if (!interact)
	{
		
	}

	if (destroyInTimer > 0)
	{
		destroyInTimer--;
	}
	else if (destroyInTimer == 0)
	{
		this->enabled = false;
		//this->Destroy();
	}

	if (updateForce)
	{
		transform.position = Vector3::add(transform.position, rigidbody.actualForce);
	}

	if (Input::GetKeyDown('K'))
	{
		if(modelPath != "" && modelName != "") LuaHook::fc_ccCreateCastByChunk((char*)name.c_str(), (char*)modelPath.c_str(), (char*)modelName.c_str());
		LuaHook::fc_ccSetCastPosition((char*)name.c_str(), transform.position.x, transform.position.y, transform.position.z);
	}

	if (Vector3::cmp(lastCastPosition, transform.position) == false)
	{
		lastCastPosition = transform.position;
		LuaHook::fc_ccMoveCast((char*)name.c_str(), transform.position.x, transform.position.y, transform.position.z, 0, 0);
	}

	if (modelPath != "" && modelAnmPath != "" && modelName != "" && modelAnmName != "")
	{
		if (LuaHook::fc_ccGetCastPointer((char*)name.c_str()) == 0)
		{
			LuaHook::fc_ccCreateCastByChunk((char*)name.c_str(), (char*)modelPath.c_str(), (char*)modelName.c_str());
			LuaHook::fc_ccSetCastMotion((char*)name.c_str(), (char*)modelAnmPath.c_str(), (char*)modelAnmName.c_str());
			LuaHook::fc_ccSetCastPosition((char*)name.c_str(), transform.position.x, transform.position.y, transform.position.z);
		}
	}	

	/*if(BoxCollider::isColliding(rigidbody.collider, pl->interactionPoint.rigidbody.collider) == true)
	{
		pl->actualInteraction = (uintptr_t)(GameObject*)this;
	}
	else
	{
		GameObject g = *(GameObject*)(pl->actualInteraction);

		if(g.name == this->name) pl->actualInteraction = (uintptr_t)(GameObject*)&GameObject::Null;
	}*/

	UpdateComponent();
}

void GameObject::UpdateDisabled()
{
	LuaHook::fc_ccDeleteCast((char*)name.c_str());
}

void GameObject::UpdateComponent()
{
	for (int x = 0; x < componentNames.size(); x++)
	{
		std::string comp = componentNames[x];
		void* cmp = (void*)(componentList[x]);

		if (comp == "Interactive_Breakable")
		{
			
		}
		else if (comp == "EntityMain")
		{
			EntityMain* ent = (EntityMain*)(cmp);
			ent->Loop();
		}
	}
}

#include "Input.h"
void GameObject::UpdateModel(std::string p, std::string n)
{
	if (modelAnmPath == p && modelAnmName == n) return;

	modelPath = p;
	modelName = n;

	char* ay = (char*)(modelPath.c_str());
	char* on = (char*)(modelName.c_str());

	//cout << "GameObject :: Changing model " << n << " in " << name << endl;

	if (modelPath != "" && modelName != "")
	{
		LuaHook::fc_ccCreateCastByChunk((char*)name.c_str(), ay, on);
		LuaHook::fc_ccSetCastPosition((char*)name.c_str(), transform.position.x, transform.position.y, transform.position.z);
	}

	//cout << "GameObject :: Changed model " << n << " in " << name << endl;
}

void GameObject::UpdateAnim(std::string p, std::string n)
{
	if (modelAnmPath == p && modelAnmName == n) return;

	modelAnmPath = p;
	modelAnmName = n;

	if (modelPath != "" && modelAnmPath != "" && modelName != "" && modelAnmName != "")
	{
		LuaHook::fc_ccCreateCastByChunk((char*)name.c_str(), (char*)modelPath.c_str(), (char*)modelName.c_str());
		LuaHook::fc_ccSetCastMotion((char*)name.c_str(), (char*)modelAnmPath.c_str(), (char*)modelAnmName.c_str());
	}

	//cout << "GameObject :: Playing " << n << " in " << name << endl;
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

#include "InteractiveMain.h"
#include "Interactive_Examine.h"
void* GameObject::AddComponent(std::string comp)
{
	void* cmp = 0;

	if (comp == "InteractiveMain")
	{
		componentNames.push_back(comp);
		cmp = (void*)(new InteractiveMain((uintptr_t)(GameObject*)this));
		componentList.push_back((uintptr_t)cmp);
	}
	else if (comp == "Interactive_Examine")
	{
		componentNames.push_back(comp);
		cmp = (void*)(new Interactive_Examine((uintptr_t)(GameObject*)this));
		componentList.push_back((uintptr_t)cmp);
	}
	else if (comp == "EntityMain")
	{
		componentNames.push_back(comp);
		cmp = (void*)(new EntityMain((uintptr_t)(GameObject*)this));
		componentList.push_back((uintptr_t)cmp);
	}
	else if (comp == "Entity_Fireball")
	{
		componentNames.push_back(comp);
		cmp = (void*)(new Entity_Fireball((uintptr_t)(GameObject*)this));
		componentList.push_back((uintptr_t)cmp);
	}

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
	uintptr_t cmp = GetComponent(comp);
	int cmpI = GetComponentIndex(comp);
	if (cmp == 0) return;

	RemoveComponent(cmpI);

	cout << "destroyed comp str " << comp << endl;

	if (comp == "InteractiveMain")
	{
		delete (InteractiveMain*)cmp;
	}
	else if (comp == "Interactive_Examine")
	{
		delete (Interactive_Examine*)cmp;
	}
	else if (comp == "EntityMain")
	{
		delete (EntityMain*)cmp;
	}
	else if (comp == "Entity_Fireball")
	{
		delete (Entity_Fireball*)cmp;
	}
}

void GameObject::RemoveComponent(int index)
{
	if (index >= componentNames.size()) return;

	void* cmp = 0;
	cmp = (void*)componentList[index];
	std::string comp = componentNames[index];

	componentNames.erase(componentNames.begin() + index);
	componentList.erase(componentList.begin() + index);

	cout << "destroyed comp ind " << index << endl;

	if (comp == "InteractiveMain")
	{
		delete (InteractiveMain*)cmp;
	}
	else if (comp == "Interactive_Examine")
	{
		delete (Interactive_Examine*)cmp;
	}
	else if (comp == "EntityMain")
	{
		delete (EntityMain*)cmp;
	}
	else if (comp == "Entity_Fireball")
	{
		delete (Entity_Fireball*)cmp;
	}

	cout << "destroyed comp ind finished" << endl;
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
	for (int x = GameObject::gCount - 1; x >= 0; x--)
	{
		if (GameObject::gList[x] == 0)
		{
			GameObject::gList.erase(GameObject::gList.begin() + x);
			GameObject::gCount--;

			for (int a = x + 1; a < GameObject::gCount; a++)
			{
				GameObject * g = (GameObject*)(GameObject::gList[x]);
				g->internalid--;
			}
		}
	}

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