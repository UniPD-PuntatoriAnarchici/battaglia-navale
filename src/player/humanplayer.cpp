#include "./../../include/player/humanplayer.h"

void Humanplayer::turn() {}

bool Humanplayer::place_ships() {
    // passo una ship e viene buttata dentro
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
                if (!check_delta(coordinates.at(1).row(), coordinates.at(0).row())) {
                    std::cout << "La lunghezza di una corazzata e': " << Battleship::LENGTH << "!"
                              << std::endl;
                    continue;
                }
                center = Coordinate(coordinates.at(0).row() + (Battleship::LENGTH / 2),
                                    coordinates.at(0).col());
            } else {
                // same row -> horizontal
                direction = Ship::Directions::HORIZONTAL;
                // if horizontal center is on the same row (x2-x1)
                if (!check_delta(coordinates.at(1).col(), coordinates.at(0).col())) {
                    std::cout << "La lunghezza di una corazzata e': " << Battleship::LENGTH << "!"
                              << std::endl;
                    continue;
                }
                center = Coordinate(coordinates.at(0).row(),
                                    coordinates.at(0).col() + (Battleship::LENGTH / 2));
            }

            // push Battleship(center, direction)
            defense_board_.place_ship(Battleship(center, direction));
            std::cout << "Corazzata inserita correttamente" << std::endl;
            valid_input = true;
        }
    }
    return true;
}

std::vector<Submarine> Humanplayer::place_submarines() {
    std::vector<Submarine> submarines;
    return submarines;
}

// true -> delta ok, false -> delta wrong, insert again
bool Humanplayer::check_delta(int n1, int n2) {
    if (n1 > n2) {
        int temp = n2;
        n2 = n1;
        n1 = temp;
    }
    return (n2 - n1 + 1) == Battleship::LENGTH;
}

std::vector<Coordinate> Humanplayer::split(const std::string &s) {
    std::vector<Coordinate> coordinates;
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, ' ')) {
        coordinates.emplace_back(item);
    }
    return coordinates;
}
