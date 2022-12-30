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

    // Submarine submarine1;
    // Submarine submarine2;
}

std::vector<Battleship> Attackboard::place_battleships() {
    std::vector<Battleship> battleships;
    std::string input;

    for (int i = 0; i < 3; i++) {
        bool valid_input = false;
        while (!valid_input) {
            std::cout << "Quali sono le coordinate per la corazzata " << i + 1
                      << "?" << std::endl;
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
                // if vertical center is y2-y1
                int y2 = coordinates.at(1).row();
                int y1 = coordinates.at(0).row();
                // if y1 is bigger i switch the positions
                if (y1 > y2) {
                    int temp = y2;
                    y2 = y1;
                    y1 = temp;
                }
                // check that delta is valid
                if (y2 - y1 != Battleship::LENGTH - 1) {
                    std::cout << "La lunghezza di una corazzata e': "
                              << Battleship::LENGTH << "!" << std::endl;
                    continue;
                }
                center = Coordinate(coordinates.at(0).col(), y2 - y1);
            } else {
                // same row -> horizontal
                direction = Ship::Directions::HORIZONTAL;
                // if horizontal center is x2-x1
                int x2 = coordinates.at(1).col();
                int x1 = coordinates.at(0).col();
                // if x1 is bigger i switch the positions
                if (x1 > x2) {
                    int temp = x2;
                    x2 = x1;
                    x1 = temp;
                }
                // check that delta is valid
                if (x2 - x1 != Battleship::LENGTH - 1) {
                    std::cout << "La lunghezza di una corazzata e': "
                              << Battleship::LENGTH << "!" << std::endl;
                    continue;
                }
                center = Coordinate(x2 - x1, coordinates.at(0).row());
            }

            // push Battleship(center, direction)
            battleships.push_back(Battleship(center, direction));
            std::cout << "Corazzata inserita correttamente" << std::endl;
            valid_input = true;
        }
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