#include <stdio.h>
#include <windows.h>

#include "GameObject.h"
#include "InteractiveMain.h"
#include "EntityMain.h"
#include "Entity_Fireball.h"

using namespace std;
using namespace moddingApi;

void EntityMain::Loop()
{
	GameObject* gameObject = (GameObject*)(gameObjectPtr);
	uintptr_t componentPtr = 0;

	switch (entity)
	{
	case EntityType::Fireball:
	{
		componentPtr = gameObject->GetComponent("Entity_Fireball");
		Entity_Fireball* fireball = (Entity_Fireball*)(componentPtr);
		fireball->Loop();
	}
	break;
	}
}