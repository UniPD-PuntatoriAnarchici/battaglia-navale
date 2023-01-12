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
    // scan destination, but i have to TODO: scan surrounding 5x5
    // go up by 2, left by 2
    // start 5x5 nested for loop with reveal
    Coordinate to_check = dest;

    to_check.set_col(to_check.col() - 1);
    to_check.set_col(to_check.col() - 1);

    to_check.set_row(to_check.row() - 1);
    to_check.set_row(to_check.row() - 1);

    if (!opponent.is_occupied(dest)) {
        return true;
    }
    self.reveal(dest);
    return true;
}