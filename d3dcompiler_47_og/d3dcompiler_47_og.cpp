#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "d3dcompiler_47_og.h"
#include "ccMain.h"

using namespace moddingApi;
using namespace std;

uintptr_t d3dcompiler_47_og::moduleBase;
uintptr_t d3dcompiler_47_og::st_hModule;
uintptr_t d3dcompiler_47_og::datasection;

HINSTANCE mHinst = 0, mHinstDLL = 0;
extern "C" UINT_PTR mProcs[29] = { 0 };

LPCSTR mImportNames[] = { "D3DAssemble", "D3DCompile", "D3DCompile2", "D3DCompileFromFile", "D3DCompressShaders", "D3DCreateBlob", "D3DCreateFunctionLinkingGraph", "D3DCreateLinker", "D3DDecompressShaders", "D3DDisassemble", "D3DDisassemble10Effect", "D3DDisassemble11Trace", "D3DDisassembleRegion", "D3DGetBlobPart", "D3DGetDebugInfo", "D3DGetInputAndOutputSignatureBlob", "D3DGetInputSignatureBlob", "D3DGetOutputSignatureBlob", "D3DGetTraceInstructionOffsets", "D3DLoadModule", "D3DPreprocess", "D3DReadFileToBlob", "D3DReflect", "D3DReflectLibrary", "D3DReturnFailure1", "D3DSetBlobPart", "D3DStripShader", "D3DWriteBlobToFile", "DebugSetMute" };
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved, HMODULE hModule) {
	mHinst = hinstDLL;
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		mHinstDLL = LoadLibrary("d3dcompiler_47_o.dll");
		if (!mHinstDLL)
			return (FALSE);
		for (int i = 0; i < 29; i++)
			mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);

		d3dcompiler_47_og::st_hModule = (uintptr_t)hModule;
		d3dcompiler_47_og::moduleBase = (uintptr_t)GetModuleHandle(NULL) + 0xC00;
		d3dcompiler_47_og::datasection = (uintptr_t)GetModuleHandle(NULL) + 0x13B6000;
		// 7FF716C86000+1416bdd10

		// Start API
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ccMain::Main, hModule, 0, nullptr));
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		FreeLibrary(mHinstDLL);
	}

	return (TRUE);
}

uintptr_t d3dcompiler_47_og::RecalculateAddress(uintptr_t a)
{
	uintptr_t recalc = d3dcompiler_47_og::moduleBase + a;

	if (a > 0x13A38AD) recalc += 0x400;
	else if (a > 0xEA7420) recalc += 0x400;

	return recalc;
}

extern "C" void D3DAssemble_wrapper();
extern "C" void D3DCompile_wrapper();
extern "C" void D3DCompile2_wrapper();
extern "C" void D3DCompileFromFile_wrapper();
extern "C" void D3DCompressShaders_wrapper();
extern "C" void D3DCreateBlob_wrapper();
extern "C" void D3DCreateFunctionLinkingGraph_wrapper();
extern "C" void D3DCreateLinker_wrapper();
extern "C" void D3DDecompressShaders_wrapper();
extern "C" void D3DDisassemble_wrapper();
extern "C" void D3DDisassemble10Effect_wrapper();
extern "C" void D3DDisassemble11Trace_wrapper();
extern "C" void D3DDisassembleRegion_wrapper();
extern "C" void D3DGetBlobPart_wrapper();
extern "C" void D3DGetDebugInfo_wrapper();
extern "C" void D3DGetInputAndOutputSignatureBlob_wrapper();
extern "C" void D3DGetInputSignatureBlob_wrapper();
extern "C" void D3DGetOutputSignatureBlob_wrapper();
extern "C" void D3DGetTraceInstructionOffsets_wrapper();
extern "C" void D3DLoadModule_wrapper();
extern "C" void D3DPreprocess_wrapper();
extern "C" void D3DReadFileToBlob_wrapper();
extern "C" void D3DReflect_wrapper();
extern "C" void D3DReflectLibrary_wrapper();
extern "C" void D3DReturnFailure1_wrapper();
extern "C" void D3DSetBlobPart_wrapper();
extern "C" void D3DStripShader_wrapper();
extern "C" void D3DWriteBlobToFile_wrapper();
extern "C" void DebugSetMute_wrapper();