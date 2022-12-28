//
// Created by filip on 25/12/2022.
//
#include "./../../include/ship/battleship.h"

std::ostream &operator<<(std::ostream &os, const Battleship &battleship) {
    std::vector<bool> cells = battleship.cells();

    os << "Battleship with center in " << battleship.center() << "and direction: " << battleship.direction()
       << ", has " << battleship.armor() << "/"
       << Battleship::LENGTH << " armor: [";

    for (bool cell: cells) {
        os << (cell ? Battleship::CHARACTER : (char) (Battleship::CHARACTER + 32));
    }

    os << "]";

    return os;
}
