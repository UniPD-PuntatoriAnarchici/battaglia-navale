/**
 * @author Rampin Matteo
 */

#include "./../../include/ship/repairship.h"

#include "./../../include/board/defenseboard.h"

/**
 * Print of Repairship
 * @overload operator<<
 * @param   os                      : output stream
 * @param   repairship              : repairship to print
 * @return {std::ostream}           : reference of the output stream
 */
std::ostream &operator<<(std::ostream &os, const Repairship &repairship) {
    std::vector<bool> cells = repairship.cells();

    os << "Repairship with center in " << repairship.center() << "and direction: " << repairship.direction() << ", has "
       << repairship.armor() << "/" << Repairship::LENGTH << " armor: [";

    for (bool cell: cells) {
        os << (cell ? Repairship::CHARACTER : (char) (Repairship::CHARACTER + 32));
    }

    os << "]";

    return os;
}

/**
     * Action of the Repairship
     * @details moves the repairship and repairs ships in a 3x3
     * @param dest Coordinate where the submarine will move and repair
     * @param self_defense Defenseboard the board where the submarine is in and where it repairs the ships
     * @param self_attack Attackboard of the other player
     * @param opponent Defenseboard of the other player
     * @return [bool] true if the action finished succesfully
     */
bool Repairship::action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) {
    if (!this->is_alive()) return false;
    if (!dest.is_valid()) return false;
    if (self_defense.is_occupied(dest)) return false;

    //check if the positions next to the center are valid
    if (this->direction_ == Ship::Directions::HORIZONTAL) {
        if (dest.col() + 1 > 12 || dest.col() - 1 < 1) return false;
    } else {
        if (dest.row() + 1 > 12 || dest.row() - 1 < 1) return false;
    }


    std::vector<Coordinate> current_grid = self_defense.get_all_but_one_raw(this->center());
    Repairship tmp{dest, this->direction()};

    for (auto position: tmp.raw_positions()) {

        if (!self_defense.is_valid(position)) {
            return false;
        }
        //checks if the positions of the tmp ship are already exists
        if (std::find(current_grid.begin(), current_grid.end(), position) != current_grid.end()) {
            return false;
        }
    }
    //move repairship
    this->set_center(dest);

    //if ship is horizontal check the rows up and down,otherwise check the cols left and right
    if (direction() == Ship::Directions::HORIZONTAL) {
        //set start col
        int start_col = dest.col();
        if (start_col - 1 > 0) start_col--;
        //set end col
        int end_col = dest.col();
        if (end_col + 1 <= 12) end_col++;

        //heal the ships in a 3x3 excluding itself
        for (int i = start_col; i <= end_col; i++) {
            if (dest.row() - 1 > 0) {
                Coordinate to_check_1(dest.row() - 1, i);
                if (self_defense.is_occupied(to_check_1)) {
                    self_defense.heal(to_check_1);
                }
            }
            if (dest.row() + 1 <= 12) {
                Coordinate to_check_2(dest.row() + 1, i);
                if (self_defense.is_occupied(to_check_2) ) {
                    self_defense.heal(to_check_2);
                }
            }
        }
    } else {
        //set start row
        int start_row = dest.row();
        if (start_row - 1 > 0) start_row--;
        //set end row
        int end_row = dest.row();
        if (end_row + 1 <= 12) end_row++;

        //heal the ships in a 3x3 excluding itself
        for (int i = start_row; i <= end_row; i++) {
            if (dest.col() - 1 > 0) {
                Coordinate to_check_1(i, dest.col() - 1);
                if (self_defense.is_occupied(to_check_1)) {
                    self_defense.heal(to_check_1);
                }
            }
            if (dest.col() + 1 <= 12) {
                Coordinate to_check_2(i, dest.col()+1);
                if (self_defense.is_occupied(to_check_2)) {
                    self_defense.heal(to_check_2);
                }
            }
        }
    }
    return true;
}

/**
 * @Override virtual destructor
 * @details
 * We use an array of smart pointer in defenseboard.
 * In order to prevent problems with implicit destructors and implicit calls to the destructors we chose to completely
 * define destructors and define the ship's one as pure virtual. In this way we ensure the correct execution of the
 * destroying chain.
 */
Repairship::~Repairship() {}

/**
 * Explicit default constructor
 * @param center [Coordinate] default value is invalid.
 * @param direction [Directions] default value is Horizontal
 */
Repairship::Repairship(Coordinate center, Ship::Directions direction) {
    cells_ = std::vector<bool>(LENGTH);
    center_ = center;
    direction_ = direction;
    armor_ = LENGTH;
    type_ = Type::REPAIRSHIP;
    reset_cells();
}
