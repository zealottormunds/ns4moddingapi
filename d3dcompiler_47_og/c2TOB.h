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
		float maxSub;
		float totalSub;
		bool init;
	public:
		c2TOB(int c);
		void Loop(int pln);
	};
}