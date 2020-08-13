#include "GameMath.h"
#include "ccGeneralGameFunctions.h"

using namespace std;
using namespace moddingApi;

#define PI 3.14159265

float GameMath::DegToRad(float deg)
{
	return deg * (PI / 180);
}

float GameMath::RadToDeg(float rad)
{
	return rad * (180 / PI);
}

int GameMath::FrameToFps(int f)
{
	if (ccGeneralGameFunctions::GetFPS() == 30) return f / 2;
	else return f;
}