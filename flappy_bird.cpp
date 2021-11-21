#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_',' ','>' };
int birdPos = 6;
int score = 0;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBorder() {

	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		gotoxy(i, 0);
		cout << "=";
		gotoxy(i, SCREEN_HEIGHT);
		cout << "=";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << "||";
		gotoxy(SCREEN_WIDTH, i);
		cout << "||";
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		gotoxy(WIN_WIDTH, i);
		cout << "||";
	}
}

void genPipe(int ind)
{
	gapPos[ind] = 3 + rand() % 10;
}

void drawPipe(int ind)
{
	if (pipeFlag[ind] == true)
	{
		for (int i = 0; i < gapPos[ind]; i++)
		{
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "***";
		}
		for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++)
		{
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "***";
		}
	}
}
void delPipe(int ind)
{
	if (pipeFlag[ind] == true)
	{
		for (int i = 0; i < gapPos[ind]; i++)
		{
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
		for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++)
		{
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
	}
}

void drawBird()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			gotoxy(j + 2, i + birdPos);
			cout << bird[i][j];
		}
	}
}
void delBird()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			gotoxy(j + 2, i + birdPos); cout << " ";
		}
	}
}

int collision()
{
	if (pipePos[0] >= 61)
	{
		if (birdPos<gapPos[0] || birdPos >gapPos[0] + GAP_SIZE)
		{
			return 1;
		}
	}
	return 0;
}

void gameover()
{
	system("cls");
	gotoxy(45, 12);
	cout << "--------------------------" << endl;
	gotoxy(45, 13);
	cout << "-------- Game Over -------" << endl;
	gotoxy(45, 14);
	cout << "--------------------------" << endl << endl;
	gotoxy(45, 15);
	cout << "Press any key to go back to menu.";
	_getch();
}
void updateScore()
{
	gotoxy(WIN_WIDTH + 7, 5);
	cout << "Score: " << score << endl;
}


void play()
{
	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;

	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();

	gotoxy(WIN_WIDTH + 5, 2); 
	cout << "FLAPPY BIRD";
	gotoxy(WIN_WIDTH + 6, 4); 
	cout << "----------";


	gotoxy(20, 12); cout << "Press any key to start";
	_getch();
	gotoxy(20, 12); cout << "                      ";

	while (1)
	{

		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 32)
			{
				if (birdPos > 3)
					birdPos -= 3;
			}
			if (ch == 27)
			{
				break;
			}
		}

		drawBird();
		drawPipe(0);
		drawPipe(1);
		if (collision())
		{
			gameover();
			return;
		}
		Sleep(100);
		delBird();
		delPipe(0);
		delPipe(1);
		birdPos += 1;

		if (birdPos > SCREEN_HEIGHT - 2)
		{
			gameover();
			return;
		}

		if (pipeFlag[0] == 1)
			pipePos[0] += 2;

		if (pipeFlag[1] == 1)
			pipePos[1] += 2;

		if (pipePos[0] >= 40 && pipePos[0] < 42)
		{
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if (pipePos[0] > 68)
		{
			score++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}

	}

}

int main()
{
	srand(time(NULL));
	do
	{
		system("cls");
		gotoxy(45, 8); cout << " -------------------------- ";
		gotoxy(45, 9); cout << " |      Flappy Bird       | ";
		gotoxy(45, 10); cout << " --------------------------";
		gotoxy(45, 12); cout << "1. Start Game";
		gotoxy(45, 14); cout << "2. Quit";
		gotoxy(45, 16); cout << "Select option: ";
		char op = _getch();

		if (op == '1')
			play();
		else if (op == '2') exit(0);

	} while (1);

	return 0;
}