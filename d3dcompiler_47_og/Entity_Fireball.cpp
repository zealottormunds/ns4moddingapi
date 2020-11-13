#include <stdio.h>
#include <windows.h>

#include "Entity_Fireball.h"
#include "InteractiveMain.h"
#include "GameObject.h"
#include "BoxCollider.h"

using namespace std;
using namespace moddingApi;

void Entity_Fireball::Loop()
{
	GameObject* thisG = (GameObject*)gameObjectPtr;

	for (int x = 0; x < GameObject::gCount; x++)
	{
		if (GameObject::gList[x] != 0 && ((GameObject*)GameObject::gList[x])->enabled)
		{
			GameObject* g = (GameObject*)GameObject::gList[x];
			uintptr_t c = g->GetComponent("InteractiveMain");

			if (c != 0)
			{
				//cout << "has interaction " << endl;

				InteractiveMain* i = (InteractiveMain*)c;
				if (i->interaction == InteractiveMain::Breakable)
				{
					if (BoxCollider::isColliding(thisG->rigidbody.collider, g->rigidbody.collider))
					{

					}
				}
			}
			else
			{
				//cout << "no interaction " << c << endl;
			}
		}
	}
}