#include "Framework.h"

int main() {

	if (!Boot::Load())
		printf("[Boot] Fatal error...\n");

	if (!g_Updater->Scan())
		printf("[Updater] Pattern failed...\n");

	g_Updater->Clean();

	getchar();

}