#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double func(double x) 
    { 
        return exp(x*5.8) + sin(x+3.5); 
    }

int main(int argc, char *argv[])
{
    srand(time(0));

    double start = -5.6, finish = -1.0, e = 1e-6, mid = (finish + start) / 2.0;

    if (func(start) * func(finish) > 0)
    {
        printf("Couldn`t find\n");
        exit(0);
    }

    while (fabs(func(mid)) >= e)
    {
        mid = (finish + start) / 2.0;
        if (func(mid) > 0)
        {
            start = (func(start) > func(finish)) ? mid : start;
            finish = (func(start) < func(finish)) ? mid : finish;
        }
        else
        {
            start = (func(start) < func(finish)) ? mid : start;
            finish = (func(start) > func(finish)) ? mid : finish;
        }
    }

    printf("Zero: %lF\n", start);

    return 0;
}