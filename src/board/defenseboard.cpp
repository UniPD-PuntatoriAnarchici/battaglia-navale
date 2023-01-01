#include "./../../include/board/defenseboard.h"

bool Defenseboard::place_ship(const Ship &ship) {
    if (ships.size() >= 8) throw FULL_BOARD_EXCEPTION{};
    ships.push_back(std::unique_ptr<Ship>(ship.clone()));
    return true;
}

bool Defenseboard::is_lost() { return false; }
