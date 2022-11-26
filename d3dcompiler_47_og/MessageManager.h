#pragma once
#include <vector>
#include <fstream>
#include "Common.h"
#include "ModManager.h"
#include <algorithm>

class MessageManager
{
public:
	struct Message
	{
		std::string messageId;
		std::string messageStr;
	};

	struct MessageCompare
	{
		bool const operator()(Message * a, Message * b)
		{
			return a->messageId[0] < b->messageId[0];
		}
	};

	static std::vector<Message*> messageList;
	static std::vector<int> letterIndex;

	static std::vector<std::string> ReadMessageFile(std::string _file)
	{
		std::ifstream f;
		f.open(_file);

		std::vector<std::string> Messages;
		std::string actual = "";
		while (!f.eof())
		{
			char a = f.get();

			if (a != 0x00)
			{
				actual = actual + a;
			}
			else
			{
				Messages.push_back(actual);
				actual = "";
			}
		}

		f.close();

		return Messages;
	}

	static void ParseMessageFile(std::string _file)
	{
		std::vector<std::string> msg = ReadMessageFile(_file);

		for (int x = 0; x + 1 < msg.size(); x = x + 2)
		{
			Message * m = new Message();
			m->messageId = msg[x];
			m->messageStr = msg[x + 1];

			messageList.push_back(m);
		}

		std::sort(messageList.begin(), messageList.end(), MessageCompare());
	}

	// Credits to GeeksforGeeks for string search function
	static int SearchMessageId(std::string message, int first, int last)
	{
		if (first > last) return -1;

		int mid = (last + first) / 2;

		if (messageList[mid]->messageId == message)
		{
			return mid;
		}

		if (messageList[mid]->messageId < message)
		{
			return SearchMessageId(message, mid + 1, last);
		}

		return SearchMessageId(message, first, mid - 1);
	}

	static const char* GetMessage(const char * id)
	{
		if (id == 0)
		{
			return "[nullmsg]";
		}

		int index = SearchMessageId(std::string(id), 0, messageList.size());

		// If not found
		if (index == -1)
		{
			return 0;
		}

		// If found
		std::string msg = messageList[index]->messageId;

		std::vector<char> copyofmsg(msg.begin(), msg.end());
		copyofmsg.push_back('\0');
		const char * c = &copyofmsg[0];

		return c;
	}

	static void PrintMessageList()
	{
		for (int x = 0; x < messageList.size(); x++)
		{
			std::cout << x << ": " << messageList[x]->messageId << " = \"" << messageList[x]->messageStr + "\"" << std::endl;
		}
	}

	static std::string GetModMessage()
	{
		std::string st = "<color red>NS4 Modding Framework</color> <color yellow>1.8-nightly-9.7.22-01:17</color> by Zealot Tomato\n\n";

		std::vector<Mod*> modList = ModManager::GetModList();
		int modCount = modList.size();

		if (modCount > 0)
		{
			st = st + "<color yellow>Mod List:</color>\n";

			for (int x = 0; x < modCount; x++)
			{
				st = st + "> " + modList[x]->title;
				if (modList[x]->author != "") st = st + " <color yellow>(" + modList[x]->author + ")</color>\n";
				else st = st + "\n";
			}

			st = st + "\n";
			st = st + "<color yellow>" + std::to_string(modCount) + " mods installed</color>";
		}
		else
		{
			st = st + "<color yellow>No mods installed</color>\n";
		}
		return st;
	}
};