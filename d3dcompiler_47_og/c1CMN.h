#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//using namespace moddingApi;
//using namespace std;

namespace moddingApi
{
	class c1CMN
	{
	public:
		c1CMN(int c);
		static void PreLoop(int pln);
		static void PostLoop(int pln);
		static int GetPointers(ccPlayer c, int pl, int en);
	};
}