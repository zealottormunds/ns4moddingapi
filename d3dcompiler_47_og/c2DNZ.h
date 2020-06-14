#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//using namespace moddingApi;
//using namespace std;

namespace moddingApi
{
	class c2DNZ
	{
	private:
		static float totalSub = 25;
		static float maxSub = 250;
		static int subsLeft = 10;
		static bool init = false;
		static int prevState = -1;
		static float prevSub = 0;
	public:
		c2DNZ(int c);
		static void Loop(int pln);
	};
}