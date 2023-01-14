#include "./../../include/ship/repairship.h"

std::ostream &operator<<(std::ostream &os, const Repairship &battleship) {
  std::vector<bool> cells = battleship.cells();

    os << "Repairship with center in " << battleship.center() 
       << "and direction: " << battleship.direction()
       << ", has " << battleship.armor() << "/"
       << Repairship::LENGTH << " armor: [";

    for (bool cell: cells) {
        os << (cell ? Repairship::CHARACTER : (char) (Repairship::CHARACTER + 32));
    }

    os << "]";

    return os;

}

Repairship::~Repairship() {

}
