#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace moddingApi;
using namespace std;

namespace moddingApi
{
	class c2MDR
	{
	private:
		float maxSub;
		float totalSub;
		float playerSpeed;
		bool init;
		bool hasMNT;
	public:
		c2MDR(int c);
		void Loop(int pln);
	};
}