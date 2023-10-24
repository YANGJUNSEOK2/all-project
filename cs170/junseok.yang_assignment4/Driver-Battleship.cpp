
/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Driver-Battleship.cpp
Author: junseok.yang
Creation Date:SPRING/5/25/2019
    Fix the driver test 0~5 class in inheritance & virtual for Boat
    Make the driver new test 6~7 file i/o for Assignment4
******************************************************************************/
#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstring>  // strcmp
#include <cstdlib>  // atoi
#include <fstream>

#include "Point.h"   //inlcude point
#include "Board.h"   //include board
#include "Boat.h"    //include boat
#include "PRNG.h"    //include rand

#define BASE_RANDOM 7
#define BASE_RANDOM2 1

using namespace CS170::BattleShip;


void PrintShotResult(const Board::ShotResult &sr) {
    const char *strings[] = { "HIT", "MISS", "DUPLICATE", "SUNK", "ILLEGAL" };
   // if (sr != Board::ShotResult::SUNK)
    
        std::cout << strings[static_cast<int>(sr)] << std::endl;
    
}

void PrintStats(const Board &board) {
    ShotStats stats = board.GetShotStats();
    std::cout << "      Hits: " << std::setw(3) << stats.hits << std::endl;
    std::cout << "    Misses: " << std::setw(3) << stats.misses << std::endl;
    std::cout << "Duplicates: " << std::setw(3) << stats.duplicates << std::endl;
    std::cout << "Boats Sunk: " << std::setw(3) << stats.sunk << std::endl;
}

void ShootPrintResultDrawPrintStats(Board &board, const CS170::Utils::Point& pt) {
    Board::ShotResult sr;
    std::cout << "Shot: " << pt.x << ", " << pt.y << "  ";
    sr = board.TakeShot(pt);
    if (sr != Board::ShotResult::SUNK)
    {
        PrintShotResult(sr);
    }
    board.DrawBoard(true);
    PrintStats(board);
    std::cout << std::endl;
}

void AddBoatAtRandomPos(Boat *boat, Board *board) {

    boat->FindRandomLocation(*board);
    board->AddBoatToBoard(*boat);
}

void AddBoatPos(Boat *boat, Board *board)
{
    board->GetBoats()[boat->GetBoatValue(Boat::ID) - 1] = boat;
}


void test0() {
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    const int numBoats = 5;
    // Setup the board
    Board *board = new Board(numBoats, 10, 10);

    Carrier boat1(1, "Carrier", 5);
    Battleship boat2(2, "Battleship", 4);
    Cruiser boat3(3, "Cruiser", 3);
    Submarine boat4(4, "Submarine", 3);
    Destroyer boat5(5, "Destroyer", 2);

    AddBoatAtRandomPos(&boat1, board);
    AddBoatAtRandomPos(&boat2, board);
    AddBoatAtRandomPos(&boat3, board);
    AddBoatAtRandomPos(&boat4, board);
    AddBoatAtRandomPos(&boat5, board);


    std::cout << "The board with " << board->GetBoard(Board::NUMBOAT) << " boats" << std::endl;
    board->DrawBoard(true);
    std::cout << std::endl;
	delete board;
}

void test1() {
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    Board *board = new Board(5, 10, 10);

    // Create the ship
    Carrier validBoat(1, { 1, 3 }, Boat::Orientation::HORIZONTAL, "Carrier", 5);
    if (board->IsBoatPositionValid(validBoat) == true) {
        board->AddBoatToBoard(validBoat);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    board->DrawBoard(true);
    std::cout << std::endl;
    Battleship invalidBoat1(2, { -1, 0 }, Boat::Orientation::HORIZONTAL, "Battleship", 4);
    if (board->IsBoatPositionValid(invalidBoat1) == true) {
        board->AddBoatToBoard(invalidBoat1);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    board->DrawBoard(true);
    std::cout << std::endl;
    Battleship invalidBoat2(2, { 7, 0 }, Boat::Orientation::HORIZONTAL, "Battleship", 4);
    if (board->IsBoatPositionValid(invalidBoat2) == true) {
        board->AddBoatToBoard(invalidBoat2);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    board->DrawBoard(true);
    std::cout << std::endl;
    Battleship invalidBoat3(2, { 0, -1 }, Boat::Orientation::VERTICAL, "Battleship", 4);
    if (board->IsBoatPositionValid(invalidBoat3) == true) {
        board->AddBoatToBoard(invalidBoat3);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    board->DrawBoard(true);
    std::cout << std::endl;
    Battleship invalidBoat4(2, { 0, 7 }, Boat::Orientation::VERTICAL, "Battleship", 4);
    if (board->IsBoatPositionValid(invalidBoat4) == true) {
        board->AddBoatToBoard(invalidBoat4);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    board->DrawBoard(true);
    std::cout << std::endl;
    Battleship invalidBoat5(2, { 2, 2 }, Boat::Orientation::VERTICAL, "Battleship", 4);
    if (board->IsBoatPositionValid(invalidBoat5) == true) {
        board->AddBoatToBoard(invalidBoat5);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    board->DrawBoard(true);
    std::cout << std::endl;
	delete board;
}

void test2() {
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    const int numBoats = 5;
    // Setup the board
    Board *board = new Board(numBoats, 10, 10);

    // Create the ships
    Carrier boat1(1, "Carrier", 5);
    Battleship boat2(2, "Battleship", 4);
    Cruiser boat3(3, "Cruiser", 3);
    Submarine boat4(4, "Submarine", 3);
    Destroyer boat5(5, "Destroyer", 2);

    AddBoatAtRandomPos(&boat1, board);
    AddBoatAtRandomPos(&boat2, board);
    AddBoatAtRandomPos(&boat3, board);
    AddBoatAtRandomPos(&boat4, board);
    AddBoatAtRandomPos(&boat5, board);

    std::cout << "The board with " << board->GetBoard(Board::NUMBOAT) << " boats" << std::endl;
    board->DrawBoard(true);
    std::cout << std::endl;

    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ -1, 0 });  // Illegal coordinate
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 10, 0 });  // Illegal coordinate
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 0, -1 });  // Illegal coordinate
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 0, 10 });  // Illegal coordinate
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 2, 7 });  // HIT
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 3, 7 });  // HIT
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 2, 7 });  // DUPLICATE
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 4, 7 });  // HIT
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 5, 7 });  // HIT
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 6, 7 });  // SUNK
	delete board;
}

void test3() {
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    const int numBoats = 5;
    // Setup the board
    Board *board = new Board(numBoats, 10, 10);

    // Create the ships
    Carrier boat1(1, "Carrier", 5);
    Battleship boat2(2, "Battleship", 4);
    Cruiser boat3(3, "Cruiser", 3);
    Submarine boat4(4, "Submarine", 3);
    Destroyer boat5(5, "Destroyer", 2);

    AddBoatAtRandomPos(&boat1, board);
    AddBoatAtRandomPos(&boat2, board);
    AddBoatAtRandomPos(&boat3, board);
    AddBoatAtRandomPos(&boat4, board);
    AddBoatAtRandomPos(&boat5, board);

    // Try to sink the boats with random shots
    int shots = 0;
    int num_boats = 5;
    while (num_boats > 0) {
        Board::ShotResult sr;
        do {
            CS170::Utils::Point shot;
            shot.x = CS170::Utils::Random(0, board->GetBoard(Board::WIDTH) - 1);
            shot.y = CS170::Utils::Random(0, board->GetBoard(Board::HEIGHT) - 1);
            std::cout << "Shot #"
                << ++shots
                << " at coordinate "
                << shot.x
                << ", "
                << shot.y
                << "  ";

            sr = board->TakeShot(shot);
            PrintShotResult(sr);
        } while (sr == Board::ShotResult::DUPLICATE);

        // Sunk a boat
        if (sr == Board::ShotResult::SUNK) {
            num_boats--;
        }

        board->DrawBoard(true);
        std::cout << std::endl;
    }
    PrintStats(*board);

	delete board;
}

void test4() {
    int num_boats = 8;
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    const int numBoats = 8;
    // Setup the board
    Board *board = new Board(numBoats, 8, 12);

    // Create the ships
    Carrier boat1(1, "Carrier", 5);
    Battleship boat2(2, "Battleship", 4);
    Cruiser boat3(3, "Cruiser", 3);
    Submarine boat4(4, "Submarine", 3);
    Destroyer boat5(5, "Destroyer", 2);
    Battleship boat6(6, "Battleship", 4);
    Cruiser boat7(7, "Cruiser", 3);
    Destroyer boat8(8, "Destroyer", 2);

    AddBoatAtRandomPos(&boat1, board);
    AddBoatAtRandomPos(&boat2, board);
    AddBoatAtRandomPos(&boat3, board);
    AddBoatAtRandomPos(&boat4, board);
    AddBoatAtRandomPos(&boat5, board);
    AddBoatAtRandomPos(&boat6, board);
    AddBoatAtRandomPos(&boat7, board);
    AddBoatAtRandomPos(&boat8, board);

    board->DrawBoard(true);
    std::cout << std::endl << std::endl;

    // Try to sink the boats with random shots
    while (num_boats > 0) {
        Board::ShotResult sr;
        do {
            CS170::Utils::Point shot;

            shot.x = CS170::Utils::Random(0, board->GetBoard(Board::WIDTH) - 1);
            shot.y = CS170::Utils::Random(0, board->GetBoard(Board::HEIGHT) - 1);
            sr = board->TakeShot(shot);
        } while (sr == Board::ShotResult::DUPLICATE);

        // Sunk a boat
        if (sr == Board::ShotResult::SUNK) {
            num_boats--;
        }
    }
    board->DrawBoard();
    PrintStats(*board);

	delete board;
}

void test5() {
    int numBoats = 100;
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);
    // Setup the board
    Board *board = new Board(numBoats, 30, 30);

    // Create the ships
    for (int i = 0; i < numBoats; i += 5) {
        Carrier *boat1 = new Carrier(i + 1, "Carrier", 5);
        Battleship *boat2 = new Battleship(i + 2, "Battleship", 4);
        Cruiser *boat3 = new Cruiser(i + 3, "Cruiser", 3);
        Submarine *boat4 = new Submarine(i + 4, "Submarine", 3);
        Destroyer *boat5 = new Destroyer(i + 5, "Destroyer", 2);

        AddBoatAtRandomPos(boat1, board);
        AddBoatAtRandomPos(boat2, board);
        AddBoatAtRandomPos(boat3, board);
        AddBoatAtRandomPos(boat4, board);
        AddBoatAtRandomPos(boat5, board);
    }

    board->DrawBoard(true);
    std::cout << std::endl << std::endl;

    // Try to sink the boats with random shots
    while (numBoats > 0) {
        Board::ShotResult sr;
        do {
            CS170::Utils::Point shot;

            shot.x = CS170::Utils::Random(0, board->GetBoard(Board::WIDTH) - 1);
            shot.y = CS170::Utils::Random(0, board->GetBoard(Board::HEIGHT) - 1);
            sr = board->TakeShot(shot);
        } while (sr == Board::ShotResult::DUPLICATE);

        // Sunk a boat
        if (sr == Board::ShotResult::SUNK) {
            numBoats--;
        }
    }
    board->DrawBoard();
    std::cout << std::endl;
    PrintStats(*board);

    board->DestroyBoats();
	delete board;
}

void test6() {

    std::ofstream file_out;
    file_out.open("file_Out.txt", std::ios_base::out | std::ios_base::binary);

    const int FILE_HIT_OFFSET = 100;
    int numBoats = 100, numBoat = 100, width = 30, height = 30;
    int count = 0;
    bool showboat = false;
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);
    // Setup the board
    Board *board = new Board(numBoats, 30, 30);

    // Create the ships
    for (int i = 0; i < numBoats; i += 5) {
        Carrier *boat1 = new Carrier(i + 1, "Carrier", 5);
        Battleship *boat2 = new Battleship(i + 2, "Battleship", 4);
        Cruiser *boat3 = new Cruiser(i + 3, "Cruiser", 3);
        Submarine *boat4 = new Submarine(i + 4, "Submarine", 3);
        Destroyer *boat5 = new Destroyer(i + 5, "Destroyer", 2);

        AddBoatAtRandomPos(boat1, board);
        AddBoatAtRandomPos(boat2, board);
        AddBoatAtRandomPos(boat3, board);
        AddBoatAtRandomPos(boat4, board);
        AddBoatAtRandomPos(boat5, board);
    }

    board->DrawBoard(true);
    std::cout << std::endl << std::endl;

    file_out << numBoats << " " << width << " " << height << std::endl;

    file_out << std::endl;

    CS170::Utils::Point shot;
    // Try to sink the boats with random shots
    while (numBoats > 0 && count < 500) {
        Board::ShotResult sr;
        do {

            shot.x = CS170::Utils::Random(0, board->GetBoard(Board::WIDTH) - 1);
            shot.y = CS170::Utils::Random(0, board->GetBoard(Board::HEIGHT) - 1);
            sr = board->TakeShot(shot);

        } while (sr == Board::ShotResult::DUPLICATE);
        // Sunk a boat
        if (sr == Board::ShotResult::SUNK) {
            numBoats--;
        }
        count++;
    }
    
    board->DrawBoard();

    std::cout << std::endl;

    for (int y = 0; y < board->GetBoard(Board::HEIGHT); y++)
    {
        for (int x = 0; x < board->GetBoard(Board::WIDTH); x++)
        {
            int value = board->GetBoardValue(CS170::Utils::Point{ x, y });
            if ((value > 0) && (value < FILE_HIT_OFFSET) && (showboat == true))
            {
                value = 0;
            }
            file_out << std::setw(4) << value;
        }
        file_out << std::endl;
    }

    file_out << std::endl;

    ShotStats file_stats = board->GetShotStats();
    file_out << file_stats.hits << std::endl;
    file_out << file_stats.misses << std::endl;
    file_out << file_stats.duplicates << std::endl;
    file_out << file_stats.sunk << std::endl;

    for (int i = 0; i < numBoat; i++)
    {
        file_out << board->GetBoats()[i]->GetId() << "   ";
        file_out << static_cast<int>(board->GetBoats()[i]->GetOrientation()) << "   ";
        file_out << board->GetBoats()[i]->GetLength() << "   ";
        file_out << board->GetBoats()[i]->GetHitsUntilSunk() << "   ";
        file_out << board->GetBoats()[i]->GetLocation().x << "   ";
        file_out << board->GetBoats()[i]->GetLocation().y << std::endl;
    }
    file_out << std::endl;

    PrintStats(*board);
    file_out.close();
    board->DestroyBoats();
	delete board;
}

void test7()
{
    std::ifstream file_in;
    file_in.open("file_Out.txt", std::ios_base::in | std::ios_base::binary);

    int numBoat = 100;
    int numBoats = 0;
    int width = 0;
    int height = 0;
    int boardValue = 0;
    int hits = 0, misses = 0, duplicates = 0, boatsSunk = 0;
    int id = 0, orientation = 0, length = 0, hitUntilSunk = 0, locationX = 0, locationY = 0;

    file_in >> numBoats >> width >> height;

    // Setup the board
    Board *board = new Board(numBoats, width, height);

    for (int y = 0; y < board->GetBoard(Board::HEIGHT); y++)
    {
        for (int x = 0; x < board->GetBoard(Board::WIDTH); x++)
        {
            file_in >> boardValue;
            board->SetBoardValue({x,y}, boardValue);
        }
    }

    file_in >> hits >> misses >> duplicates >> boatsSunk;
    
    
    board->SetBoard(hits, Board::BoardValue::SHOTSTATS_HIT);
    board->SetBoard(duplicates, Board::BoardValue::SHOTSTATS_DUPLICATE);
    board->SetBoard(misses, Board::BoardValue::SHOTSTATS_MISS);
    board->SetBoard(boatsSunk, Board::BoardValue::SHOTSTATS_SUNK);

    // Create the ships
    for (int i = 0; i < numBoat; i++) {

        file_in >> id >> orientation >> length >> hitUntilSunk >> locationX >> locationY;

        if (id % 5 == 0)
        {
            Destroyer* m_boat5 = new Destroyer(id, { locationX, locationY }, static_cast<Boat::Orientation>(orientation), "Destroyer", length);
            board->GetBoats()[m_boat5->GetBoatValue(Boat::ID) - 1] = m_boat5;
            //AddBoatPos(m_boat5, board);
            m_boat5->SetHitsUntilSunk(hitUntilSunk);

        }
        else if(id % 5 == 1)
        {
            Carrier *m_boat1 = new Carrier(id, { locationX, locationY }, static_cast<Boat::Orientation>(orientation), "Carrier", length);
            //AddBoatPos(m_boat1, board);
            board->GetBoats()[m_boat1->GetBoatValue(Boat::ID) - 1] = m_boat1;
            m_boat1->SetHitsUntilSunk(hitUntilSunk);
        }
        else if (id % 5 == 2)
        {
            Battleship *m_boat2 = new Battleship(id, { locationX, locationY }, static_cast<Boat::Orientation>(orientation), "Battleship", length);
            //AddBoatPos(m_boat2, board);
            board->GetBoats()[m_boat2->GetBoatValue(Boat::ID) - 1] = m_boat2;
            m_boat2->SetHitsUntilSunk(hitUntilSunk);
        }
        else if (id % 5 == 3)
        {
            Cruiser *m_boat3 = new Cruiser(id, { locationX, locationY }, static_cast<Boat::Orientation>(orientation), "Cruiser", length);
            //AddBoatPos(m_boat3, board);
            board->GetBoats()[m_boat3->GetBoatValue(Boat::ID) - 1] = m_boat3;
            m_boat3->SetHitsUntilSunk(hitUntilSunk);
        }
        else if (id % 5 == 4)
        {
            Submarine *m_boat4 = new Submarine(id, { locationX, locationY }, static_cast<Boat::Orientation>(orientation), "Submarine", length);
            //AddBoatPos(m_boat4, board);
            board->GetBoats()[m_boat4->GetBoatValue(Boat::ID) - 1] = m_boat4;
            m_boat4->SetHitsUntilSunk(hitUntilSunk);
        }
    }

    board->DrawBoard();
    std::cout << std::endl;
    PrintStats(*board);
    std::cout << std::endl;

    for(int i=0;i<numBoats;i++)
    {
        if (board->GetBoats()[i]->GetHitsUntilSunk() == 0)
        {
            numBoat--;
        }
    }

    // Try to sink the boats with random shots
    CS170::Utils::Point test_shot;
     while (numBoat > 0 ) {
        Board::ShotResult m_sr;
        do {

            test_shot.x = CS170::Utils::Random(0, board->GetBoard(Board::WIDTH) - 1);
            test_shot.y = CS170::Utils::Random(0, board->GetBoard(Board::HEIGHT) - 1);
            m_sr = board->TakeShot(test_shot);
        } while (m_sr == Board::ShotResult::DUPLICATE);

        //Sunk a boat
        if (m_sr == Board::ShotResult::SUNK) {
            numBoat--;
        }
    }
    board->DrawBoard();
    std::cout << std::endl;
    PrintStats(*board);

    file_in.close();

    board->DestroyBoats();
	delete board;
}

int main(int argc, char **argv) {
    int test_num = 7;

    if (argc > 1) {
        if (strcmp(argv[1], "all") == 0)
            test_num = -1;
        else
            test_num = std::atoi(argv[1]);
    }

    switch (test_num) {
    case 0:
        test0();
        break;

    case 1:
        test1();
        break;

    case 2:
        test2();
        break;

    case 3:
        test3();
        break;

    case 4:
        test4();
        break;

    case 5:
        test5();
        break;

    case 6:
        test6();
        break;

    case 7:
        test7();
        break;

    default:
        test0();
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
        break;
    }

    return 0;
}