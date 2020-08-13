#ifndef GAMEMATH_H 
#define GAMEMATH_H
#pragma once

namespace moddingApi
{
	class GameMath
	{
	public:
		static float DegToRad(float deg);
		static float RadToDeg(float rad);
		static int FrameToFps(int f);
	};
}

#endif