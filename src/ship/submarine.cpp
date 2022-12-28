#include "./../../include/ship/submarine.h"

std::ostream &operator<<(std::ostream &os, const Submarine &battleship) {
    std::vector<bool> cells = battleship.cells();

    os << "Submarine with center in " << battleship.center()
       << "and direction: " << battleship.direction() << ", has "
       << battleship.armor() << "/" << Submarine::LENGTH << " armor: [";

    for (bool cell : cells) {
        os << (cell ? Submarine::CHARACTER : (char)(Submarine::CHARACTER + 32));
    }

    os << "]";

    return os;
}