#include "Interactive_Examine.h"

using namespace std;
using namespace moddingApi;

void Interactive_Examine::StartAction()
{

}

void Interactive_Examine::AddText(uintptr_t msg1, uintptr_t msg2)
{
	message1Ptr.push_back(msg1);
	message2Ptr.push_back(msg2);
}