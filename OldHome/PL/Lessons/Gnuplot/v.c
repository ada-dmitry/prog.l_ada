#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define E 1.0E-5
#define A1 -2.0
#define B1 -1.5
#define A2 -1.0
#define B2  0.0

char *sf1 = "[-3:1] sin(2*x)-exp(x)\"";
char *sf2 = "[-3:1] sin(2*x)+exp(x)\"";
char *gpl = "gnuplot -p -e \"plot ";

#define DBG    
//gcc filename.c -l m -o filename
double f1(double x) {
     return sin(2*x)-exp(x);
}
double f2(double x) {
     return sin(2*x)+exp(x);
}

double dih(double f(), double a, double b);

int main(){
    char cmd[128] = "\0";
    strcat(cmd,gpl);
    strcat(cmd,sf1);
    printf("%s\n", cmd);
    system(cmd);
    printf("X1 = %.10F\n",dih(f1,A1,B1));
    printf("X2 = %F\n",dih(f2,A2,B2));
    return 0;
}

double dih(double f(), double a, double b){
    double c;	
    while( fabs(b-a) > E ) {
       c = (a+b)/2;
#ifdef DBG       
       printf ("%F \n", c );
#endif
       if(f(a)*f(c) < 0 )
           b = c;
       else
           a = c;
    }
    return c;
}
