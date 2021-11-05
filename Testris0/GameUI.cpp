#include "GameUI.h"
using namespace std;

GameUI::GameUI()
	:Gp(new GamePlay())
{
	srand((unsigned)time(NULL));
	hdc = GetDC(FindWindow(TEXT("ConsoleWindowClass"), NULL));
	system("mode con cols=135 lines=32");
}

GameUI::~GameUI()
{
	delete Gp;
	Gp = nullptr;
}

void GameUI::gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
}

void GameUI::SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

void GameUI::SetCursorView(bool visible)
{
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

int GameUI::show_logo()
{
	PlaySound(TEXT("sound//interstellar.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);



	string string_logo[] = {
	   "   $$$$$$$$  $$$$$$$   $$$$$$$$ $$$$$$$$ $$$$     $$",
	   "  $$//////$$/$$////$$ /$$///// /$$///// /$$/$$   /$$",
	   " $$      // /$$   /$$ /$$      /$$      /$$//$$  /$$",
	   "/$$         /$$$$$$$  /$$$$$$$ /$$$$$$$ /$$ //$$ /$$",
	   "/$$    $$$$$/$$///$$  /$$////  /$$////  /$$  //$$/$$",
	   "//$$  ////$$/$$  //$$ /$$      /$$      /$$   //$$$$",
	   " //$$$$$$$$ /$$   //$$/$$$$$$$$/$$$$$$$$/$$    //$$$",
	   "  ////////  //     // //////// //////// //      ///",
	   "",
	   "  $$$$$$$$$$ $$$$$$$$ $$$$$$$    $$$$$$$$ $$$$$$$$$$ $$$$$$$$ $$       $$           $$",
	   "  ////$$/// /$$///// /$$////$$  $$////// /////$$/// /$$///// /$$      /$$          $$$$",
	   "     /$$    /$$      /$$   /$$ /$$           /$$    /$$      /$$      /$$         $$//$$",
	   "     /$$    /$$$$$$$ /$$$$$$$  /$$$$$$$$$    /$$    /$$$$$$$ /$$      /$$        $$  //$$",
	   "     /$$    /$$////  /$$///$$  ////////$$    /$$    /$$////  /$$      /$$       $$$$$$$$$$",
	   "     /$$    /$$      /$$  //$$        /$$    /$$    /$$      /$$      /$$      /$$///////$$",
	   "     /$$    /$$$$$$$$/$$   //$$ $$$$$$$$     /$$    /$$$$$$$$/$$$$$$$$/$$$$$$$$/$$      /$$",
	   "     //     //////// //     // ////////      //     //////// //////// //////// //       /// "
	};
	SetColor(DARK_GREEN);
	for (int j = 0; j < 17; j++) {
		gotoxy(20, j + 5);
		cout << string_logo[j] << endl;
		Sleep(100);
	}
	SetColor(WHITE);

	gotoxy(55, 25);
	cout << "Please Press Any Key~!";
	_getwch();

	show_manual();
	gotoxy(55, 25);
	cout << "Please Press Any Key~!";
	_getwch();

	system("cls");
	show_dialog("  AD2296, 인간의 무분별한 개발로 지구는 황폐화가 되고", 37, 7);
	show_dialog("  더 이상 제 기능을 하지 못하자 사람들은 파괴되지 않은 행성을 찾으려고 한다.", 27, 8);
	show_dialog("  하지만 그런 행성을 찾는 것은 쉽지 않아 보인다. ", 40, 11);
	show_dialog("  온갖 분야의 사람들이 함께 노력하고 있지만 진전은 없어 보인다...", 30, 13);

	system("cls");
	PlaySound(NULL, 0, 0);

	gotoxy(60, 5);
	SetColor(DARK_GREEN);
	cout << "   <stage 1>";
	SetColor(WHITE);
	gotoxy(23, 7);
	cout << " 황폐화된 지구에서 블럭 2줄을 깨고 마지막으로 남은 인류들이 새롭게 개척할 행성을 찾아주세요!";
	draw_image("Images//computer.bmp", 380, 150, 300, 300);
	gotoxy(55, 28);
	SetColor(DARK_GRAY);
	cout << "Please Press Any Key~!";
	_getwch();
	SetColor(WHITE);
	system("cls");

	show_story();

	return 0;
}

void GameUI::show_default_dialog(const int x, const int y)
{
	SetColor(WHITE);
	for (int i = -1; i < 8; i++) {
		gotoxy(x, y + i);
		if (i == 0)
			cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
		else if (i == 7)
			cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
		else if (i == -1)
			cout << "                                                                                                             ";
		else
			cout << "┃                                                                                      ┃";
	}
}void GameUI::show_dialog(const char * comment, const int & x, const int & y)
{
	string::iterator itr;
	string s_com = comment;
	int dialog_flag = 0;
	char keytemp;

	SetColor(WHITE);
	gotoxy(x + 2, y + 1);
	for (auto i : s_com)
	{
		cout << i;
		dialog_flag++;

		if (dialog_flag % 86 == 0)
		{
			gotoxy(x + 2, y + 1 + dialog_flag / 86);
		}
		Sleep(20);

		if (_kbhit())
		{
			keytemp = _getch();
			if (keytemp == 32)
			{
				dialog_flag = 0;
				gotoxy(x + 2, y + 1);
				for (auto i : s_com)
				{
					cout << i;
					dialog_flag++;

					if (dialog_flag % 86 == 0)
					{
						gotoxy(x + 2, y + 1 + dialog_flag / 86);
					}
				}
				gotoxy(x + 2, y + 1);
				cout << " ";
				Sleep(1000);
				keytemp = _getwch();
				if (keytemp == 32)
				{
					return;
				}
			}
		}
	}
	keytemp = _getwch();
	if (keytemp == 32)
	{
		return;
	}
}
void GameUI::show_npc_dialog(const char* npc, const char* comment, int npc_x)
{
	show_default_dialog(dialog_X, dialog_Y);

	string::iterator itr;
	string s_npc = npc;
	string s_com = comment;
	int dialog_flag = 0;
	char keytemp;

	SetColor(WHITE);
	gotoxy(dialog_X + 2 + npc_x, dialog_Y - 1);
	for (auto i : s_npc)
	{
		cout << i;
	}

	SetColor(WHITE);
	gotoxy(dialog_X + 2, dialog_Y + 1);
	for (auto i : s_com)
	{
		cout << i;
		dialog_flag++;

		if (dialog_flag % 86 == 0)
		{
			gotoxy(dialog_X + 2, dialog_Y + 1 + dialog_flag / 86);
		}
		Sleep(20);

		if (_kbhit())
		{
			fflush(stdin);
			keytemp = _getch();
			if (keytemp == 32)
			{
				dialog_flag = 0;
				gotoxy(dialog_X + 2, dialog_Y + 1);
				for (auto j : s_com)
				{
					cout << j;
					dialog_flag++;

					if (dialog_flag % 86 == 0)
					{
						gotoxy(dialog_X + 2, dialog_Y + 1 + dialog_flag / 86);
					}
				}
				gotoxy(dialog_X + 2, dialog_Y + 1);
				cout << " ";
				Sleep(1000);
				keytemp = _getwch();
				if (keytemp == 32)
				{
					return;
				}
			}
		}
	}
	fflush(stdin);
	keytemp = _getwch();
	if (keytemp == 32)
	{
		return;
	}
	Sleep(1000);
}

void GameUI::draw_image(const char* str, const int& nXDest, const int& nYDest, const int& nWidth, const int& nHeight)
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

void GameUI::show_story()
{
	int level = 0;

	while (level != 7) {
		level = Gp->play();

		if (level < 10) {
			switch (level) {
			case 1:
				system("cls");
				show_dialog("  그렇게 전세계의 과학자들은 파괴되지 않은,", 45, 13);
				show_dialog("  사람이 살 수 있는 행성은 GREENJOA 행성임을 발견, 이주를 결정하게 된다.", 30, 15);
				draw_spaceship(level);
				// 지구에서 그린조아 가는거 추가하기
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 우와 여기가 GREENJOA 행성이구나!");
				system("cls");
				show_npc_dialog("사람들", " 여기 사람이 살 수 있는 곳 맞아?? (웅성웅성)");
				show_npc_dialog("사람들", " 숨도 잘 안쉬어지고 흙이나 물도 별로 안보이는걸..");
				show_npc_dialog("지도자", " 진정들 하게! 사실 우리 지구에는 바람,물,불,땅 정령이 있네.", 80);
				show_npc_dialog("지도자", " 지구가 점점 파괴되면서 보이지 않기 시작했지만 지금은 그들이 유일한 희망이라네..", 80);
				show_npc_dialog("지도자", " 우리 중 누군가가 지구에 가서 그들을 구해와야하네..", 80);
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " (어쩌지... 무섭긴 하지만 유일한 희망인걸.. 내가 가는게 맞겠지) 제가 다녀오겠습니다!!");
				system("cls");
				show_npc_dialog("지도자", " 오, 자네는 초록이 아닌가! 참으로 믿음직하군. 그런데 우주선이 착륙하다 고장났으니 수리가 먼저겠네.", 80);
				system("cls");

				break;
			case 2:
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 휴! 수리가 끝났어! 이제 지구로 출발해볼까?");
				draw_spaceship(level);
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 음.. 그런데 바람,물,불,땅 정령들이 다 어디로 갔지?");
				show_npc_dialog("초록", " 엇 지도자님이 주신 좌표랑 다른 곳에 왔잖아!!");
				show_npc_dialog("초록", " 어쩔 수 없지.. 다시 그 좌표로 가자");
				system("cls");

				break;
			case 3:
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 안녕하세요! 바람 정령님! 저는 초록이라고 해요. 다른 정령들은 어디에 있나요?");
				show_npc_dialog("초록", " 지구 사람들이 이주한 GREENJOA 행성에 모든 정령들의 도움이 필요해요..");
				system("cls");
				draw_image("Images//wind350.bmp", 450, 20, 350, 350);
				show_npc_dialog("바람 정령", " 지구가 폐허가 된 후 우리는 흩어져 버렸어..그래도 걱정하지마! 내가 있잖아", 80);
				show_npc_dialog("바람 정령", " 초록이 네가 다른 정령들을 찾는 걸 도와줄게", 80);
				show_npc_dialog("바람 정령", " 그리고 너에게 능력을 하나 빌려줄게.", 80);
				show_npc_dialog("바람 정령", " 1번 키를 누르면 현재의 블럭을 다음 블럭으로 바꿔줄 수 있어!", 80);
				show_npc_dialog("바람 정령", " 다음 스테이지부터 사용할 수 있지만 딱 1번만 사용할 수 있다는걸 알아둬!", 80);
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 감사합니다!");
				system("cls");


				break;
			case 4:
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 안녕하세요! 물 정령님! 저는 초록이라고 해요. 도움이 필요해서 바람 정령님과 찾아왔어요.");
				system("cls");
				draw_image("Images//water350.bmp", 450, 20, 350, 350);
				show_npc_dialog("물 정령", " 그렇다면 잘 찾아왔어!", 80);
				show_npc_dialog("물 정령", " 이제부터 너는 블럭의 그림자를 볼 수 있어.", 80);
				show_npc_dialog("물 정령", " 또 2번 키를 누르면 블럭을 그 자리에 3초 정도 멈출 수 있어.", 80);
				show_npc_dialog("물 정령", " 블럭을 멈추는 능력은 1번만 사용할 수 있다는걸 알아둬!", 80);
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 감사합니다!");
				system("cls");

				break;
			case 5:
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 안녕하세요! 불 정령님! 저는 초록이라고 해요. 도움이 필요해서 왔어요.");
				system("cls");
				draw_image("Images//fire350.bmp", 450, 20, 350, 350);
				show_npc_dialog("불 정령", " 그래. 잘 찾아왔네. 나는 3X3 공간만큼의 블럭을 지워줄 수 있어.", 80);
				show_npc_dialog("불 정령", " 3번 키를 누르면 다음 블럭이 불 블럭으로 바뀌고 사용할 수 있게 돼.", 80);
				show_npc_dialog("불 정령", " 스테이지당 1번만 사용할 수 있어.", 80);
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 감사합니다!");
				system("cls");
				draw_image("Images//fire350.bmp", 450, 20, 350, 350);
				show_npc_dialog("불 정령", " 내가 땅의 정령이 어디있는지 알고 있어. 땅 밑으로 가야해", 80);
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 헉!! 넵!!");
				system("cls");

				break;
			case 6:
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 안녕하세요! 땅 정령님! 저는 초록이라고 해요. 도움이 필요해서 왔어요.");
				system("cls");
				draw_image("Images//ground350.bmp", 450, 20, 350, 350);
				show_npc_dialog("땅 정령", " 용케도 나를 찾아왔네. 좋아! 내 능력을 빌려주지", 80);
				show_npc_dialog("땅 정령", " 나는 지진을 일으켜서 빈칸을 채워줄 수 있어. 무려 두 줄이나 지워준다구!", 80);
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 정말 엄청나네요!");
				system("cls");
				draw_image("Images//ground350.bmp", 450, 20, 350, 350);
				show_npc_dialog("땅 정령", " 이제 모든 정령들을 모았니?", 80);
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 네! 이제 다같이 GREENJOA 행성으로 떠나요!");
				draw_spaceship(level);
				show_dialog("쾅!!!!", 3, 21);
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 뭐야!!!");
				system("cls");
				draw_image("Images//wind350.bmp", 450, 20, 350, 350);
				show_npc_dialog("바람 정령", " 우주선에 구멍이 났어! 저 운석 때문이야!", 80);
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 헉 빨리 메꿔야해요!! 모두 힘을 합쳐주세요!!");
				system("cls");
				draw_image("Images//정령들.bmp", 450, 20, 350, 350);
				show_npc_dialog("정령들", " 그래! 우리의 힘을 모두 빌려줄게 !!!", 80);
				system("cls");

				break;
			case 7:
				system("cls");
				draw_image("Images//초록350.bmp", 20, 20, 350, 350);
				show_npc_dialog("초록", " 정령님들 덕분에 무사히 도착할 수 있었어요! 감사해요!");
				system("cls");
				draw_image("Images//정령들.bmp", 450, 20, 350, 350);
				show_npc_dialog("정령들", " 그래. 이제 우리가 GREENJOA 행성을 돌봐줄게", 80);
				system("cls");
				show_npc_dialog("지도자", " 초록아. 고생이 많았구나. 네 덕분에 우리 모두가 다시 희망을 되찾았구나", 80);
				show_npc_dialog("사람들", " 와~~~ 초록이 짱!!", 80);
				draw_image("Images//초록400.bmp", 300, 20, 350, 350); //
				show_npc_dialog("초록", " (뿌듯-)");
				system("cls");
				show_dialog("  그렇게 초록이와 사람들은 정령의 도움을 얻어", 45, 14);
				show_dialog("  GREENJOA 행성을 성공적으로 개척해 살아갈 수 있게 되었습니다.", 35, 16);
				system("cls");
				PlaySound(TEXT("sound//fanfare.wav"), NULL, SND_FILENAME | SND_ASYNC);
				draw_image("Images//greenjoa.bmp", 300, 50, 400, 400);
				Sleep(5000);

				break;
			}
		}
		else {
			//중간에 게임오버됐을 때

			if (level - 10 > 0) {
				draw_image("Images//초록400.bmp", 300, 20, 350, 350);
				show_npc_dialog("초록", " 안돼!!! 내가 모두의 희망이었는데...");
				system("cls");

			}


			SetColor(DARK_YELLOW);
			string continue_logo[] = {
			"   ■■■■■■                                ■■    //■■                                             ■■■■",
			"  ■■////■■                                /■■                                                      ■■//■■",
			" ■■    //      ■■■■■■  ■■■■■  ■■■■■■  ■■  ■■■■■■   ■■   ■■   ■■■■■ /■■ /■■",
			"/■■            ■■////■■//■■///■■  ///■■/    /■■ //■■///■■  /■■  /■■  ■■///■■    //■■ ",
			"/■■           /■■   /■■ /■■  /■■    /■■     /■■  /■■  /■■  /■■  /■■ /■■■■■■   //■■",
			"//■■    ■■  /■■   /■■ /■■  /■■    /■■     /■■  /■■  /■■  /■■  /■■ /■■////         " ,
			" //■■■■■■//■■■■■■  ■■  /■■   //■■     /■■  ■■■  /■■//■■■■■■//■■■■■■   ■■"  ,
			"  ///////////   ///////////    ////  ////    //////     /////  /////   ////  ///////////  /////////////   ////  "
			};
			for (int k = 0; k < 8; k++) {
				gotoxy(10, k + 8);
				cout << continue_logo[k];
			}
			SetColor(WHITE);
			string countdown[] = {
			   "□   □□ ",
			   "□  □  □ ",
			   "□  □  □ ",
			   "□  □  □ ",
			   "□   □□ ",
			   "  □□□ ",
			   "  □  □ ",
			   "  □□□ ",
			   "      □",
			   "  □□□",
			   "  □□□ ",
			   "  □  □ ",
			   "  □□□ ",
			   "  □  □ ",
			   "  □□□ ",
			   "  □□□ ",
			   "      □ ",
			   "      □ ",
			   "      □ ",
			   "      □ ",
			   "  □□□ ",
			   "  □ ",
			   "  □□□ ",
			   "  □  □ ",
			   "  □□□ ",
			   "  □□□ ",
			   "  □ ",
			   "  □□□ ",
			   "      □ ",
			   "  □□□ ",
			   "  □  □ ",
			   "  □  □ ",
			   "  □□□ ",
			   "      □ ",
			   "      □ ",
			   "  □□□ ",
			   "      □ ",
			   "  □□□ ",
			   "      □ ",
			   "  □□□ ",
			   "  □□□ ",
			   "      □ ",
			   "  □□□ ",
			   "  □  ",
			   "  □□□ ",
			   "    □ ",
			   "    □ ",
			   "    □ ",
			   "    □ ",
			   "    □ "
			};
			string countdown_erase[] = {
			   "            ",
			   "            ",
			   "            ",
			   "            ",
			   "            "
			};
			SetColor(DARK_GRAY);
			gotoxy(58, 27);
			cout << "Press '0' Key~!";
			SetColor(WHITE);
			char keytemp;
			int m = 0;
			bool check = false;
			fflush(stdin);
			for (int h = 0; h < 10; h++) {
				for (int k = 0; k < 5; k++) {
					if (_kbhit()) {
						check = true;
						break;
					}
					gotoxy(60, k + 20);
					cout << countdown[m];
					m++;

				}
				if (check) break;
				Sleep(1000);
				for (int k = 0; k < 5; k++) {
					if (_kbhit()) {
						check = true;
						break;
					}
					gotoxy(60, k + 20);
					cout << countdown_erase[k];

				}
				if (check) break;
				Sleep(100);
			}
			system("cls");
			if (check) {
				keytemp = _getwch();
				if (keytemp == 48) {
					level -= 10;
				}
				else {
					system("cls");
					show_dialog("  임무를 실패하였습니다.", 50, 14);
					system("cls");
					return;
				}
			}
			else {
				system("cls");
				show_dialog("  임무를 실패하였습니다.", 50, 21);
				system("cls");
				return;
			}
		}
		system("cls");
		switch (level) {
		case 0:
			//stage 1
			gotoxy(60, 5);
			SetColor(DARK_GREEN);
			cout << "   <stage 1>";
			SetColor(WHITE);
			gotoxy(30, 7);
			cout << " 블럭 2줄을 깨고 마지막으로 남은 인류들이 새롭게 개척할 행성을 찾아주세요!";
			draw_image("Images//computer.bmp", 380, 150, 300, 300);
			gotoxy(55, 28);
			SetColor(DARK_GRAY);
			cout << "Please Press Any Key~!";
			_getwch();
			SetColor(WHITE);
			break;
		case 1:
			//stage 2
			gotoxy(60, 5);
			SetColor(DARK_GREEN);
			cout << "   <stage 2>";
			SetColor(WHITE);
			gotoxy(44, 7);
			cout << " 블럭 20줄을 깨고 고장난 우주선을 고쳐주세요 !";
			draw_image("Images//부우4.bmp", 380, 150, 300, 300);
			gotoxy(55, 28);
			SetColor(DARK_GRAY);
			cout << "Please Press Any Key~!";
			_getwch();
			SetColor(WHITE);
			break;
		case 2:
			//stage 3
			gotoxy(60, 3);
			SetColor(DARK_GREEN);
			cout << "   <stage 3>";
			SetColor(WHITE);
			gotoxy(47, 5);
			cout << " 블럭 20줄을 깨고 바람의 정령을 만나세요 !";
			SetColor(RED);
			gotoxy(43, 7);
			cout << "※주의 ! 바람의 정령이 블럭을 제멋대로 움직입니다.";
			draw_image("Images//wind350.bmp", 350, 150, 350, 350);
			gotoxy(55, 28);
			SetColor(DARK_GRAY);
			cout << "Please Press Any Key~!";
			_getwch();
			SetColor(WHITE);
			break;
		case 3:
			//stage 4
			gotoxy(60, 3);
			SetColor(DARK_GREEN);
			cout << "   <stage 4>";
			SetColor(WHITE);
			gotoxy(47, 5);
			cout << " 블럭 20줄을 깨고 물의 정령을 만나세요 !";
			SetColor(RED);
			gotoxy(43, 7);
			cout << "※주의 ! 물의 정령이 블럭을 점점 차오르게 합니다.";
			draw_image("Images//water350.bmp", 350, 150, 350, 350);
			gotoxy(55, 28);
			SetColor(DARK_GRAY);
			cout << "Please Press Any Key~!";
			_getwch();
			SetColor(WHITE);
			system("cls");
			break;
		case 4:

			//stage 5
			gotoxy(60, 3);
			SetColor(DARK_GREEN);
			cout << "   <stage 5>";
			SetColor(WHITE);
			gotoxy(47, 5);
			cout << " 블럭 20줄을 깨고 불의 정령을 만나세요 !";
			SetColor(RED);
			gotoxy(43, 7);
			cout << "※주의 ! 불의 정령이 블럭의 좌우를 바꿉니다.";
			draw_image("Images//fire350.bmp", 350, 150, 350, 350);
			gotoxy(55, 28);
			SetColor(DARK_GRAY);
			cout << "Please Press Any Key~!";
			_getwch();
			SetColor(WHITE);
			system("cls");
			break;
		case 5:
			//stage 6
			gotoxy(60, 3);
			SetColor(DARK_GREEN);
			cout << "   <stage 6>";
			SetColor(WHITE);
			gotoxy(47, 5);
			cout << " 블럭 20줄을 깨고 땅의 정령을 만나세요 !";
			SetColor(RED);
			gotoxy(37, 7);
			cout << "※주의 ! 땅의 정령이 지진을 일으켜 블럭의 위치가 바뀝니다.";
			draw_image("Images//ground350.bmp", 350, 150, 350, 350);
			gotoxy(55, 28);
			SetColor(DARK_GRAY);
			cout << "Please Press Any Key~!";
			_getwch();
			SetColor(WHITE);
			system("cls");
			break;
		case 6:
			//stage 7
			gotoxy(58, 3);
			SetColor(DARK_GREEN);
			cout << "   <final stage>";
			SetColor(WHITE);
			gotoxy(40, 5);
			cout << " 구멍난 우주선을 메꾸고 GREENJOA로 무사히 복귀하세요 !";
			SetColor(RED);
			gotoxy(43, 7);
			cout << "지금부터는 모든 능력을 2번씩 사용할 수 있습니다.";
			draw_image("Images//정령들.bmp", 350, 150, 350, 350);
			gotoxy(55, 28);
			SetColor(DARK_GRAY);
			cout << "Please Press Any Key~!";
			_getwch();
			SetColor(WHITE);
			break;
		}
		system("cls");
	}

}


void GameUI::show_manual()
{
	system("cls");
	SetColor(DARK_YELLOW);
	int k = 50;
	gotoxy(k, 7);
	cout << "┏━━━━━<GAME KEY>━━━━┓";
	gotoxy(k, 8);
	cout << "┃ UP   : Rotate Block        ┃";
	gotoxy(k, 9);
	cout << "┃ DOWN : Move One-Step Down  ┃";
	gotoxy(k, 10);
	cout << "┃ SPACE: Move Bottom Down    ┃";
	gotoxy(k, 11);
	cout << "┃ LEFT : Move Left           ┃";
	gotoxy(k, 12);
	cout << "┃ RIGHT: Move Right          ┃";
	gotoxy(k, 13);
	cout << "┗━━━━━━━━━━━━━━┛";
	SetColor(WHITE);

}

void GameUI::draw_spaceship(int & level)      //추가
{
	if (level == 2) {
		PlaySound(TEXT("sound//flying.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int k = 300; k <= 550; k += 20) {
			system("cls");
			draw_image("Images//g_e.bmp", 40, 0, 1000, 500);
			draw_image("Images//우주선A.bmp", k, 150, 200, 200);
			Sleep(200);
		}
	}
	else if (level == 1) {
		PlaySound(TEXT("sound//flying.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int k = 550; k >= 300; k -= 20) {
			system("cls");
			draw_image("Images//g_e.bmp", 40, 0, 1000, 500);
			draw_image("Images//우주선B.bmp", k, 150, 200, 200);
			Sleep(200);
		}
	}
	else if (level == 6) {
		PlaySound(TEXT("sound//flying.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int k = 550; k >= 400; k -= 20) {
			system("cls");
			draw_image("Images//g_e.bmp", 40, 0, 1000, 500);
			draw_image("Images//우주선B.bmp", k, 150, 200, 200);
			Sleep(200);
		}
		PlaySound(TEXT("sound//bigboom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		draw_image("Images//운석충돌.bmp", 40, 20, 1000, 500);
	}


	Sleep(1000);
	system("cls");
}