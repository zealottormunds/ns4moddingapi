#pragma once

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"

class EditorGUI
{
public:
	static bool Show;
	static void LoopGUI();
	static bool showHelpWindow;

	static void ReloadWindow();
	static bool showReloadWindow;
	static int selectedMod;
	static int selectedPlugin;
};