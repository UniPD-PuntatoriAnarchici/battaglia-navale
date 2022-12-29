#include "./../../include/board/attackboard.h"

#include <sstream>

Attackboard::Attackboard() {
    std::cout << "INSERIMENTO NAVI NELLA GRIGLIA" << std::endl;
    // 3 battleship 3 support 3 submarine
    std::vector<Battleship> battleships = place_battleships();
    // Submarine submarine1;
    // Submarine submarine2;
}

std::vector<Battleship> Attackboard::place_battleships() {
    std::vector<Battleship> battleships;
    std::string input;

    for (int i = 0; i < 3; i++) {
        std::cout << "Quali sono le coordinate per la corazzata " << i + 1
                  << "?" << std::endl;
        bool valid_input = false;
        while (!valid_input) {
            // get coordinates
            std::getline(std::cin, input);
            // split coordinates
            std::vector<Coordinate> coordinates = split(input);
            // check validity

            // set center and direction

            // create battleship (center, direction)

            // push battleship

            // 2 coordinates, space in between is 5, same row or same column
            if (coordinates.size() == 2)
                valid_input = true;
            else
                std::cout << "bad input" << std::endl;
        }
        std::cout << "Corazzata inserita correttamente" << std::endl;
    }

    return battleships;
}

std::vector<Coordinate> Attackboard::split(const std::string &s) {
    std::vector<Coordinate> coordinates;
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, ' ')) {
        coordinates.emplace_back(item);
    }
    return coordinates;
}

std::vector<Coordinate> Attackboard::get_all() {
    return std::vector<Coordinate>(1);
}