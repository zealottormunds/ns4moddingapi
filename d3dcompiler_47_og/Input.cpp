/*#include "Input.h"
#include <stdio.h>
#include <Windows.h>

using namespace std;
using namespace moddingApi;

void Input::UpdateKeys()
{
	for (int x = 0; x < 0xFF; x++)
	{
		Input::pressedKeysPrev[x] = Input::pressedKeys[x];
		Input::pressedKeys[x] = (GetKeyState(x) < 0);
	}
}

bool Input::GetKeyDown(char k)
{
	if (Input::pressedKeys[k] && !Input::pressedKeysPrev[k]) return true;
	else return false;
}

bool Input::GetKey(char k)
{
	if (Input::pressedKeys[k]) return true;
	else return false;
}

bool Input::GetKeyUp(char k)
{
	if (Input::pressedKeysPrev[k] && !Input::pressedKeys[k]) return true;
	else return false;
}

bool Input::pressedKeys[0xFF]{ 0 };
bool Input::pressedKeysPrev[0xFF]{ 0 };
*/