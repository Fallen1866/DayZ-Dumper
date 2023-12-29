#include "Framework.h"

int main() {

	if (!Boot::Load())
		printf("[Boot] Fatal error...\n");

}