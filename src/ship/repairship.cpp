#include "./../../include/ship/repairship.h"

std::ostream &operator<<(std::ostream &os, const Repairship &battleship) {
    std::vector<bool> cells = battleship.cells();

    os << "Repairship with center in " << battleship.center() << "and direction: " << battleship.direction() << ", has "
       << battleship.armor() << "/" << Repairship::LENGTH << " armor: [";

    for (bool cell : cells) {
        os << (cell ? Repairship::CHARACTER : (char)(Repairship::CHARACTER + 32));
    }

    os << "]";

    return os;
}

bool Repairship::action(Coordinate dest, Defenseboard &opponent, Attackboard &self) {
    if (!this->is_alive()) throw Ship::DEAD_SHIP{};
    if (!dest.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    return true;
}

Repairship::~Repairship() {}

Repairship::Repairship(Coordinate center, Ship::Directions direction) {
    cells_ = std::vector<bool>(LENGTH);
    center_ = center;
    direction_ = direction;
    armor_ = LENGTH;
    type_ = Type::REPAIRSHIP;
    reset_cells();
}
