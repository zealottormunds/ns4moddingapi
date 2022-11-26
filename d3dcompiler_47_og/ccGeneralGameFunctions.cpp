#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Common.h"
/*#pragma comment(lib, "XInput.lib")
#include <Xinput.h>*/

#include "ccGeneralGameFunctions.h"
#include "HookFunctions.h"
#include "ModManager.h"
#include "MessageManager.h"

using namespace moddingApi;
using namespace std;

char * ccGeneralGameFunctions::MessageToString(char * msg)
{
	typedef char *(__fastcall * message_to_string)(char *);
	message_to_string g_MessageToString;
	g_MessageToString = (message_to_string)(moduleBase + HookFunctions::fc_msgtostring);
	return g_MessageToString(msg);
}

// All custom messageinfo functions
char ccGeneralGameFunctions::ViewMessageConversions = 0;

uintptr_t ccGeneralGameFunctions::Hook_MsgToString(uintptr_t MessageToDecode)
{
	if (ccGeneralGameFunctions::ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		if (isDebug == false) HookFunctions::UndoMessageInfoHook(19);
		else HookFunctions::UndoMessageInfoHook(14);

		char* result = ccGeneralGameFunctions::MessageToString((char*)MessageToDecode);

		if (isDebug == false) HookFunctions::DoMessageInfoHook(19);
		else HookFunctions::DoMessageInfoHook(14);

		if (MessageToDecode != 0)
		{
			bool finished = false;

			string message((char*)MessageToDecode);

			if (message == "network_agreement_EU_s-A" || message == "network_agreement_s-A")
			{
				result = (char*)MessageManager::GetModMessage().c_str();
				finished = true;
			}
			else if (message == "network_agreementp2_EU_s-A" || message == "network_agreementp2_s-A")
			{
				result = "";
				finished = true;
			}

			if (finished == false)
			{
				std::string msg = (std::string)(char*)MessageToDecode;

				if (msg == "network_agreement_select") result = "Press any button to continue";
				else if (msg == "network_agreement_ok") result = "";
				else if (msg == "network_agreement_ng") result = "<icon btn_2 />";
				else
				{
					/*for (int x = 0; x < MessageManager::MessageID.size(); x++)
					{
						if (msg == MessageManager::MessageID[x])
						{
							result = (char*)MessageManager::MessageStr[x].c_str();
						}
					}*/
				}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}
		}

		return (uintptr_t)result;
	}
	else
	{
		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}

typedef char *(__fastcall * message_to_string2)(char *);
message_to_string2 g_MessageToString2;

uintptr_t ccGeneralGameFunctions::Hook_MsgToString_Alt(uintptr_t MessageToDecode)
{
	g_MessageToString2 = (message_to_string2)(moduleBase + HookFunctions::fc_msgtostring_3);

	if (ccGeneralGameFunctions::ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		if(isDebug == false) HookFunctions::UndoMessageInfoHook2(19);
		else HookFunctions::UndoMessageInfoHook2(14);

		char* result = g_MessageToString2((char*)MessageToDecode);

		if (isDebug == false) HookFunctions::DoMessageInfoHook2(19);
		else HookFunctions::UndoMessageInfoHook2(14);

		if (MessageToDecode != 0)
		{
			bool finished = false;

			string message((char*)MessageToDecode);

			if (message == "network_agreement_EU_s-A" || message == "network_agreement_s-A")
			{
				result = (char*)MessageManager::GetModMessage().c_str();
				finished = true;
			}
			else if (message == "network_agreementp2_EU_s-A" || message == "network_agreementp2_s-A")
			{
				result = "";
				finished = true;
			}

			if (finished == false)
			{
				std::string msg = (std::string)(char*)MessageToDecode;

				if (msg == "network_agreement_select") result = "Press any button to continue";
				else if (msg == "network_agreement_ok") result = "";
				else if (msg == "network_agreement_ng") result = "<icon btn_2 />";
				else
				{
					/*for (int x = 0; x < MessageManager::MessageID.size(); x++)
					{
						if (msg == MessageManager::MessageID[x])
						{
							result = (char*)MessageManager::MessageStr[x].c_str();
						}
					}*/
				}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}
		}

		return (uintptr_t)result;
	}
	else
	{

		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}