/**
 * @author Matteo Galiazzo
 */
#include "./../../include/ship/submarine.h"

#include "./../../include/board/attackboard.h"
#include "./../../include/board/defenseboard.h"

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
    this->center_ = dest;

    return true;
}

Submarine::~Submarine() {}

Submarine::Submarine(Coordinate center, Ship::Directions direction) {
    cells_ = std::vector<bool>(LENGTH);
    center_ = center;
    direction_ = direction;
    armor_ = LENGTH;
    type_ = Type::SUBMARINE;
    reset_cells();
}
