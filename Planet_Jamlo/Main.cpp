#include <iostream>
#include "GameManager.h"

int main(int argc, char* argv[]) {

	GameManager * gm = new GameManager();

	if (!gm->Initialize()) {
		std::cout << "Error! Cannot initialize program." << std::endl;
		return 1;
	}

	gm->Run();
	
	return 0;
}