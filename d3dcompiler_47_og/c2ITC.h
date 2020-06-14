#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//using namespace moddingApi;
//using namespace std;

namespace moddingApi
{
	class c2ITC
	{
	private:
		static int chakraCharge;

		// UJ
		static bool effectEnabled;
		static float originalMoveSpeed;
		static float originalAnmSpeed;
		static float prevEnemyHealth;
		static bool doneAwk;
		static bool doneUj;
		static int frameCounterForUj;
		static float removedLifeEffect;
		static float playerSpeed;
		static int framesToDoCU1;

		// Amaterasu
		static int framesToDoCD1;
		static int cd1_enableEffect;
	public:
		c2ITC(int c);
		static void Loop(int pln);
	};
}