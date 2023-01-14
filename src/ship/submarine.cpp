#include "./../../include/ship/submarine.h"
// ???
#include "./../../include/board/attackboard.h"
#include "./../../include/board/defenseboard.h"

std::ostream &operator<<(std::ostream &os, const Submarine &battleship) {
    std::vector<bool> cells = battleship.cells();

    os << "Submarine with center in " << battleship.center() << "and direction: " << battleship.direction()
       << ", has " << battleship.armor() << "/" << Submarine::LENGTH << " armor: [";

    for (bool cell : cells) {
        os << (cell ? Submarine::CHARACTER : (char)(Submarine::CHARACTER + 32));
    }

    os << "]";

    return os;
}

bool Submarine::action(Coordinate dest, Defenseboard &opponent, Attackboard &self) {
    if (!dest.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    // set start row
    int check_start_row = dest.row();
    for (int i = 0; i < 2; i++)
        if (check_start_row - 1 > 0) check_start_row--;

    // set start col
    int check_start_col = dest.col();
    for (int i = 0; i < 2; i++)
        if (check_start_col - 1 > 0) check_start_col--;

    // set end row
    int check_end_row = (check_start_row + 4 < 12) ? check_start_row + 4 : 12;
    // set end col
    int check_end_col = (check_start_col + 4 < 12) ? check_start_col + 4 : 12;

    // nested for loop on bounds with reveal
    for (int row = check_start_row; row <= check_end_row; row++) {
        for (int col = check_start_col; col <= check_end_col; col++) {
            Coordinate to_check(row, col);
            self.clear(to_check);
            if (opponent.is_occupied(to_check)) self.reveal(to_check, opponent.is_alive(to_check));
        }
    }

    return true;
}

Submarine::~Submarine() {

}
