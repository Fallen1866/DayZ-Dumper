#include "Framework.h"

bool Boot::Load() {

	if (!g_Coms->Init(g_TargetProcess)) {
		printf("[Boot] Failed to init communication...\n");
		return false;
	}

	g_Game = g_Coms->GetModule(L"DayZ_x64.exe");

	if (!g_Game) {
		printf("[Boot] Failed to get game...\n");
		return false;
	}

	if (!g_Updater->Init(&g_Game)) {
		printf("[Boot] Failed to init updater...\n");
		return false;
	}

	return true;
}

bool Boot::Unload() {


	return false;
}
