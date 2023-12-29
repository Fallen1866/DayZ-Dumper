#include "Framework.h"

bool Boot::Load() {

	if (!g_Coms->Init(g_TargetProcess)) {
		printf("[Boot] Failed to init communication...\n");
		return false;
	}

	

	return true;
}

bool Boot::Unload() {


	return false;
}
