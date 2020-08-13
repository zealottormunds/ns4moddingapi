#include <WinSock2.h>
#include "AudioPlayer.h"

// Windows Media Foundation
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#include <vector>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

using namespace std;
using namespace moddingApi;

// This code is unfinished.

HRESULT AudioPlayer::Initialize()
{
	IXAudio2* pXAudio2 = NULL;
	HRESULT hr;
	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		return hr;

	IXAudio2MasteringVoice* pMasterVoice = NULL;
	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
		return hr;
}