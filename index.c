#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

int getNumberFromUser(char name[]);
void generateMatrix(int height, int width, int (*arr)[width]);
void upwardAnimation(int height, int width, int (*arr)[width], int rowNumber);
void upwardAnimationSimpleFactory(int width, int (*arr)[width], int rowNumber, int part);
void upwardAnimationPart1(int width, int (*arr)[width], int rowNumber);
void upwardAnimationPart2(int width, int (*arr)[width], int rowNumber);
void upwardAnimationPart3(int width, int (*arr)[width], int rowNumber);
void upwardAnimationPart4(int width, int (*arr)[width], int rowNumber);
void putArr(int height, int width, int (*arr)[width]);

int main()
{
    int width = getNumberFromUser("width") * 2;
    int height = getNumberFromUser("height") * 2;

    int arr[height][width];

    generateMatrix(height, width, arr);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (!arr[i][j])
            {
                printf("   ");
                continue;
            }

            printf("%3d", arr[i][j]);
        }

        printf("%c", '\n');
    }

    Sleep(1000);

    while (true)
    {
        for (int i = 0; i < height - 2; i++)
        {
            if (i % 2 != 0)
            {
                continue;
            }

            upwardAnimation(height, width, arr, i);
        }
    }

    return 0;
}

int getNumberFromUser(char name[])
{
    int value;

    printf("please enter %s of your array - from 2 to 10 (default-4): ", name);
    scanf("%d", &value);

    if (value < 2 || value > 10)
    {
        value = 4;
    }

    return value;
}

void generateMatrix(int height, int width, int (*arr)[width])
{
    srand(time(0));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i % 2 == 1 || j % 2 == 1)
            {
                *(*(arr + i) + j) = 0;
                continue;
            }

            *(*(arr + i) + j) = rand() % 98 + 1;
        }
    }
}

void upwardAnimation(int height, int width, int (*arr)[width], int rowNumber)
{
    for (int i = 1; i < 5; i++)
    {
        upwardAnimationSimpleFactory(width, arr, rowNumber, i);
        putArr(height, width, arr);
        for (int k = 1; k < 128; k++)
        {
            if (GetAsyncKeyState(k) && i != 1)
            {
                ExitProcess(0);
            }
        }
        Sleep(1000);
    }
}

void upwardAnimationSimpleFactory(int width, int (*arr)[width], int rowNumber, int part)
{
    switch (part)
    {
        case 1: 
            upwardAnimationPart1(width, arr, rowNumber);
            break;
        case 2:
            upwardAnimationPart2(width, arr, rowNumber);
            break;
        case 3:
            upwardAnimationPart3(width, arr, rowNumber);
            break;
        case 4:
            upwardAnimationPart4(width, arr, rowNumber);
            break;
    }
}

void upwardAnimationPart1(int width, int (*arr)[width], int rowNumber)
{
    int bottomIndex = rowNumber + 2;

    for (int j = 0; j < width; j++)
    {
        if (j % 2 == 1)
        {
            *(*(arr + bottomIndex) + j) = *(*(arr + bottomIndex) + j - 1);
            *(*(arr + bottomIndex) + j - 1) = 0;
        }
    }
}

void upwardAnimationPart2(int width, int (*arr)[width], int rowNumber)
{
    int bottomIndex = rowNumber + 2;

    for (int j = 0; j < width; j++)
    {
        if (j % 2 == 1)
        {
            *(*(arr + bottomIndex - 1) + j) = *(*(arr + bottomIndex) + j);
            *(*(arr + bottomIndex) + j) = 0;
        }
    }
}

void upwardAnimationPart3(int width, int (*arr)[width], int rowNumber)
{
    int middleIndex = rowNumber + 1;

    for (int j = 0; j < width; j++)
    {
        if (j % 2 == 0)
        {
            *(*(arr + middleIndex) + j) = *(*(arr + middleIndex - 1) + j);
            *(*(arr + middleIndex - 1) + j) = 0;
        } else
        {
            *(*(arr + middleIndex - 1) + j) = *(*(arr + middleIndex) + j);
            *(*(arr + middleIndex) + j) = 0;
        }
    }
}

void upwardAnimationPart4(int width, int (*arr)[width], int rowNumber)
{
    for (int j = 0; j < width; j++)
    {
        if (j % 2 == 0)
        {
            *(*(arr + rowNumber + 2) + j) = *(*(arr + rowNumber + 1) + j);
            *(*(arr + rowNumber + 1) + j) = 0;
            *(*(arr + rowNumber) + j) = *(*(arr + rowNumber) + j + 1);
            *(*(arr + rowNumber) + j + 1) = 0;
        }
    }
}

void putArr(int height, int width, int (*arr)[width])
{
    COORD pos;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    pos.Y = height * 2;
    pos.X = width * 2;

    for (int i = 0; i < height; i++)
    {
        SetConsoleCursorPosition(hConsole, pos);

        for (int j = 0; j < width; j++)
        {
            if (!*(*(arr + i) + j))
            {
                printf("   ");
            } else 
            {
                printf("%3d", *(*(arr + i) + j));
            }
        }

        pos.Y += 1;
    }
}
