/**
 * @author Tiberio Filippo
 */

#include "./../../include/ship/battleship.h"
#include "./../../include/board/attackboard.h"
#include "./../../include/board/defenseboard.h"

std::ostream &operator<<(std::ostream &os, const Battleship &battleship) {
    std::vector<bool> cells = battleship.cells();

    os << "Battleship with center in " << battleship.center() << "and direction: " << battleship.direction() << ", has "
       << battleship.armor() << "/" << Battleship::LENGTH << " armor: [";

    for (bool cell: cells) {
        os << (cell ? Battleship::CHARACTER : (char) (Battleship::CHARACTER + 32));
    }

    os << "]";

    return os;
}

bool Battleship::action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) {
    if (!this->is_alive()) return false;
    if (!dest.is_valid()) return false;

    if (!opponent.is_occupied(dest)) {
        self_attack.miss(dest);
        return true;
    }

    opponent.hit(dest);
    self_attack.hit(dest);

    return true;
}

Battleship::~Battleship() {}

Battleship::Battleship(Coordinate center, Ship::Directions direction) {
    cells_ = std::vector<bool>(LENGTH);
    center_ = center;
    direction_ = direction;
    armor_ = LENGTH;
    type_ = Type::BATTLESHIP;
    reset_cells();
}
