#include "./../../include/board/defenseboard.h"

#include <algorithm>

bool Defenseboard::place_ship(const Ship &ship) {
    if (ships_.size() >= 8) throw FULL_BOARD_EXCEPTION{};
    ships_.push_back(std::unique_ptr<Ship>(ship.clone()));
    return true;
}

std::vector<std::pair<Coordinate, char>> Defenseboard::get_all() {
    // ships_.at(0)->positions();
    std::vector<std::pair<Coordinate, char>> occupied_positions;
    //    Battleship b1{Coordinate{5,5},Ship::Directions::HORIZONTAL};
    //    Battleship b2{Coordinate{5,8},Ship::Directions::VERTICAL};
    //
    //    auto tmp = b1.positions();
    //    occupied_positions.insert(occupied_positions.end(), tmp.begin(), tmp.end());
    //    tmp = b2.positions();
    //    occupied_positions.insert(occupied_positions.end(), tmp.begin(), tmp.end());

    for (auto &ship: ships_) {
        auto tmp = ship->positions();
        occupied_positions.insert(occupied_positions.end(), tmp.begin(), tmp.end());
    }

    std::sort(occupied_positions.begin(), occupied_positions.end(),
              [](std::pair<Coordinate, char> a, std::pair<Coordinate, char> b) {
                  return (a.first < b.first);
              });

    return occupied_positions;
}

bool Defenseboard::is_lost() { return false; }

std::vector<Coordinate> Defenseboard::get_all_raw() {
    std::vector<Coordinate> occupied_positions;

    for (auto &ship: ships_) {
        auto tmp = ship->raw_positions();
        occupied_positions.insert(occupied_positions.end(), tmp.begin(), tmp.end());
    }

    std::sort(occupied_positions.begin(), occupied_positions.end(),
              [](Coordinate a, Coordinate b) {
                  return (a < b);
              });

    return occupied_positions;
}
