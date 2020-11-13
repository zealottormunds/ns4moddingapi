#pragma once

#include <vector>
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