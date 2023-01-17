/**
 * @author Galiazzo Matteo
 */

#include "./../../include/board/defenseboard.h"

#include <algorithm>

bool Defenseboard::place_ship(const Ship &ship) {
    if (ships_.size() >= 8) throw FULL_BOARD_EXCEPTION{};
    ships_.push_back(std::unique_ptr<Ship>(ship.clone()));
    return true;
}

std::vector<std::pair<Coordinate, char>> Defenseboard::get_all() const {
    std::vector<std::pair<Coordinate, char>> occupied_positions;

    for (auto &ship : ships_) {
        auto tmp = ship->positions();
        if (ship->is_alive()) occupied_positions.insert(occupied_positions.end(), tmp.begin(), tmp.end());
    }

    std::sort(occupied_positions.begin(), occupied_positions.end(),
              [](std::pair<Coordinate, char> a, std::pair<Coordinate, char> b) { return (a.first < b.first); });

    return occupied_positions;
}

bool Defenseboard::is_alive(Coordinate &c) const {
    for (auto &ship : ships_) {
        std::vector<std::pair<Coordinate, char>> tmp = ship->positions();
        for (auto &pair : tmp) {
            if (pair.first == c && (pair.second == 'c' || pair.second == 'e' || pair.second == 's')) return false;
        }
    }
    return true;
}

bool Defenseboard::is_lost() const {
    for (auto &ship : ships_) {
        int current_armor = ship->armor();
        if (current_armor > 0) return false;
    }
    return true;
}

std::vector<Coordinate> Defenseboard::get_all_raw() const {
    std::vector<Coordinate> occupied_positions;

    for (auto &ship : ships_) {
        auto tmp = ship->raw_positions();
        if (ship->is_alive()) {
            occupied_positions.insert(occupied_positions.end(), tmp.begin(), tmp.end());
        }
    }

    std::sort(occupied_positions.begin(), occupied_positions.end(), [](Coordinate a, Coordinate b) { return (a < b); });

    return occupied_positions;
}

std::string Defenseboard::to_log_format() const {
    std::string buffer;
    for (auto &ship : ships_) {
        buffer += (ship->direction() == Ship::Directions::HORIZONTAL) ? "H" : "V";
        buffer += ship->center().to_string() + " ";
    }
    return buffer;
}

bool Defenseboard::is_occupied(Coordinate &c) const {
    std::vector<Coordinate> opponent_postions = get_all_raw();
    auto found = std::find(opponent_postions.begin(), opponent_postions.end(), c);

    return found != opponent_postions.end();
}
bool Defenseboard::hit(Coordinate &c) {
    if (!is_occupied(c)) return false;

    for (auto &ship : ships_) {
        std::vector<Coordinate> positions = ship->raw_positions();
        std::vector<Coordinate>::iterator cell = std::find(positions.begin(), positions.end(), c);
        if (!(cell == positions.end())) {
            ship->hit(c);
            return true;
        }
    }
    return false;
}

bool Defenseboard::heal(Coordinate &c) {
    if (!is_occupied(c)) return false;

    for (auto &ship : ships_) {
        std::vector<Coordinate> positions = ship->raw_positions();
        auto cell = std::find(positions.begin(), positions.end(), c);
        if (!(cell == positions.end())) {
            ship->reset_cells();
            return true;
        }
    }
    return false;
}

const std::unique_ptr<Ship> &Defenseboard::ship_at(Coordinate c) const {
    for (auto &ship : ships_) {
        if (ship->center() == c && ship->is_alive()) {
            return ship;
        }
    }
    //    throw std::exception{};
    return NO_SHIP;
}

const std::unique_ptr<Ship> &Defenseboard::ship_at_index(int i) const {
    if (i > 7) throw std::invalid_argument("Only 8 ships!");
    if (!ships_.at(i)->is_alive()) return NO_SHIP;

    return ships_.at(i);
}

std::vector<Coordinate> Defenseboard::get_all_but_one_raw(Coordinate exluded_ship_center) const {
    std::vector<Coordinate> occupied_positions;

    for (auto &ship : ships_) {
        auto tmp = ship->raw_positions();
        if (ship->is_alive() && ship->center() != exluded_ship_center) {
            occupied_positions.insert(occupied_positions.end(), tmp.begin(), tmp.end());
        }
    }

    std::sort(occupied_positions.begin(), occupied_positions.end(), [](Coordinate a, Coordinate b) { return (a < b); });

    return occupied_positions;
}
