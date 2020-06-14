#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//using namespace moddingApi;
//using namespace std;

namespace moddingApi
{
	class c3MNT
	{
	private:
		static float maxSub;
		static float totalSub;
		static float playerSpeed;
		static bool init;
		static bool hasMDR;
	public:
		c3MNT(int c);
		static void Loop(int pln);
	};
}