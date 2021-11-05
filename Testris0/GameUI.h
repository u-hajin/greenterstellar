#pragma once
#include "GamePlay.h"

class GameUI
{
private:
	GamePlay * Gp;   //테트리스를 실행할 때 이용
	HDC hdc;
	int dialog_X = 3, dialog_Y = 21;

public:
	GameUI();
	~GameUI();

	enum {
		BLACK,      /*  0 : 까망 */
		DARK_BLUE,    /*  1 : 어두운 파랑 */
		DARK_GREEN,    /*  2 : 어두운 초록 */
		DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
		DARK_RED,    /*  4 : 어두운 빨강 */
		DARK_VOILET,  /*  5 : 어두운 보라 */
		DARK_YELLOW,  /*  6 : 어두운 노랑 */
		GRAY,      /*  7 : 회색 */
		DARK_GRAY,    /*  8 : 어두운 회색 */
		BLUE,      /*  9 : 파랑 */
		GREEN,      /* 10 : 초록 */
		SKY_BLUE,    /* 11 : 하늘 */
		RED,      /* 12 : 빨강 */
		VIOLET,      /* 13 : 보라 */
		YELLOW,      /* 14 : 노랑 */
		WHITE,      /* 15 : 하양 */
	};

	void gotoxy(int x, int y);   //커서옮기기
	void SetColor(int color);   //색표현
	void SetCursorView(bool visible); // 커서 지우기

	int show_logo();
	void show_default_dialog(const int x, const int y);
	void show_npc_dialog(const char* npc, const char* comment, int npc_x = 0);

	void draw_image(const char* str, const int& nXDest, const int& nYDest, const int& nWidth, const int& nHeight);

	void show_story();
	void show_dialog(const char * comment, const int & x, const int & y);
	void show_manual();
	void draw_spaceship(int& level);

};