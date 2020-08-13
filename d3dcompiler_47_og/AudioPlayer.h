#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H
#pragma once

#include <WinSock2.h>
#include <xaudio2.h>

namespace moddingApi
{
	class AudioPlayer
	{
	public:
		HRESULT Initialize();
		HRESULT MasteringVoice();

	};
}

#endif