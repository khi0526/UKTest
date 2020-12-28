#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Conio.h>
#include <Windows.h>

#define LINE 15
#define TIME 600

#define ZERO 48
#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53
#define SIX 54
#define SEVEN 55
#define EIGHT 56
#define NINE 57
#define DELETE 8

void init(int);
void setNum(int,int);
void countdown(int);
int processKey(int);
void gotoxy(int, int);
void numofPut(int);
int corCheck(int,int);

int num[30][120];   // LINE 최대 15*2 VOLUME 최대 120

int main()
{
    int timeout = TIME;
    int key, row = 0, vol = 0;

    printf("모니터의 가로 길이에 따라 한 줄당 숫자 개수를 설정하세요. \n 1. 80개 2. 100개 3. 120개 \n :");
    while (vol == 0)
    {
        key = _getch();
        if (key >= ONE && key <= THREE)
        {
            printf(" %d", processKey(key));
            vol = 60 + (20 * processKey(key));
        }
    }

    printf("\n 한 줄당 1분 총 15줄 아무 키나 클릭시 3초 후 시작 (숫자 제외)");
    while (!(key < ZERO || key > NINE))
        key = _getch();
    system("cls");
    printf("\n");
    countdown(3);

    while (2)
    {
        init(vol);
        for (int i = 0; i < LINE; i++)
        {
            setNum(i, vol);
            row = 0;
            timeout = TIME;
            printf("\n\n");
            for (int j = 0; j < vol; j++)
                printf("%d ", num[i][j]);
            printf("\n");
            while (3)
            {
                if (_kbhit())
                {
                    key = _getch();
                    if (key >= ZERO && key <= NINE)
                    {
                        printf(" %d", processKey(key));
                        num[i+15][row++] = processKey(key);
                    }
                    if (key == DELETE && row > 0)
                    {
                        num[i + 15][--row] = -1;
                        gotoxy(row*2, i*3 + 4);
                        printf("  ");
                        gotoxy(row*2, i*3 + 4);
                    }
                    if (row == vol - 1)
                    {
                        printf("\n");
                        break;
                    }
                }
                if (timeout == 0)
                    break;
                timeout--;
                Sleep(100);
            }
        }
        numofPut(vol);
        printf("틀린 개수 %d개 정확도 %d \n\n다시 시작하려면 아무 키나 입력 (5초 뒤 시작, 숫자 제외)", corCheck(1, vol), corCheck(2, vol));
        Sleep(3000);
        while (!(key < ZERO || key > NINE))
            key = _getch();
        system("cls");
        numofPut(vol);
        countdown(5);
    }
    return 0;
}

void init(int vol)
{
    srand(time(NULL));
    for (int i = 0; i < LINE + 15; i++)
        for (int j = 0; j < vol; j++)
            num[i][j] = -1;
}

void setNum(int i, int vol)
{
    num[i][0] = rand() % 9 + 1;
    for (int j = 1; j < vol; j++)
        do
        {
            num[i][j] = rand() % 9 + 1;
        } while (num[i][j] == num[i][j - 1]);
}

void countdown(int i)
{
    for (i; i > 0; i--)
    {
        printf(" %d", i);
        Sleep(1000);
    }
}

int processKey(int key)
{
    switch (key)
    {
    case ZERO:
        return 0;
    case ONE:
        return 1;
    case TWO:
        return 2;
    case THREE:
        return 3;
    case FOUR:
        return 4;
    case FIVE:
        return 5;
    case SIX:
        return 6;
    case SEVEN:
        return 7;
    case EIGHT:
        return 8;
    case NINE:
        return 9;
    }
}

void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void numofPut(int vol)
{
    int a, avg = 0;
    printf("\n\n");
    for (int j = 0; j < LINE; j++)
    {
        a = 0;
        for (int k = 0; k < vol - 1; k++)
        {
            if (num[j+15][k] == -1)
                break;
            a++;
        }
        printf("%d ", a);
        avg += a;
    }
    printf("평균 %d \n", avg / LINE );
}

int corCheck(int a, int vol)
{
    double correct = 0;
    int count = 0;
    for (int i = 0; i < LINE; i++)
        for (int j = 0; j < vol - 1; j++)
        {
            if (num[i+15][j] == -1)
                break;
            count++;
            if ((num[i][j] + num[i][j + 1]) % 10 == num[i + 15][j])
                correct++;
        }
    if (a == 1)
        return count - correct;
    return correct / count * 100;
}