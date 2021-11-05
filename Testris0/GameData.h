#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <string.h>
#include <Windows.h> //Game.h
#include <string>
#include <time.h>
using namespace std;

#define EXT_KEY         0xffffffe0   //확장키 인식값 
#define KEY_LEFT        0x4b
#define KEY_RIGHT       0x4d
#define KEY_UP          0x48
#define KEY_DOWN        0x50
#define KEY_ESC         0x1B
#define KEY_EARTH		52

class GameData
{
private:
	int speed;   //숫자가 낮을수록 속도가 빠르다
	int stick_rate;      //막대가 나오는 확률 0~99 , 99면 막대기만 나옴
	int clear_line;      //레벨을 클리어하기 위해 없애야 하는 줄 수

public:
	void setspeed(int s);
	void setstickrate(int stickrate);
	void setclearline(int clearline);
	int getspeed() { return speed; };
	int getstickrate() { return stick_rate; };
	int getclearline() { return clear_line; };
	GameData();
	GameData(int _speed, int _stick_rate, int _clear_line);
	~GameData();
};

