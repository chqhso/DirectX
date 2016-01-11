#include "Application.h"
#include "GameApplication.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT){
	Application* app = new GameApplication(hInst);
	app->run();
}