/**
    \file        exercise2.c
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS120
    \par         lab: 2
    \date        10/5/2018
    \brief
        Write a program that asks the user to enter a Positive three digit number
   */
#include<stdio.h>

int main(void)
{
    int origin_num;

    scanf("%d", &origin_num);

    int Opposite1 = origin_num % 10;
    int Opposite3 = origin_num / 100;
    int Opposite2 = origin_num / 10 - Opposite3 * 10;

    printf("Please enter a three digit, positive number: %d%d%d\n", Opposite1, Opposite2, Opposite3);
    
    return 0;
}