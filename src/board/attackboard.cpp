#include "./../../include/board/attackboard.h"

#include <sstream>

Attackboard::Attackboard() {
    std::cout << "INSERIMENTO NAVI NELLA GRIGLIA" << std::endl;
    // 3 battleship 3 support 3 submarine
    std::vector<Battleship> battleships = place_battleships();
    Submarine submarine1;
    Submarine submarine2;
}

std::vector<Battleship> Attackboard::place_battleships() {
    std::string input;
    std::cout << "Quali sono le coordinate per la corazzata 1?" << std::endl;
    std::getline(std::cin, input);
    std::vector<Coordinate> coordinates = split(input);
    
    // INPUT SIZE
    std::cout << "SIZE: " << coordinates.size() << std::endl;

    // for (int i = 0; i < coordinates.size() - 1; i++) {
    //     std::cout << coordinates.at(i) << std::endl;
    // }

    // Battleship battleship1;
    // Battleship battleship2;
    // Battleship battleship3;
}

std::vector<Coordinate> Attackboard::split(const std::string &s) {
    std::vector<Coordinate> coordinates;
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, ' ')) {
        coordinates.push_back(Coordinate(item));
    }
    // std::cout << coordinates.at(0) << std::endl;
    return coordinates;
}

std::vector<Coordinate> Attackboard::get_all() {
    return std::vector<Coordinate>(1);
}