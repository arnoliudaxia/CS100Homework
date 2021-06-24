#pragma warning(disable : 4996)
#include <stdio.h>
#include <math.h>
#define E 63

int main()
{
    int input = 0;
    scanf("%x", &input);
   // input = 0b00111110001000000000000000000000;
    int sign = input >> 31;
    int exponent = (input >>24)-sign*pow(2,7);
    int fraction = input & 0b00000000111111111111111111111111;
    float adder = 0;
    
    for (int i = 0; i < 24; i++)
    {
        if (fraction&(1<<i))
            adder += 1.0 / pow(2 , (24-i));
    }
    float result = pow((-1) , sign) * (1 + adder) * pow(2,exponent-E);
    //printf("%f", result);
    printf("The number converts to %f\n", result);
}


