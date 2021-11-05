#include <iostream>
#include "GameUI.h"
using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	GameUI GUI;
	GUI.SetCursorView(0);
	GUI.show_logo();
	return 0;
}