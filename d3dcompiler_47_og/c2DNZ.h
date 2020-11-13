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
		float totalSub;
		float maxSub;
		int subsLeft;
		bool init;
		int prevState;
		float prevSub;
	public:
		c2DNZ(int c);
		void Loop(int pln);
	};
}