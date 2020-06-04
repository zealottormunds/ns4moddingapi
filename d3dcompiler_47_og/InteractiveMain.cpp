#include <stdio.h>
#include <windows.h>

#include "GameObject.h"
#include "InteractiveMain.h"
#include "Interactive_Examine.h"

using namespace std;
using namespace moddingApi;

void InteractiveMain::StartAction()
{
	GameObject* gameObject = (GameObject*)(gameObjectPtr);
	uintptr_t componentPtr = 0;

	switch (interaction)
	{
	case InteractiveType::Examine:
	{
		componentPtr = gameObject->GetComponent("Interactive_Examine");
		Interactive_Examine* examine = (Interactive_Examine*)(componentPtr);
		examine->StartAction();
		break;
	}
	}
}

void InteractiveMain::StartActionAlt()
{
	GameObject* gameObject = (GameObject*)(gameObjectPtr);
	uintptr_t componentPtr = 0;

	/*switch (interaction)
	{
	case InteractiveType::Breakable:
	{
		componentPtr = gameObject->GetComponent("Interactive_Breakable");
		Interactive_Breakable* breakable = (Interactive_Breakable*)(componentPtr);
		breakable->StartBreak();
		break;
	}
	}*/
}