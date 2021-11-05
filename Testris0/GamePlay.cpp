#include "GamePlay.h"
#include <iostream>
using namespace std;

//
GamePlay::GamePlay()
	:game_data(new GameData*[7]), score(0)
{
	game_data[0] = new GameData(40, 20, 2);
	game_data[1] = new GameData(35, 18, 20);
	game_data[2] = new GameData(25, 16, 20);
	game_data[3] = new GameData(15, 14, 20);
	game_data[4] = new GameData(10, 13, 20);
	game_data[5] = new GameData(6, 12, 20);
	game_data[6] = new GameData(4, 11, 20);
	hdc = GetDC(FindWindow(TEXT("ConsoleWindowClass"), NULL));
}
//

GamePlay::~GamePlay()
{
	for (int i = 0; i < 7; i++)
		delete game_data[i];
	delete[] game_data;
	game_data = nullptr;
}

int GamePlay::play()
{
	int i, t = 0;
	int is_gameover = 0;
	char keytemp;
	bool firecheck = false;
	bool stop = false;
	bool reverse = false;
	int len = game_data[4]->getclearline();
	bool reverse_random[20] = { false , };   //delete
	len /= 3;   //총 3번의 reverse 버그
	for (int k = 0; k < 3; k++) {
		if (len != 0)
			reverse_random[(rand() % len) + (len*k)] = true;
	}
	init();


	while (true) //한 번의 게임오버
	{
		stop = false;
		time_t timer, start(0), end(0), start2(0), end2(0);
		struct tm* t;
		show_total_block();
		block_shape = make_new_block();
		next_block_shape = make_new_block();
		show_next_block(next_block_shape);
		block_start(block_angle, block_x, block_y);
		show_gamestat();
		showProgress();

		if (level == 3)
			stop = true;


		for (i = 1; 1; i++)      //i가 int 값을 넘어가면??
		{
			if (level == 4) {   //추가
				if (reverse) show_colorful_block(block_shape, block_angle, block_x, block_y);
			}

			if (level > 3)
				shadow(shadow_y);

			if (level == 3 && stop == true) {
				timer = time(NULL);
				t = localtime(&timer);
				start2 = t->tm_sec;
				stop = false;
			}
			if (end - start >= 3 || end - start < -3) // 블럭이 멈추고 3초 지나면 stop을 false로
				stop = false;
			if (_kbhit())
			{
				keytemp = _getch();
				if (keytemp == EXT_KEY)
				{
					keytemp = _getch();
					if (reverse)
					{
						if (keytemp == KEY_LEFT)
							keytemp = KEY_RIGHT;
						else if (keytemp == KEY_RIGHT)
							keytemp = KEY_LEFT;
					}
					switch (keytemp)
					{
					case KEY_UP:      //회전하기

						if (strike_check(block_shape, (block_angle + 1) % 4, block_x, block_y) == 0)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							if (level > 3)
								erase_cur_block(block_shape, block_angle, block_x, shadow_y);
							block_angle = (block_angle + 1) % 4;
							show_cur_block(block_shape, block_angle, block_x, block_y);
							if (level > 3) {
								shadow(shadow_y);
								erase_cur_block(block_shape, block_angle, block_x, shadow_y);
								show_cur_block2(block_shape, block_angle, block_x, shadow_y);
							}
						}
						else {
							if (block_shape == 0) {         //막대 모양일 경우
								for (int take = 1; take <= 3; take++) {
									if (strike_check(block_shape, (block_angle + 1) % 4, block_x - take, block_y) == 0) {
										erase_cur_block(block_shape, block_angle, block_x, block_y);

										if (level > 3)
											erase_cur_block(block_shape, block_angle, block_x, shadow_y);
										block_angle = (block_angle + 1) % 4;
										block_x -= take;
										show_cur_block(block_shape, block_angle, block_x, block_y);
										if (level > 3) {
											shadow(shadow_y);
											erase_cur_block(block_shape, block_angle, block_x, shadow_y);
											show_cur_block2(block_shape, block_angle, block_x, shadow_y);
										}
										break;
									}
								}
							}
							else {
								if (strike_check(block_shape, (block_angle + 1) % 4, block_x - 1, block_y) == 0) {
									//x좌표를 왼쪽으로 한칸 옮겼을 경우에도 strick_check 가 0 반환하면 x좌표를 바꿔주고 회전하기
									erase_cur_block(block_shape, block_angle, block_x, block_y);
									if (level > 3)
										erase_cur_block(block_shape, block_angle, block_x, shadow_y);
									block_angle = (block_angle + 1) % 4;
									show_cur_block(block_shape, block_angle, --block_x, block_y);
									if (level > 3) {
										shadow(shadow_y);
										erase_cur_block(block_shape, block_angle, block_x, shadow_y);
										show_cur_block2(block_shape, block_angle, block_x, shadow_y);
									}
								}
							}
						}
						if (level == 4) {   //추가   //회전 했을 때 버그 발생 & 버그 취소
							if (reverse_random[lines]) {
								reverse = true;
							}
							else reverse = false;
						}
						break;
					case KEY_LEFT:      //왼쪽으로 이동
						if (block_x > 1)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							if (level > 3)
								erase_cur_block(block_shape, block_angle, block_x, shadow_y);
							block_x--;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x++;
							if (level > 3)
							{
								shadow(shadow_y);
								show_cur_block2(block_shape, block_angle, block_x, shadow_y);
							}
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_RIGHT:      //오른쪽으로 이동
						if (block_x < 14)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							if (level > 3)
								erase_cur_block(block_shape, block_angle, block_x, shadow_y);
							block_x++;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x--;
							if (level > 3) {
								shadow(shadow_y);
								show_cur_block2(block_shape, block_angle, block_x, shadow_y);
							}
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_DOWN:      //아래로 이동
						if (stop == false)
						{ // 블럭이 멈췄을 때 아래로 이동 막기위함.
							is_gameover = move_block(block_shape, block_angle, block_x, block_y, next_block_shape);
							if (level > 3)
								show_cur_block2(block_shape, block_angle, block_x, shadow_y);
							show_cur_block(block_shape, block_angle, block_x, block_y);

							break;

						}
					}
				}
				if (keytemp == 32)   //스페이스바를 눌렀을때
				{
					while (is_gameover == 0)
					{
						is_gameover = move_block(block_shape, block_angle, block_x, block_y, next_block_shape);
					}
					show_cur_block(block_shape, block_angle, block_x, block_y);
					if (stop == true)
						stop = false;
				}

				if (keytemp == KEY_ESC)
				{
					continue;
				}

				//바람 능력 : 현재 블록 날리고 다음 블록 나온다
				//키보드 '1'을 눌렀을 때
				if (keytemp == 49) {
					if (level > 2 && wind != 0) {
						PlaySound(TEXT("sound//wind.wav"), NULL, SND_FILENAME | SND_ASYNC);
						erase_cur_block(block_shape, block_angle, block_x, block_y);
						if (level > 3)
							erase_cur_block(block_shape, block_angle, block_x, shadow_y);
						block_shape = next_block_shape;
						next_block_shape = make_new_block();

						block_start(block_angle, block_x, block_y);
						show_next_block(next_block_shape);
						show_cur_block(block_shape, block_angle, block_x, block_y);
						if (level > 3)
							shadow(shadow_y);
						wind--;
						show_gamestat();
					}
				}
				// 나중에 조건으로 사용할 수 있는 횟수 정해놓기
				if (keytemp == 50) // 2번키 눌렀을 때
				{
					if (level > 3 && ice != 0) {
						PlaySound(TEXT("sound//ice.wav"), NULL, SND_FILENAME | SND_ASYNC);
						stop = true;
						timer = time(NULL); // 현재 시간받아옴.
						t = localtime(&timer); // 초 단위의 시간 분리해서 구조체에 넣기
						start = t->tm_sec; // start값을 2번키 눌렀을 때의 초로 초기화해줌.
						ice--;
						show_gamestat();
					}
				}

				if (keytemp == 51) {   //3번 키
					if (level > 4 && fire != 0) {
						bool f = false;
						for (int k = 0; k < 3; k++) {
							for (int m = 1; m <= 12; m++) {
								if (total_block[k][m] == 1) {
									f = true;
									break;
								}
							}
							if (f)break;
						}
						if (!f) {
							int x = 15, y = 1;
							show_fireblock(x, y);
							gotoxy((0 + x) * 2 + ab_x, 3 + y + ab_y);
							cout << " ";
							firecheck = true;
							fire--;
							show_gamestat();
						}

					}
				}
				if (keytemp == KEY_EARTH)
				{
					if (level > 5 && earth != 0) {
						erase_cur_block(block_shape, block_angle, block_x, shadow_y);
						use_Earth();
						earth--;
						show_gamestat();
					}
				}
			}
			if (is_gameover == 2 && firecheck)
			{
				if (level > 3)
					erase_cur_block(block_shape, block_angle, block_x, shadow_y);
				bool f = false;
				for (int k = 0; k < 3; k++) {
					for (int m = 1; m <= 12; m++) {
						if (total_block[k][m] == 1) {
							f = true;
							break;
						}
					}
					if (f)break;
				}
				if (!f) {
					next_block_shape = block_shape;
					show_next_block(next_block_shape);
					use_fire();
				}
				next_block_shape = make_new_block();
				block_start(block_angle, block_x, block_y);
				firecheck = false;
			}
			if (level == 5 && (i % 500 == 0))
			{
				mix_block();
			}
			if (level == 2) {
				if (i % 100 == 0) {
					if (strike_check(block_shape, (block_angle + 1) % 4, block_x, block_y) == 0)
					{
						erase_cur_block(block_shape, block_angle, block_x, block_y);
						block_angle = (block_angle + 1) % 4;
						show_cur_block(block_shape, block_angle, block_x, block_y);
					}
					else {
						if (block_shape == 0) {         //막대 모양일 경우
							for (int take = 1; take <= 3; take++) {
								if (strike_check(block_shape, (block_angle + 1) % 4, block_x - take, block_y) == 0) {
									erase_cur_block(block_shape, block_angle, block_x, block_y);
									block_angle = (block_angle + 1) % 4;
									block_x -= take;
									show_cur_block(block_shape, block_angle, block_x, block_y);
									break;
								}
							}
						}
					}
				}
			}
			if (stop == false) {
				if (i % game_data[level]->getspeed() == 0)
				{
					is_gameover = move_block(block_shape, block_angle, block_x, block_y, next_block_shape);
					if (level > 3)
						show_cur_block2(block_shape, block_angle, block_x, shadow_y);
					show_cur_block(block_shape, block_angle, block_x, block_y);

				}
			}
			if (game_data[level]->getclearline() <= lines)   //클리어 스테이지
			{
				level++;
				SetAbility(); // 레벨에 따라 능력 쓰는 횟수 조정
				lines = 0;
				system("cls");
				erase_cur_block(block_shape, block_angle, block_x, block_y);
				if (level > 3)
					erase_cur_block(block_shape, block_angle, block_x, shadow_y);

				if (level == 1) {
					system("cls");
					PlaySound(TEXT("sound//fanfare.wav"), NULL, SND_FILENAME | SND_ASYNC);
					draw_image("Images//computer.bmp", 350, 50, 300, 300);
					Sleep(1000);
					system("cls");
					draw_image("Images//found.bmp", 350, 50, 300, 300);
					Sleep(2000);
					system("cls");
				}
				else if (level == 2) {
					system("cls");
					draw_image("Images//부우.bmp", 350, 50, 300, 300);
					Sleep(2000);
					system("cls");
				}
				return level;
			}
			if (is_gameover == 1)
			{
				show_gameover();
				SetColor(GRAY);
				SetAbility();
				return level + 10;   //추가
							//break;//종료
			}

			gotoxy(77, 23);
			Sleep(30);
			gotoxy(77, 23);
			if (stop == true)
			{
				timer = time(NULL);
				t = localtime(&timer);
				end = t->tm_sec; // 현재 초를 end에 대입
			}

			if (level == 3) {
				timer = time(NULL);
				t = localtime(&timer);
				end2 = t->tm_sec;
				if ((end2 - start2 >= 9 || end2 - start2 < -9)) { // 초 조정
					int u;
					u = waterfill();
					if (u == 1)
						is_gameover = 1;
					stop = true;
				}
			}
		}
		init();
		is_gameover = 0;
		score = 0;
		i = 0;
	}
	return level;
}

int GamePlay::gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

void GamePlay::SetColor(int color)
{
	HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

int GamePlay::init()
{
	int i, j;
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if (i == 20) //제일 밑 줄은 벽으로 채운다.
				total_block[i][j] = 1;
			else if ((j == 0) || (j == 13))
				total_block[i][j] = 1;
			else
				total_block[i][j] = 0;

		}
	}

	lines = 0;
	ab_x = 5;
	ab_y = 1;

	if (level == 0) {
		total_block[11][8] = 1; total_block[11][9] = 1; total_block[11][10] = 1; total_block[11][11] = 1;
		total_block[12][1] = 1; total_block[12][2] = 1; total_block[12][3] = 1; total_block[12][4] = 1; total_block[12][5] = 1; total_block[12][10] = 1; total_block[12][11] = 1; total_block[12][12] = 1;
		total_block[13][1] = 1; total_block[13][2] = 1; total_block[13][3] = 1; total_block[13][4] = 1; total_block[13][6] = 1; total_block[13][7] = 1; total_block[13][10] = 1; total_block[13][11] = 1; total_block[13][12] = 1;
		total_block[14][1] = 1; total_block[14][2] = 1; total_block[14][3] = 1; total_block[14][4] = 1; total_block[14][6] = 1; total_block[14][8] = 1; total_block[14][9] = 1; total_block[14][10] = 1; total_block[14][11] = 1; total_block[14][12] = 1;
		total_block[15][1] = 1; total_block[15][5] = 1; total_block[15][6] = 1; total_block[15][7] = 1; total_block[15][8] = 1; total_block[15][9] = 1; total_block[15][10] = 1; total_block[15][11] = 1; total_block[15][12] = 1;
		total_block[16][1] = 1; total_block[16][3] = 1; total_block[16][4] = 1; total_block[16][6] = 1; total_block[16][7] = 1; total_block[16][11] = 1;
		total_block[17][1] = 1; total_block[17][7] = 1; total_block[17][9] = 1; total_block[17][10] = 1; total_block[17][11] = 1;
		total_block[18][1] = 1; total_block[18][2] = 1; total_block[18][3] = 1; total_block[18][4] = 1; total_block[18][6] = 1; total_block[18][7] = 1; total_block[18][8] = 1; total_block[18][9] = 1; total_block[18][10] = 1; total_block[18][11] = 1;
		total_block[19][1] = 1; total_block[19][2] = 1; total_block[19][3] = 1; total_block[19][7] = 1; total_block[19][8] = 1; total_block[19][9] = 1; total_block[19][11] = 1; total_block[19][12] = 1;
	}

	return 0;
}

int GamePlay::show_cur_block(int shape, int angle, int x, int y)
{
	int i, j;

	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VIOLET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + y) < 0)
				continue;

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout << "■";
			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

int GamePlay::erase_cur_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout << "  ";
			}
		}
	}
	return 0;
}

int GamePlay::erase_cur_block2(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				block[shape][angle][j][i] = 0;
				cout << "  ";
				block[shape][angle][j][i] = 1;
			}
		}
	}
	return 0;
}


int GamePlay::show_total_block()
{
	int i, j;
	if (level == 2) {
		SetColor(SKY_BLUE);
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 14; j++)
			{
				if (j == 0 || j == 13 || i == 20)      //레벨에 따라 외벽 색이 변함
				{
					SetColor(DARK_GREEN);
				}
				else {
					SetColor(SKY_BLUE);
				}
				gotoxy((j * 2) + ab_x, i + ab_y);
				if (total_block[i][j] == 1)
				{
					cout << "■";
				}
				else if (total_block[i][j] == 2)
				{
					cout << "□";
				}
				else {
					cout << "  ";
				}

			}
		}
	}
	else if (level == 3) {
		SetColor(BLUE);
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 14; j++)
			{
				if (j == 0 || j == 13 || i == 20)      //레벨에 따라 외벽 색이 변함
				{
					SetColor(DARK_GREEN);
				}
				else {
					SetColor(BLUE);
				}
				gotoxy((j * 2) + ab_x, i + ab_y);
				if (total_block[i][j] == 1)
				{
					cout << "■";
				}
				else if (total_block[i][j] == 2)
				{
					cout << "□";
				}
				else {
					cout << "  ";
				}

			}
		}
	}
	else if (level == 4) {
		SetColor(RED);
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 14; j++)
			{
				if (j == 0 || j == 13 || i == 20)      //레벨에 따라 외벽 색이 변함
				{
					SetColor(DARK_GREEN);
				}
				else {
					SetColor(RED);
				}
				gotoxy((j * 2) + ab_x, i + ab_y);
				if (total_block[i][j] == 1)
				{
					cout << "■";
				}
				else if (total_block[i][j] == 2)
				{
					cout << "□";
				}
				else {
					cout << "  ";
				}

			}
		}
	}
	else if (level == 5) {
		SetColor(DARK_YELLOW);
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 14; j++)
			{
				if (j == 0 || j == 13 || i == 20)      //레벨에 따라 외벽 색이 변함
				{
					SetColor(DARK_GREEN);
				}
				else {
					SetColor(DARK_YELLOW);
				}
				gotoxy((j * 2) + ab_x, i + ab_y);
				if (total_block[i][j] == 1)
				{
					cout << "■";
				}
				else if (total_block[i][j] == 2)
				{
					cout << "□";
				}
				else {
					cout << "  ";
				}

			}
		}
	}
	else {
		SetColor(DARK_GRAY);
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 14; j++)
			{
				if (j == 0 || j == 13 || i == 20)      //레벨에 따라 외벽 색이 변함
				{
					SetColor(DARK_GREEN);
				}
				else {
					SetColor(DARK_GRAY);
				}
				gotoxy((j * 2) + ab_x, i + ab_y);
				if (total_block[i][j] == 1)
				{
					cout << "■";
				}
				else if (total_block[i][j] == 2)
				{
					cout << "□";
				}
				else {
					cout << "  ";
				}

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

int GamePlay::show_next_block(int shape)
{
	int i, j;
	SetColor((level + 1) % 6 + 1);
	for (i = 1; i < 7; i++)
	{
		gotoxy(33, i);
		for (j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << "■";
			}
			else {
				cout << "  ";
			}

		}
	}
	show_cur_block(shape, 0, 15, 1);
	return 0;
}

int GamePlay::make_new_block()
{
	int shape;
	int i;
	i = rand() % 100;
	if (i <= game_data[level]->getstickrate())      //막대기 나올확률 계산
		return 0;                     //막대기 모양으로 리턴

	shape = (rand() % 6) + 1;      //shape에는 1~6의 값이 들어감
	show_next_block(shape);

	return shape;
}

int GamePlay::strike_check(int shape, int angle, int x, int y)
{
	int i, j;
	int block_dat = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			//블록이 좌측벽 또는 우측벽에 닿았을때
			if (((x + j) == 0) || ((x + j) == 13))
				block_dat = 1;

			else
			{
				if (y + i >= 0)
					block_dat = total_block[y + i][x + j]; // 원래있는 블록에 닿을때
				else
					block_dat = 0;
			}

			if ((block_dat == 1) && (block[shape][angle][i][j] == 1))               //좌측벽의 좌표를 빼기위함
			{
				return 1;
			}
		}
	}
	return 0;
}

int GamePlay::merge_block(int shape, int angle, int x, int y)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (y + i >= 0)
				total_block[y + i][x + j] |= block[shape][angle][i][j];
		}
	}
	check_full_line();
	show_total_block();

	return 0;
}

int GamePlay::block_start(int& angle, int& x, int& y)
{
	x = 5;
	y = -3;
	angle = 0;
	return 0;
}

int GamePlay::move_block(int& shape, int& angle, int& x, int& y, int& next_shape)
{
	erase_cur_block(shape, angle, x, y);

	y++;   //블럭을 한칸 아래로 내림
	if (strike_check(shape, angle, x, y) == 1)
	{
		if (y < 0)   //게임오버
		{
			return 1;
		}
		y--;
		merge_block(shape, angle, x, y);
		shape = next_shape;
		next_shape = make_new_block();

		block_start(angle, x, y);
		show_next_block(next_shape);

		if (level > 3)
			shadow(shadow_y);
		return 2;
	}
	return 0;
}

int GamePlay::show_gameover()
{
	PlaySound(TEXT("sound//gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
	SetColor(RED);
	gotoxy(15, 8);
	cout << "┏━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃*        GAME OVER       *┃";
	gotoxy(15, 11);
	cout << "┃**************************┃";
	gotoxy(15, 12);
	cout << "┗━━━━━━━━━━━━━┛";
	fflush(stdin); //버퍼비우기
	Sleep(1000);

	_getche();
	system("cls");

	return 0;
}

int GamePlay::show_gamestat()
{
	static int printed_text = 0;

	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(35, 7);
		cout << "STAGE";

		gotoxy(35, 9);
		cout << "SCORE";

		gotoxy(35, 12);
		cout << "LINES";

		gotoxy(35, 15);
		cout << "WIND";

		gotoxy(35, 16);
		cout << "ICE";

		gotoxy(35, 17);
		cout << "FIRE";

		gotoxy(35, 18);
		cout << "EARTH";
	}

	gotoxy(41, 7);
	cout << level + 1;
	gotoxy(35, 10);
	cout << score;
	gotoxy(35, 13);
	if (game_data[level]->getclearline() - lines < 0)
		cout << 0;
	else
		cout << game_data[level]->getclearline() - lines << " ";
	gotoxy(41, 15);
	cout << wind;
	gotoxy(41, 16);
	cout << ice;
	gotoxy(41, 17);
	cout << fire;
	gotoxy(41, 18);
	cout << earth;
	return 0;
}

int GamePlay::input_data()
{
	int i = 0;

	while (i < 1 || i>8)
	{
		SetColor(GRAY);
		gotoxy(10, 7);
		cout << "┏━━━━━<GAME KEY>━━━━┓";
		Sleep(10);
		gotoxy(10, 8);
		cout << "┃ UP   : Rotate Block        ┃";
		Sleep(10);
		gotoxy(10, 9);
		cout << "┃ DOWN : Move One-Step Down  ┃";
		Sleep(10);
		gotoxy(10, 10);
		cout << "┃ SPACE: Move Bottom Down    ┃";
		Sleep(10);
		gotoxy(10, 11);
		cout << "┃ LEFT : Move Left           ┃";
		Sleep(10);
		gotoxy(10, 12);
		cout << "┃ RIGHT: Move Right          ┃";
		Sleep(10);
		gotoxy(10, 13);
		cout << "┗━━━━━━━━━━━━━━┛";

		gotoxy(10, 3);
		cout << "Select Start level[1-8]:       \b\b\b\b\b\b\b";
		cin >> i;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		system("cls");
	}
	level = i - 1;
	// 레벨에 따라 능력 쓰는 횟수 조정
	SetAbility();

	return 0;
}

int GamePlay::use_Earth()
{
	PlaySound(TEXT("sound//ground.wav"), NULL, SND_FILENAME | SND_ASYNC);
	int i, j, k;

	for (i = 18; i < 20; i++)
	{
		for (j = 1; j < 13; j++)
		{
			if (total_block[i][j] != 1)
			{
				total_block[i][j] = 1;
				SetColor(BLUE);
				gotoxy(j * 2 + ab_x, i + ab_y);
				cout << "□";
				Sleep(50);
			}
		}
		if (j == 13)   //한줄이 다 채워졌음
		{
			lines++;
			show_total_block();
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "□";
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "  ";
				Sleep(10);
			}

			for (k = i; k > 0; k--)
			{
				for (j = 1; j < 13; j++)
					total_block[k][j] = total_block[k - 1][j];
			}
			for (j = 1; j < 13; j++)
				total_block[0][j] = 0;
			score += 100 + (level * 10) + (rand() % 10);
			show_gamestat();
		}
		show_total_block();
	}
	if (lines <= game_data[level]->getclearline() - 1) {

		showProgress();
	}
	show_cur_block(block_shape, block_angle, block_x, block_y);
	if (level > 3)
		shadow(shadow_y);
	return 0;
}

int GamePlay::check_full_line()
{
	int i, j, k;
	for (i = 0; i < 20; i++)
	{
		for (j = 1; j < 13; j++)
		{
			if (total_block[i][j] != 1)
				break;
		}
		if (j == 13)   //한줄이 다 채워졌음
		{
			PlaySound(TEXT("sound//boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
			lines++;
			show_total_block();
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "□";
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "  ";
				Sleep(10);
			}

			for (k = i; k > 0; k--)
			{
				for (j = 1; j < 13; j++)
					total_block[k][j] = total_block[k - 1][j];
			}
			for (j = 1; j < 13; j++)
				total_block[0][j] = 0;
			score += 100 + (level * 10) + (rand() % 10);
			show_gamestat();
		}

	}
	if (lines <= game_data[level]->getclearline() - 1) {
		showProgress();
	}
	return 0;
}

void GamePlay::use_fire()
{
	//if (level > 3)
	//   erase_cur_block(block_shape, block_angle, block_x, shadow_y);
	int x = 5, y = 0;
	char keytemp;
	bool is_over = false;
	show_fireblock(x, y);
	PlaySound(TEXT("sound//fire.wav"), NULL, SND_FILENAME | SND_SYNC);
	while (true) {
		if (_kbhit()) {
			keytemp = _getch();
			if (keytemp == EXT_KEY) {
				keytemp = _getch();
				switch (keytemp) {
				case KEY_LEFT:
					if (x > 1)
					{
						erase_fireblock(x, y);
						x--;
						if (total_block[y][x] != 0) x++;
						show_fireblock(x, y);
					}
					break;
				case KEY_RIGHT:      //오른쪽으로 이동

					if (x < 14)
					{
						erase_fireblock(x, y);
						x++;
						if (total_block[y][x + 2] != 0) x--;
						show_fireblock(x, y);

					}
					break;
				}

			}
			if (keytemp == 32) {

				PlaySound(TEXT("sound//bigboom.wav"), NULL, SND_FILENAME | SND_ASYNC);
				while (!is_over)
				{
					Sleep(10);
					erase_fireblock(x, y);

					y++;   //블럭을 한칸 아래로 내림
					if (fire_strike(x, y))
					{

						//게임오버 조건은 x?
						y--;
						is_over = true;
						for (int i = 0; i < 3; i++) {
							erase_fireblock(x, y);

							y++;

							if (y + 3 == 21) {
								y--;
								break;
							}
							for (int j = 0; j < 3; j++) {
								total_block[y + 2][x + j] = 0;
							}
							show_fireblock(x, y);
						}
					}
					show_fireblock(x, y);
				}
				Sleep(500);
				erase_fireblock(x, y);
				break;
			}
			if (keytemp == KEY_ESC)
			{
				continue;
			}
		}


	}
	if (level > 3)
		shadow(shadow_y);
}

void GamePlay::show_fireblock(int & x, int & y) {
	SetColor(RED);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
			if (fireblock[j][i] == 1) cout << "■";
			else cout << " ";
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);

}
void GamePlay::erase_fireblock(int& x, int& y) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (fireblock[j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout << "  ";
			}
		}
	}
}

bool GamePlay::fire_strike(int & x, int & y)
{
	for (int i = 0; i < 3; i++) {
		if (total_block[y + 2][x + i] == 1) return true;
	}
	return false;
}

// 레벨에 따라 능력 쓰는 횟수 조정
void GamePlay::SetAbility() {
	//바람
	if (level > 5)
		wind = 2;
	else if (level > 2)
		wind = 1;
	else
		wind = 0;
	//얼음
	if (level > 5)
		ice = 2;
	else if (level > 3)
		ice = 1;
	else
		ice = 0;
	//불
	if (level > 5)
		fire = 2;
	else if (level > 4)
		fire = 1;
	else
		fire = 0;
	//대지
	if (level > 5)
		earth = 2;
	else
		earth = 0;
}

void GamePlay::showProgress()  //다가가는 모션
{

	if (level == 0) {
		if (game_data[level]->getclearline() <= lines) {
			system("cls");
			PlaySound(TEXT("sound//fanfare.wav"), NULL, SND_FILENAME | SND_ASYNC);
			draw_image("Images//found.bmp", 350, 50, 300, 300);
			Sleep(2000);
			system("cls");
		}
		else {
			draw_image("Images//computer.bmp", 500, 50, 300, 300);
		}
	}
	else if (level == 1) {
		if (lines < 5) draw_image("Images//부우4.bmp", 500, 50, 300, 300);
		else if (lines < 10) draw_image("Images//부우3.bmp", 500, 50, 300, 300);
		else if (lines < 15) draw_image("Images//부우2.bmp", 500, 50, 300, 300);
		else if (game_data[level]->getclearline() <= lines) {
			system("cls");
			draw_image("Images//부우.bmp", 350, 50, 300, 300);
			Sleep(2000);
			system("cls");
		}
		else draw_image("Images//부우1.bmp", 500, 50, 300, 300);

	}
	else if (level >= 2 && level <= 5) {
		int x = 360 + lines * 10;
		SetColor(WHITE);
		gotoxy(70, 4);
		cout << "                          ";
		gotoxy(70, 5);
		cout << "                          ";
		gotoxy(70, 6);
		cout << "                          ";
		gotoxy(70, 7);
		cout << "                          ";
		gotoxy(70, 8);
		cout << "                          ";
		gotoxy(70, 9);
		cout << "--------------------------";
		gotoxy(70, 10);
		cout << "                          ";
		gotoxy(70, 11);
		cout << "                          ";
		gotoxy(70, 12);
		cout << "                          ";
		gotoxy(70, 13);
		cout << "                          ";
		gotoxy(70, 14);
		cout << "                          ";
		draw_image("Images//초록.bmp", x, 50, 200, 200);
		if (level == 2) draw_image("Images//wind.bmp", 760, 50, 200, 200);
		else if (level == 3) draw_image("Images//water.bmp", 760, 50, 200, 200);
		else if (level == 4) draw_image("Images//fire.bmp", 760, 50, 200, 200);
		else if (level == 5) draw_image("Images//ground.bmp", 760, 50, 200, 200);
	}
}

void GamePlay::draw_image(const char* str, const int& nXDest, const int& nYDest, const int& nWidth, const int& nHeight)
{
	HBITMAP hImage = 0, hPreBit, g_BackBitMap;
	HDC hMemDC, hBackDC;

	hMemDC = CreateCompatibleDC(hdc);
	g_BackBitMap = CreateCompatibleBitmap(hdc, 1024, 768);
	hPreBit = (HBITMAP)SelectObject(hMemDC, g_BackBitMap);
	hBackDC = CreateCompatibleDC(hdc);

	hImage = (HBITMAP)LoadImage(NULL, TEXT(str), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	SelectObject(hBackDC, hImage);
	BitBlt(hMemDC, nXDest, nYDest, nWidth, nHeight, hBackDC, 0, 0, SRCCOPY); //크기
	BitBlt(hdc, nXDest, nYDest, nWidth, nHeight, hMemDC, nXDest, nYDest, SRCCOPY); //위치
}

void GamePlay::shadow(int & shadow_y)
{
	if (strike_check(block_shape, block_angle, block_x, shadow_y) == 0) {
		while (strike_check(block_shape, block_angle, block_x, shadow_y) != 1)
			shadow_y++;
	}
	while (strike_check(block_shape, block_angle, block_x, shadow_y) != 0)
		shadow_y--;
	if (strike_check(block_shape, block_angle, block_x, shadow_y) == 1)
		shadow_y--;
}

int GamePlay::show_cur_block2(int shape, int angle, int x, int y)
{
	int i, j;

	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VIOLET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + y) < 0)
				continue;

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout << "□";
			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

void GamePlay::mix_block()
{
	erase_cur_block2(block_shape, block_angle, block_x, shadow_y);
	erase_cur_block2(block_shape, block_angle, block_x, block_y);
	srand((unsigned)time(NULL));
	int i, j;
	int count_block = 0, first_row;
	int temp_block = 0;

	// 처음 블록이 있는 라인을 찾아주고
	for (i = 20; i > 0; i--)
	{
		for (j = 1; j < 13; j++)
		{
			if (total_block[i][j])
			{
				count_block++;
				first_row = i;
			}
		}
	}

	// 최소한의 블록 개수를 정해주고 너무 적으면 재배치하는 의미 X
	if (count_block < 30)
	{
		return;
	}
	else
	{
		// 블록이 처음 존재하는 라인부터
		for (i = first_row; i < 20; i++)
		{
			for (int j = 1; j < 13; j++)
			{
				// 0 또는 1 생성 후
				temp_block = rand() % 2;
				total_block[i][j] = temp_block;
				// 재배치한 블록 개수 체크하고
				if (temp_block)
					count_block--;
			}
			// 다 배치했으면 함수 종료 
			if (count_block < 1)
				break;
		}
	}
	// 재배치된 블록 보여줌
	erase_cur_block(block_shape, block_angle, block_x, shadow_y);
	show_total_block();
}

int GamePlay::waterfill()
{
	bool check = true;
	int count;
	int pos;
	for (int i = 0; i < 21; i++) {
		for (int j = 1; j < 13; j++) {
			if (total_block[i][j] == 1) {
				pos = i;
				count = pos;
				check = false;
				break;
			}
		}
		if (check == false)
			break;
	}
	if (pos == 0) {
		return 1;
	}

	for (int j = 0; j < 20 - pos; j++) {
		for (int i = 1; i < 13; i++) {
			if (total_block[count][i] == 1)
				total_block[count - 1][i] = 1;
			else if (total_block[count][i] == 0)
				total_block[count - 1][i] = 0;
		}
		count++;
	}
	for (int i = 1; i < 13; i++)
	{
		total_block[19][i] = rand() % 2;
	}
	show_total_block();
	return 0;
}

int GamePlay::show_colorful_block(int shape, int angle, int x, int y)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + y) < 0)
				continue;

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				SetColor(rand() % 15 + 1);
				cout << "■";
			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}