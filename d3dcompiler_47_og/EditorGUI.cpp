#include "EditorGUI.h"
#include <sstream>

#include "DirectX.h"
#include "FileParser.h"
#include "NS4Framework.h"
#include "Common.h"

bool EditorGUI::Show = false;
bool EditorGUI::showHelpWindow = false;

void EditorGUI::LoopGUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (Show)
	{
		// Call own GUI
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Framework"))
		{
			if (ImGui::MenuItem("Plugin Manager", "")) { showReloadWindow = true; }
			if (ImGui::MenuItem("About...", "")) { showHelpWindow = true; }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		if (showHelpWindow)
		{
			ImGui::Begin("Framework Help", &showHelpWindow);
			ImGui::TextWrapped("Storm Framework by Zealot Tormunds.\nDear ImGui by ocornut.");
			ImGui::End();
		}

		if (showReloadWindow) ReloadWindow();
	}

	// Call plugin GUI
	NS4Framework::OnGUI(Show, (__int64)(DirectX::theWindow), (__int64)(DirectX::guiContext));

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

bool EditorGUI::showReloadWindow = false;

#include "ModManager.h"

int EditorGUI::selectedMod = -1;
int EditorGUI::selectedPlugin = -1;
void EditorGUI::ReloadWindow()
{
	ImVec2 tempSize = ImVec2(500, 190);
	ImGui::SetNextWindowSize(tempSize);

	ImGui::Begin("Plugin Manager", &showReloadWindow);

	std::vector<Mod*> mList = ModManager::GetModList();
	int totalPlugin = 0;

	if (ImGui::ListBoxHeader("Loaded Plugins"))
	{
		for (int x = 0; x < mList.size(); x++)
		{
			for (int y = 0; y < mList[x]->pluginList.size(); y++)
			{
				Plugin * p = mList[x]->pluginList[y];
				if (ImGui::Selectable(p->pluginName.c_str(), selectedMod == x && selectedPlugin == y))
				{
					selectedMod = x;
					selectedPlugin = y;
				}

				totalPlugin++;
			}
		}

		ImGui::ListBoxFooter();
	}

	if (selectedMod != -1 && selectedPlugin != -1)
	{
		Plugin * p = mList[selectedMod]->pluginList[selectedPlugin];

		if (p->hInstance != 0)
		{
			if (ImGui::Button("Disable Plugin"))
			{
				p->FreePlugin();
			}
		}
		else
		{
			if (ImGui::Button("Enable Plugin"))
			{
				p->ReloadLibrary();
			}
		}
	}

	ImGui::End();

	/*ImGui::Begin("File Reload", &showReloadWindow);

	if (gameVersion != "1.09")
	{
		ImGui::TextWrapped("This function is not available.");
		ImGui::End();
		return;
	}

	ImGui::TextWrapped("You can use this window to reload certain files from the game.");
	ImGui::End();*/
}