#include <iostream>
#include "Engine.h"

using namespace std;
int main() {
#if _WIN64
	std::cout << "AORIA ON WINDOWS (64BIT)" << std::endl;
#else
	std::cerr << "NOT 64 BIT WINDOWS! [App is only 64 bit]]" << std::endl;
#endif
	Engine *engine = new Engine();
	engine->loadGame();
	delete engine;
#if _DEBUG
	cout << "Session end!" << endl;
#endif
	return 0;
}