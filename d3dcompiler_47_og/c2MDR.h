#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//using namespace moddingApi;
//using namespace std;

namespace moddingApi
{
	class c2MDR
	{
	private:
		static float maxSub;
		static float totalSub;
		static float playerSpeed;
		static bool init;
		static bool hasMNT;
	public:
		c2MDR(int c);
		static void Loop(int pln);
	};
}