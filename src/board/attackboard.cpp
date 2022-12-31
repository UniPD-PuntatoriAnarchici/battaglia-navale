#include "./../../include/board/attackboard.h"

#include <sstream>

Attackboard::Attackboard() {
    std::cout << "INSERIMENTO NAVI NELLA GRIGLIA" << std::endl;
    // 3 battleship 3 support 3 submarine
    std::vector<Battleship> battleships = place_battleships();
    std::cout << "BATTLESHIPS" << std::endl;
    for (auto battleship : battleships) {
        std::cout << battleship << std::endl;
    }
    std::vector<Submarine> submarines = place_submarines();
    // Submarine submarine1;
    // Submarine submarine2;
}

std::vector<Battleship> Attackboard::place_battleships() {
    std::vector<Battleship> battleships;
    std::string input;

    for (int i = 0; i < 3; i++) {
        bool valid_input = false;
        while (!valid_input) {
            std::cout << "Quali sono le coordinate per la corazzata " << i + 1 << "?" << std::endl;
            // get and split coordinates
            std::getline(std::cin, input);
            std::vector<Coordinate> coordinates = split(input);

            // if i don't have 2 coordinates i break out to get new coordinates
            if (coordinates.size() != 2) {
                std::cout << "Devi inserire due coordinate!" << std::endl;
                continue;
            }

            // set center and direction
            Coordinate center;
            Ship::Directions direction;
            if (coordinates.at(0).col() == coordinates.at(1).col()) {
                // same column -> vertical
                direction = Ship::Directions::VERTICAL;
                // if vertical center is on the same column (y2-y1)
                // check that delta is valid
                int delta = ship_length(coordinates.at(1).row(), coordinates.at(0).row());
                if (delta != Battleship::LENGTH - 1) {
                    std::cout << "La lunghezza di una corazzata e': " << Battleship::LENGTH << "!" << std::endl;
                    continue;
                }
                center = Coordinate(coordinates.at(0).col(), delta);
            } else {
                // same row -> horizontal
                direction = Ship::Directions::HORIZONTAL;
                // // if horizontal center is on the same row (x2-x1)
                // check that delta is valid
                int delta = ship_length(coordinates.at(1).col(), coordinates.at(0).col());
                if (delta != Battleship::LENGTH - 1) {
                    std::cout << "La lunghezza di una corazzata e': " << Battleship::LENGTH << "!" << std::endl;
                    continue;
                }
                center = Coordinate(delta, coordinates.at(0).row());
            }

            // push Battleship(center, direction)
            battleships.push_back(Battleship(center, direction));
            std::cout << "Corazzata inserita correttamente" << std::endl;
            valid_input = true;
        }
    }

    return battleships;
}

std::vector<Submarine> Attackboard::place_submarines() {
    std::vector<Submarine> submarines;
    return submarines;
}

int Attackboard::ship_length(int n1, int n2) {
    if (n1 > n2) {
        int temp = n2;
        n2 = n1;
        n1 = temp;
    }
    return n2 - n1;
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

std::vector<Coordinate> Attackboard::get_all() { return std::vector<Coordinate>(1); }