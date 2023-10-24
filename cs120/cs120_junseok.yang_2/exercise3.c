/**
    \file        exercise3.c
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS120
    \par         lab: 2
    \date        10/5/2018
    \brief
        Write a program that prompts a user to enter a floating point number. Print out that number.
   */
#include<stdio.h>

int main(void)
{
    float origin_num, plus, Squared, Cubed, Divide;

    scanf("%f", &origin_num);

    plus = origin_num + 10;
    Squared = origin_num * origin_num;
    Cubed = origin_num * origin_num*origin_num;
    Divide = origin_num / 2;

    printf("Please enter a floating point number: %f\n%f\n%f\n%f\n", plus, Squared, Cubed, Divide);

    return 0;
}