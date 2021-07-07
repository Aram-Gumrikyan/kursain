#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

void generateMatrix(int height, int width, int (*arr)[width]);
void upwardMovement(int height, int width, int (*arr)[width]);
int getNumberFromUser(char name[]);
void copyArray(int width, int *dest, int *root);
void putArr(int height, int width, int (*arr)[width], int delay);

int main()
{
    int width = getNumberFromUser("width");
    int height = getNumberFromUser("height");

    int arr[height][width];

    generateMatrix(height, width, arr);
    putArr(height, width, arr, 0);
    Sleep(3000);

    while (true)
    {
        upwardMovement(height, width, arr);
        putArr(height, width, arr, 500);
    }

    return 0;
}

int getNumberFromUser(char name[])
{
    int value;

    printf("please enter %s of your array - from 2 to 101 (default-4): ", name);
    scanf("%d", &value);

    if (value < 2 || value > 100)
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
            *(*(arr + i) + j) = rand() % 99;
        }
    }
}

void upwardMovement(int height, int width, int (*arr)[width])
{
    int firstRow[width];
    copyArray(width, firstRow, *(arr + 0));

    for (int i = 1; i < height; i++)
    {
        copyArray(width, *(arr + i - 1), *(arr + i));
    }

    copyArray(width, *(arr + height - 1), firstRow);
}

void copyArray(int width, int *dest, int *root)
{
    for (int i = 0; i < width; i++)
    {
        *(dest + i) = *(root + i);
    }
}

void putArr(int height, int width, int (*arr)[width], int delay)
{
    COORD pos;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    pos.Y = 8;
    pos.X = 30;

    for (int i = 0; i < height; i++)
    {
        SetConsoleCursorPosition(hConsole, pos);

        for (int j = 0; j < width; j++)
        {
            printf("%3d", *(*(arr + i) + j));

            if (!delay)
            {
                continue;
            }

            for (int k = 0; k < 127; k++)
            {
                if (GetAsyncKeyState(k) && i != 0)
                {
                    ExitProcess(0);
                }
            }

            // Sleep(delay); //animation type 1
        }

        pos.Y += 1;

        Sleep(delay); //animation type 2
    }
}

//