/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Queens.hpp
Project: Lab 3 - Recurssion
Author: 
Creation date: 
******************************************************************/

template<int BOARDSIZE>
void Queens<BOARDSIZE>::PrintSolution() {
    std::cout << "-------------------------------" << std::endl;
    for (int y = 0; y < BOARDSIZE; y++) {
        for (int x = 0; x < BOARDSIZE; x++) {
            if (board[y][x] == true) {
                std::cout << "X ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}