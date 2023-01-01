#include "./../../include/board/defenseboard.h"

bool Defenseboard::place_ship(const Ship &ship) {
    if (ships_.size() >= 8) throw FULL_BOARD_EXCEPTION{};
    ships_.push_back(std::unique_ptr<Ship>(ship.clone()));
    return true;
}

std::vector<Coordinate> Defenseboard::get_all() {
    // ships_.at(0)->positions();
    std::vector<Coordinate> occupied_positions;

    return occupied_positions;
}

bool Defenseboard::is_lost() { return false; }
