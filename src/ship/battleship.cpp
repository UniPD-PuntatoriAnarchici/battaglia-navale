/**
 * @author Tiberio Filippo
 */

#include "./../../include/ship/battleship.h"
#include "./../../include/board/attackboard.h"
#include "./../../include/board/defenseboard.h"

/**
 * @overload operator<<
 */
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

/**
 * action: shoots at a Coordinate of the opponent's defense grid
 * @return [bool] true if action is valid
 */
bool Battleship::action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) {
    if (!this->is_alive()) return false; //Check if action is valid
    if (!dest.is_valid()) return false;

    if (!opponent.is_occupied(dest)) { //if opponent board is not occupied in dest coordinat set miss
        self_attack.miss(dest);
        return true;
    }

    opponent.hit(dest); //else hit
    self_attack.hit(dest);

    return true;
}

/**
 * @Override virtual destructor
 * @details
 * We use an array of smart pointer in defenseboard.
 * In order to prevent problems with implicit destructors and implicit calls to these, we opted to completely define destructors
 * and define the ship's one as pure virtual. In this way we ensure the correct execution of the destroying chain.
 */
Battleship::~Battleship() {}

/**
 * Explicit default constructor
 * @param center [Coordinate] default value is invalid.
 * @param direction [Directions] default value is Horizontal
 */
Battleship::Battleship(Coordinate center, Ship::Directions direction) {
    cells_ = std::vector<bool>(LENGTH);
    center_ = center;
    direction_ = direction;
    armor_ = LENGTH;
    type_ = Type::BATTLESHIP;
    reset_cells();
}
