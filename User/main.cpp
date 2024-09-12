#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <windows.h>

/*****************************控制台颜色函数宏定义*****************************/
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED)
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN)
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE)
#define GREENPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define REDPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY)
#define BLUEPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define YELLO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY)
#define INDIG SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)

/*食物结构体*/
struct food
{
	int x;
	int y;
}apple;

typedef struct body
{
	int x;
	int y;
	struct body* Next;
	struct body* Last;
}Snake;

/*蛇头指针*/
Snake* Header = NULL;
int Score = 0;

void gotoxy(int， int);
void Initialization(void);/*初始化场景和蛇头*/
void Food(void);/*随机化食物*/
void Play(void);/*WSAD操作*/
void Draw(char);/*打印游戏场景*/
int Die(void);/*检测死亡*/
void Grow(char); /*长度增加*/

int main(void)
{
	char chioce; /*游戏结束后，是否继续的选择*/
	srand((unsigned)(time(NULL)));
Omega:
	system("cls");
	Score = 0;
	Initialization();
	Play();
Alpha:
	printf("Developer: vmpy(Flee)\n");
	printf("Game over!Do you want to play again?(Y\\N)\n");
	chioce = _getch();
	chioce = _getch();
	switch (chioce) {
	case 'Y':
	case 'y':goto Omega; break;
	case 'X':
	case 'x':break;
	default:goto Alpha; break;
	}
	return 0;
}

void Play(void)
{
	char ch = 0;
	int Tmpx, Tmpy;
	Snake* Tmp = Header;
	Food();			//随机化食物 
	Draw(ch);			//绘制图形

Hell:
	ch = _getch();
	/*具体操作*/
	while (1) {
	GO:
		Tmp = Header;
		if (ch == 'W') {
			while (1) {
				Grow(ch);
				while (Tmp->Next != NULL) {
					Tmp = Tmp->Next;				//定位到末尾 
				}
				Tmpx = Tmp->x;
				Tmpy = Tmp->y;
				while (Tmp != NULL) {
					if (Tmp->Last) {
						Tmp->x = Tmp->Last->x;
						Tmp->y = Tmp->Last->y;
					}
					Tmp = Tmp->Last;
				}
				(Header->y)--;
				if (Die()) {
					goto Death;
				}
				Tmp = Header;
				Sleep(170);
				gotoxy(Tmpx + 5, Tmpy + 5);
				printf(" ");
				Draw(ch);
				if (_kbhit()) {
					ch = _getch();
					if (ch == 'S') {					//贪吃蛇一律不得倒退 
						ch = 'W';
					}
					goto GO;
				}
			}
		}
		else if (ch == 'S') {
			while (1) {
				Grow(ch);
				while (Tmp->Next != NULL) {
					Tmp = Tmp->Next;				//定位到末尾 
				}
				Tmpx = Tmp->x;
				Tmpy = Tmp->y;
				while (Tmp != NULL) {
					if (Tmp->Last) {
						Tmp->x = Tmp->Last->x;
						Tmp->y = Tmp->Last->y;
					}
					Tmp = Tmp->Last;
				}
				(Header->y)++;
				if (Die()) {
					goto Death;
				}
				Tmp = Header;
				Sleep(170);
				gotoxy(Tmpx + 5, Tmpy + 5);
				printf(" ");
				Draw(ch);
				if (_kbhit()) {
					ch = _getch();
					if (ch == 'W') {
						ch = 'S';
					}
					goto GO;
				}
			}
		}
		else if (ch == 'A') {
			while (1) {
				Grow(ch);
				while (Tmp->Next != NULL) {
					Tmp = Tmp->Next;				//定位到末尾 
				}
				Tmpx = Tmp->x;
				Tmpy = Tmp->y;
				while (Tmp != NULL) {
					if (Tmp->Last) {
						Tmp->x = Tmp->Last->x;
						Tmp->y = Tmp->Last->y;
					}
					Tmp = Tmp->Last;
				}
				(Header->x) = (Header->x) - 2;
				if (Die()) {
					goto Death;
				}
				Tmp = Header;
				Sleep(170);
				gotoxy(Tmpx + 5, Tmpy + 5);
				printf(" ");
				Draw(ch);
				if (_kbhit()) {
					ch = _getch();
					if (ch == 'D') {
						ch = 'A';
					}
					goto GO;
				}
			}
		}
		else if (ch == 'D') {
			while (1) {
				Grow(ch);
				while (Tmp->Next != NULL) {
					Tmp = Tmp->Next;				//定位到末尾 
				}
				Tmpx = Tmp->x;
				Tmpy = Tmp->y;
				while (Tmp != NULL) {
					if (Tmp->Last) {
						Tmp->x = Tmp->Last->x;
						Tmp->y = Tmp->Last->y;
					}
					Tmp = Tmp->Last;
				}
				(Header->x) = (Header->x) + 2;
				if (Die()) {
					goto Death;
				}
				Tmp = Header;
				Sleep(170);
				gotoxy(Tmpx + 5, Tmpy + 5);
				printf(" ");
				Draw(ch);
				if (_kbhit()) {
					ch = _getch();
					if (ch == 'A') {
						ch = 'D';
					}
					goto GO;
				}
			}
		}
		else {
			goto Hell;
		}
	}

Death:							//游戏失败之后 
	system("cls");
	gotoxy(0, 0);
	printf("You died!\n");
	printf("\n\t分数:%d\n\n", Score);
}

void Grow(char ch)					//长长一截身体 
{
	Snake* End = Header;
	if (Header->x == apple.x && Header->y == apple.y) {
		while (End->Next != NULL) {
			End = End->Next;
		}
		End->Next = (Snake*)(malloc(sizeof(Snake)));
		(End->Next)->Next = NULL;
		(End->Next)->Last = End;
		switch (ch) {							//根据贪吃蛇吃到食物时的姿势改变新身体的出现位置 
		case 'W': {
			(End->Next)->x = End->x;
			(End->Next)->y = End->y + 1;
		}
		case 'S': {
			(End->Next)->x = End->x;
			(End->Next)->y = End->y - 1;
		}
		case 'A': {
			(End->Next)->x = End->x + 2;
			(End->Next)->y = End->y;
		}
		case 'D': {
			(End->Next)->x = End->x - 2;
			(End->Next)->y = End->y;
		}
		}
		Food();
		Score = Score + 10;
	}
	return;
}

void Draw(char ch)
{
	int x, y, space = 0;
	Snake* Tmp;
	Tmp = Header->Next;
	gotoxy(Header->x + 5, Header->y + 5);
	REDPLUS;
	printf("□");
	YELLO;
	while (Tmp != NULL) {
		gotoxy(Tmp->x + 5, Tmp->y + 5);
		printf("■");
		Tmp = Tmp->Next;
	}
	GREENPLUS;
	for (x = 0x0; x < 0x19; x++) {
		gotoxy(x + space + 5, 0x0 + 5);
		printf("□");
		gotoxy(x + space + 5, 0x19 + 5);
		printf("□");
		space++;
	}
	for (y = 0x0; y < 0x19; y++) {
		gotoxy(0x0 + 5, y + 5);
		printf("□");
		gotoxy(0x32 + 5, y + 5);
		printf("□");
	}
	gotoxy(x + space + 5, 0x19 + 5);
	printf("□");
	REDPLUS;
	gotoxy(apple.x + 5, apple.y + 5);
	printf("○");
	gotoxy(52 + 5, 5 + 5);
	printf("\t分数:%d", Score);
	gotoxy(0, 1);
	printf("\t\t\t    Snake\t\t\t");
	gotoxy(0, 37);
	printf("\t\t   W:↑ S:↓ A:← D:→\n");
	printf("\t\t  开始:切换为大写任意键.\n");
	printf("\t\t  暂停:切换为小写任意键.\n");
}

int Die(void)									//判断是否出界 
{
	Snake* Tmp = Header->Next;
	if (Header->x <= 0 || Header->y <= 0 || Header->x > 50 || Header->y > 24)
	{
		return 1;
	}
	while (Tmp) {
		if (Header->x == Tmp->x && Header->y == Tmp->y) {
			return 1;
		}
		Tmp = Tmp->Next;
	}
	return 0;
}

void Food(void)
{
	Snake* Tmp = Header;
again:
	apple.x = rand() % 23 + 2;
	apple.y = rand() % 23 + 2;
	while (Tmp != NULL) {
		if (Tmp->x == apple.x && Tmp->y == apple.y) {
			Tmp = Header;
			goto again;
		}
		if (apple.x % 2 != 0) {
			goto again;
		}
		Tmp = Tmp->Next;
	}
}

void Initialization(void)
{
	Header = (Snake*)malloc(sizeof(Snake));
	Header->x = 24;
	Header->y = 12;
	Header->Next = NULL;
	Header->Last = NULL;
	return;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	return;
}
