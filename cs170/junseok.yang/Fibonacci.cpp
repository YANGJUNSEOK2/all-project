/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author:junseok.yang
Creation Date:Spring 2019.3.25
cs170 lab3
******************************************************************************/
#include "WriteData.h"
#include"Fibonacci.h"

namespace CS170
{
    namespace Lap2
    {
        int FibonacciCalculation(int& prevTotal, int& currTotal)
        {
            int nextTotal = prevTotal + currTotal;
            prevTotal = currTotal;
            currTotal = nextTotal;

            return currTotal;
        }

        void WriteFibonacciHeader()
        {
            WriteColumn("Fibonaci");
            WriteColumn("Fibonaci");
            std::cout << std::endl;
            WriteColumn("N",column1Width);
            WriteColumn("number",18);
            WriteColumn("quotient");
            std::cout << std::endl;
            for(int i=1;i<=40;i++)
            {
                std::cout << "-";
            }
            std::cout << std::endl;
        }
        void Fibonacci(int value)
        {
            WriteFibonacciHeader();
            int num1 = 0;
            int num2 = 1;
            WriteColumn(num1, column1Width);
            WriteColumn(num1,18);
            WriteColumn("N/A");
            std::cout << std::endl;
            WriteColumn(num2, column1Width);
            WriteColumn(num2,18);
            WriteColumn("N/A");
            std::cout << std::endl;

            int lastTotal = 0;
            int currTotal = 1;

            for (int i = 2; i <= value; i++)
            {
                int beforeNum = i;
                int nextNum = i + 1;
                WriteColumn(i, column1Width);
                
                
                WriteColumn(FibonacciCalculation(lastTotal, currTotal),18);
                WriteColumn(((double)currTotal) / lastTotal);
                std::cout << std::endl;

            }
        }
    }
}

