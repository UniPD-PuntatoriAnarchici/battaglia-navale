#include "./../../include/board/attackboard.h"

Attackboard::Attackboard() {
    std::cout << "INSERIMENTO NAVI NELLA GRIGLIA" << std::endl;
    Battleship battleship1;
    Battleship battleship2;
    Battleship battleship3;
}

std::vector<Coordinate> Attackboard::get_all() {
    return std::vector<Coordinate>(1);
}