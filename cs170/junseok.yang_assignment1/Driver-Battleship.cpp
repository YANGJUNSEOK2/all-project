
#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstring>  // strcmp
#include <cstdlib>  // atoi

#include "Point.h"
#include "Board.h"
#include "Boat.h"
#include "PRNG.h"

#define BASE_RANDOM 6
#define BASE_RANDOM2 1

using namespace CS170::BattleShip;

void PrintShotResult(const ShotResult &sr) {
    const char *strings[] = { "HIT", "MISS", "DUPLICATE", "SUNK", "ILLEGAL" };
    std::cout << strings[static_cast<int>(sr)] << std::endl;
}

void PrintStats(const Board &board) {
    ShotStats stats = GetShotStats(board);
    std::cout << "      Hits: " << std::setw(3) << stats.hits << std::endl;
    std::cout << "    Misses: " << std::setw(3) << stats.misses << std::endl;
    std::cout << "Duplicates: " << std::setw(3) << stats.duplicates << std::endl;
    std::cout << "Boats Sunk: " << std::setw(3) << stats.sunk << std::endl;
}

void ShootPrintResultDrawPrintStats(Board &board, const CS170::Utils::Point& pt) {
    ShotResult sr;
    std::cout << "Shot: " << pt.x << ", " << pt.y << "  ";
    sr = TakeShot(board, pt);
    PrintShotResult(sr);
    DrawBoard(board, true);
    PrintStats(board);
    std::cout << std::endl;
}

void test0() {
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    const int numBoats = 5;
    // Setup the board
    Board *board = CreateBoard(numBoats, 10, 10);

    // Create the ships
    Boat boats[numBoats];
    for (int i = 0; i < numBoats; i++) {
        InitRandomLocation(boats[i], i + 1, *board);
        AddBoatToBoard(*board, boats[i]);
    }

    std::cout << "The board with " << board->numBoats << " boats" << std::endl;
    DrawBoard(*board, true);
    std::cout << std::endl;
    DestroyBoard(board);
}

void test1() {
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    Board *board = CreateBoard(5, 10, 10);

    // Create the ships
    Boat validBoat;
    validBoat.id = 1;
    Boat invalidBoat;
    invalidBoat.id = 2;

    InitBoatAndPlace(validBoat, CS170::Utils::Point{ 1, 3 }, Orientation::HORIZONTAL);  // valid placement
    if (IsBoatPositionValid(*board, validBoat) == true) {
        AddBoatToBoard(*board, validBoat);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    DrawBoard(*board, true);
    std::cout << std::endl;

    InitBoatAndPlace(invalidBoat, CS170::Utils::Point{ -1, 0 }, Orientation::HORIZONTAL);  // invalid placement
    if (IsBoatPositionValid(*board, invalidBoat) == true) {
        AddBoatToBoard(*board, invalidBoat);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    DrawBoard(*board, true);
    std::cout << std::endl;

    InitBoatAndPlace(invalidBoat, CS170::Utils::Point{ 7, 0 }, Orientation::HORIZONTAL);  // invalid placement
    if (IsBoatPositionValid(*board, invalidBoat) == true) {
        AddBoatToBoard(*board, invalidBoat);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    DrawBoard(*board, true);
    std::cout << std::endl;

    InitBoatAndPlace(invalidBoat, CS170::Utils::Point{ 0, -1 }, Orientation::VERTICAL);  // invalid placement
    if (IsBoatPositionValid(*board, invalidBoat) == true) {
        AddBoatToBoard(*board, invalidBoat);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    DrawBoard(*board, true);
    std::cout << std::endl;

    InitBoatAndPlace(invalidBoat, CS170::Utils::Point{ 0, 7 }, Orientation::VERTICAL);  // invalid placement
    if (IsBoatPositionValid(*board, invalidBoat) == true) {
        AddBoatToBoard(*board, invalidBoat);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    DrawBoard(*board, true);
    std::cout << std::endl;

    InitBoatAndPlace(invalidBoat, CS170::Utils::Point{ 2, 2 }, Orientation::VERTICAL);  // invalid placement
    if (IsBoatPositionValid(*board, invalidBoat) == true) {
        AddBoatToBoard(*board, invalidBoat);
        std::cout << "Boat placement is accepted." << std::endl;
    }
    else {
        std::cout << "Boat placement is rejected." << std::endl;
    }
    DrawBoard(*board, true);
    std::cout << std::endl;
    DestroyBoard(board);
}

void test2() {
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    const int numBoats = 5;
    // Setup the board
    Board *board = CreateBoard(numBoats, 10, 10);

    // Create the ships
    Boat boats[numBoats];
    for (int i = 0; i < numBoats; i++) {
        InitRandomLocation(boats[i], i + 1, *board);
        AddBoatToBoard(*board, boats[i]);
    }

    std::cout << "The board with " << board->numBoats << " boats" << std::endl;
    DrawBoard(*board, true);
    std::cout << std::endl;

    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ -1, 0 });  // Illegal coordinate
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 10, 0 });  // Illegal coordinate
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 0, -1 });  // Illegal coordinate
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 0, 10 });  // Illegal coordinate	
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 2, 1 });  // HIT
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 3, 1 });  // HIT
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 2, 1 });  // DUPLICATE
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 4, 1 });  // HIT
    ShootPrintResultDrawPrintStats(*board, CS170::Utils::Point{ 5, 1 });  // SUNK

    DestroyBoard(board);
}

void test3() {
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    const int numBoats = 5;
    // Setup the board
    Board *board = CreateBoard(numBoats, 10, 10);

    // Create the ships
    Boat boats[numBoats];
    for (int i = 0; i < numBoats; i++) {
        InitRandomLocation(boats[i], i + 1, *board);
        AddBoatToBoard(*board, boats[i]);
    }

    // Try to sink the boats with random shots
    int shots = 0;
    int num_boats = 5;
    while (num_boats > 0) {
        ShotResult sr;
        do {
            CS170::Utils::Point shot;
            shot.x = CS170::Utils::Random(0, board->width - 1);
            shot.y = CS170::Utils::Random(0, board->height - 1);
            std::cout << "Shot #"
                << ++shots
                << " at coordinate "
                << shot.x
                << ", "
                << shot.y
                << "  ";

            sr = TakeShot(*board, shot);
            PrintShotResult(sr);
        } while (sr == ShotResult::DUPLICATE);

        // Sunk a boat
        if (sr == ShotResult::SUNK) {
            num_boats--;
        }

        DrawBoard(*board, true);
        std::cout << std::endl;
    }
    PrintStats(*board);

    DestroyBoard(board);
}

void test4() {
    int num_boats = 8;
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);

    const int numBoats = 8;
    // Setup the board
    Board *board = CreateBoard(numBoats, 10, 10);

    // Create the ships
    Boat boats[numBoats];
    for (int i = 0; i < numBoats; i++) {
        InitRandomLocation(boats[i], i + 1, *board);
        AddBoatToBoard(*board, boats[i]);
    }

    DrawBoard(*board, true);
    std::cout << std::endl << std::endl;

    // Try to sink the boats with random shots
    while (num_boats > 0) {
        ShotResult sr;
        do {
            CS170::Utils::Point shot;
            shot.x = CS170::Utils::Random(0, board->width - 1);
            shot.y = CS170::Utils::Random(0, board->height - 1);
            sr = TakeShot(*board, shot);
        } while (sr == ShotResult::DUPLICATE);

        // Sunk a boat
        if (sr == ShotResult::SUNK) {
            num_boats--;
        }
    }
    DrawBoard(*board);
    PrintStats(*board);

    DestroyBoard(board);
}

void test5() {
    int numBoats = 100;
    // Initialize the pseudo-random number generator
    CS170::Utils::srand(BASE_RANDOM, BASE_RANDOM2);
    // Setup the board
    Board *board = CreateBoard(numBoats, 30, 30);

    // Create the ships
    for (int i = 0; i < numBoats; i++) {
        Boat *boat = new Boat;
        InitRandomLocation(*boat, i + 1, *board);
        AddBoatToBoard(*board, *boat);
    }

    DrawBoard(*board, true);
    std::cout << std::endl << std::endl;

    // Try to sink the boats with random shots
    while (numBoats > 0) {
        ShotResult sr;
        do {
            CS170::Utils::Point shot;
            shot.x = CS170::Utils::Random(0, board->width - 1);
            shot.y = CS170::Utils::Random(0, board->height - 1);
            sr = TakeShot(*board, shot);
        } while (sr == ShotResult::DUPLICATE);

        // Sunk a boat
        if (sr == ShotResult::SUNK) {
            numBoats--;
        }
    }
    DrawBoard(*board);
    std::cout << std::endl;
    PrintStats(*board);

    DestroyBoats(*board);
    DestroyBoard(board);
}

int main(int argc, char **argv) {
    int test_num = 100;

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

    default:
        test0();
        test1();
        test2();
        test3();
        test4();
        test5();
        break;
    }


    return 0;
}