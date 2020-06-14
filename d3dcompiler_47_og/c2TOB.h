#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//using namespace moddingApi;
//using namespace std;

namespace moddingApi
{
	class c2TOB
	{
	private:
		static float maxSub;
		static float totalSub;
		static bool init;
	public:
		c2TOB(int c);
		static void Loop(int pln);
	};
}