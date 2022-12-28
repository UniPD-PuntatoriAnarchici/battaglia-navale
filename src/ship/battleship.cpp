//
// Created by filip on 25/12/2022.
//
#include "./../../include/ship/battleship.h"

std::ostream &operator<<(std::ostream &os, const Battleship &battleship) {
    std::vector<bool> cells = battleship.get_cells();

    os << "Battleship with center in " << battleship.center() << "and direction: " << battleship.direction()
       << ", has " << battleship.get_life() << "/"
       << Battleship::length() << " armor: [";

    for (bool cell: cells) {
        os << (cell ? Battleship::character() : (char) (Battleship::character() + 32));
    }

    os << "]";

    return os;
}
