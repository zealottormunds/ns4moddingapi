#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace moddingApi;
using namespace std;

namespace moddingApi
{
	class c3MNT
	{
	private:
		float maxSub;
		float totalSub;
		float playerSpeed;
		bool init;
		bool hasMDR;
	public:
		c3MNT(int c);
		void Loop(int pln);
	};
}