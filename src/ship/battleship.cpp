//
// Created by filip on 25/12/2022.
//
#include "./../../include/ship/battleship.h"
/**
 * ?????????????
 */
#include "./../../include/board/defenseboard.h"
#include "./../../include/board/attackboard.h"

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

bool Battleship::action(Coordinate dest, Defenseboard &opponent, Attackboard &self) {

    if (!dest.is_valid())
        throw Coordinate::INVALID_COORDINATE{};

    if (!opponent.is_occupied(dest)) {
        self.miss(dest);
        return false; //MISS TODO: CHANGE TO TRUE
    }

    opponent.hit(dest);
    self.hit(dest);

    return true;
}

Battleship::~Battleship() {

}
