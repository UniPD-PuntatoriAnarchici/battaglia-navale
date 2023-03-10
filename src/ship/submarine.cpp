/**
 * @author Matteo Galiazzo
 */
#include "./../../include/ship/submarine.h"

#include "./../../include/board/attackboard.h"
#include "./../../include/board/defenseboard.h"

/**
 * @Override virtual destrucctor
 * @details
 * We use an array of smart pointer in defenseboard.
 * In order to prevent problems with implicit destructors and implicit calls to the destructors we chose to completely
 * define destructors and define the ship's one as pure virtual. In this way we ensure the correct execution of the
 * destroying chain.
 */
Submarine::~Submarine() {}

/**
 * Explicit default constructor
 * @param center [Coordinate] default value is invalid
 * @param direction not useful in submarine but required since it extends ship
 */
Submarine::Submarine(Coordinate center, Ship::Directions direction) {
    cells_ = std::vector<bool>(LENGTH);
    center_ = center;
    direction_ = direction;
    armor_ = LENGTH;
    type_ = Type::SUBMARINE;
    reset_cells();
}

/**
 * Action of the submarine
 * @details moves the submarine and scans the surrounding cells in a 5x5
 * @param dest Coordinate where the submarine will move and scan
 * @param self_defense Defenseboard the board where the submarine is in
 * @param self_attack Attackboard where the submarine will show the scanning results
 * @param opponent Defenseboard where the submarine will perform the scan
 * @return [bool] true if the action finished succesfully
 */
bool Submarine::action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) {
    if (!this->is_alive()) return false;
    if (!dest.is_valid()) return false;

    if (self_defense.is_occupied(dest)) return false;

    // this is because if i can't go up/left a row/col i "lose" and don't have to check the row/col
    // in this way i consider this possibility and adress it
    int cells_left_to_ignore = 0;
    int cells_up_to_ignore = 0;

    // set start row
    int check_start_row = dest.row();
    for (int i = 0; i < 2; i++)
        if (check_start_row - 1 > 0)
            check_start_row--;
        else
            cells_up_to_ignore++;

    // set start col
    int check_start_col = dest.col();
    for (int i = 0; i < 2; i++)
        if (check_start_col - 1 > 0)
            check_start_col--;
        else
            cells_left_to_ignore++;

    // set end row
    int check_end_row = (check_start_row + 4 - cells_up_to_ignore < 12) ? check_start_row + 4 - cells_up_to_ignore : 12;
    // set end col
    int check_end_col = (check_start_col + 4 - cells_left_to_ignore < 12) ? check_start_col + 4 - cells_left_to_ignore : 12;

    // nested for loop on bounds with reveal
    for (int row = check_start_row; row <= check_end_row; row++) {
        for (int col = check_start_col; col <= check_end_col; col++) {
            Coordinate to_check(row, col);
            self_attack.clear(to_check);
            if (opponent.is_occupied(to_check)) self_attack.reveal(to_check, opponent.is_alive(to_check));
        }
    }

    // move submarine to destination
    this->set_center(dest);

    return true;
}

/**
 * Print of the submarine
 * @details detailed submarine print
 * @param os output stream
 * @param submarine to print
 * @return [std::ostream] reference of the output stream
 */
std::ostream &operator<<(std::ostream &os, const Submarine &battleship) {
    std::vector<bool> cells = battleship.cells();

    os << "Submarine with center in " << battleship.center() << "and direction: " << battleship.direction() << ", has "
       << battleship.armor() << "/" << Submarine::LENGTH << " armor: [";

    for (bool cell : cells) {
        os << (cell ? Submarine::CHARACTER : (char)(Submarine::CHARACTER + 32));
    }

    os << "]";

    return os;
}
