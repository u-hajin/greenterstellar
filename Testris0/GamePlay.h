#pragma once
#include "GameData.h"

enum
{
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

class GamePlay
{
private:
	int level;    //레벨
	int ab_x, ab_y;   //화면중 블럭이 나타나는 좌표의 절대위치
	int block_shape, block_angle, block_x, block_y;   //현재 떨어지는 블럭의 정보(종류, 회전상태, 좌표)
	int next_block_shape;   //다음블럭모양
	int score;   //점수
	int lines;   //깬 줄

	char total_block[21][14];      //화면에 표시되는 블럭들
	char block[7][4][4][4] = {
		//막대모양
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//네모모양
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'ㅓ' 모양
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,   1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,   0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄱ'모양
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,   1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,   0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄴ' 모양
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,   1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,   1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' 모양
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,   1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,   0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' 모양
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,   0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0
	};
	char fireblock[3][3] = { 1,1,1,1,1,1,1,1,1 };
	int wind, ice, fire, earth; // 능력 잔여 횟수
	int shadow_y; // 잔상변수
	HDC hdc;
	GameData** game_data;

public:
	int play();
	int gotoxy(int x, int y);   //커서옮기기
	void SetColor(int color);   //색표현
	int init();               //각종변수 초기화 
	int show_cur_block(int shape, int angle, int x, int y);   //진행중인 블럭을 화면에 표시한다
	int erase_cur_block(int shape, int angle, int x, int y);   //블럭 진행의 잔상을 지우기 위한 함수
	int show_total_block();   //쌓여져있는 블럭을 화면에 표시한다.
	int show_next_block(int shape);   //다음 블럭 표시
	int make_new_block();   //return값으로 block의 모양번호를 알려줌
	int strike_check(int shape, int angle, int x, int y);   //블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴
	int merge_block(int shape, int angle, int x, int y);   //블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
	int block_start(int& angle, int& x, int& y);   //블럭이 처음 나올때 위치와 모양을 알려줌
	int move_block(int& shape, int& angle, int& x, int& y, int& next_shape);   //게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
	int input_data();
	int show_gameover();
	int show_gamestat(); //스테이지, 점수, 줄 수 출력
	int check_full_line();   //한 줄이 채워졌는지 확인하고 채워졌으면 없앰

	// 능력 추가 함수 부분
	int use_Earth();
	void use_fire();
	void show_fireblock(int& x, int& y);
	void erase_fireblock(int& x, int& y);
	bool fire_strike(int& x, int&y);
	void SetAbility();    // 레벨에 따라 능력 쓰는 횟수 조정
	void showProgress();
	void draw_image(const char* str, const int& nXDest, const int& nYDest, const int& nWidth, const int& nHeight);
	void shadow(int& shadow_y);
	int show_cur_block2(int shape, int angle, int x, int y);
	GamePlay();
	~GamePlay();

	void mix_block();
	int show_colorful_block(int shape, int angle, int x, int y);
	int waterfill();
	int erase_cur_block2(int shape, int angle, int x, int y);

};

