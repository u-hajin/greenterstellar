#include "GameData.h"
#pragma comment(lib, "winmm.lib")
GameData::GameData()
	:speed(0), stick_rate(0), clear_line(0)
{
}

GameData::GameData(int _speed, int _stick_rate, int _clear_line)
	: speed(_speed), stick_rate(_stick_rate), clear_line(_clear_line)
{
}

void GameData::setspeed(int s)
{
	speed = s;
}

void GameData::setstickrate(int stickrate)
{
	stick_rate = stickrate;
}

void GameData::setclearline(int clearline)
{
	clear_line = clearline;
}

GameData::~GameData()
{
}
