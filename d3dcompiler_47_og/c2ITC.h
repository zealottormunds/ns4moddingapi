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
		int chakraCharge;

		// UJ
		bool effectEnabled;
		float originalMoveSpeed;
		float originalAnmSpeed;
		float prevEnemyHealth;
		bool doneAwk;
		bool doneUj;
		int frameCounterForUj;
		float removedLifeEffect;
		float playerSpeed;
		int framesToDoCU1;

		// Amaterasu
		int framesToDoCD1;
		int cd1_enableEffect;
	public:
		c2ITC(int c);
		void Loop(int pln);
	};
}