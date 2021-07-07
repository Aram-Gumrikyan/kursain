#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

void sleep(int sleepTime)
{
    clock_t start = clock();
    clock_t now;

    do
    {
        now = clock();
    } while (now - start != sleepTime);
}