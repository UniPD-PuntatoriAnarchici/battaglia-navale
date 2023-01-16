//
// Created by Filippo Tiberio on 24/12/2022.
//
#include "./../../include/ship/ship.h"

Ship::~Ship() {}

bool Ship::is_alive() const { return armor_ != 0; }

void Ship::reset_cells() {
    for (auto &&cell : cells_) {
        cell = true;
    }
}

void Ship::hit(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    std::vector<Coordinate> ship_positions = raw_positions();

    auto found = std::find(ship_positions.begin(), ship_positions.end(), c);

    if (found == ship_positions.end()) throw Coordinate::INVALID_COORDINATE{};

    if (cells_[found - ship_positions.begin()]) armor_--;

    cells_[found - ship_positions.begin()] = false;
}

void Ship::heal(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    std::vector<Coordinate> ship_positions = raw_positions();

    auto found = std::find(ship_positions.begin(), ship_positions.end(), c);

    if (found == ship_positions.end()) throw Coordinate::INVALID_COORDINATE{};

    if (!cells_[found - ship_positions.begin()]) armor_++;

    cells_[found - ship_positions.begin()] = true;
}

std::vector<std::pair<Coordinate, char>> Ship::positions() const {
    std::vector<std::pair<Coordinate, char>> positions;

    std::vector<bool> localCells = cells();
    int length = static_cast<int>(localCells.size());  // unsigned int to int.

    std::pair<int, int> center = Coordinate::coordinates_to_indexes(center_);

    for (int i = 0; i < length; i++) {
        char c;
        switch (type_) {
            case Ship::Type::BATTLESHIP:
                c = localCells[i] ? 'C' : 'c';
                break;

            case Ship::Type::SUBMARINE:
                c = localCells[i] ? 'E' : 'e';
                break;

            case Ship::Type::REPAIRSHIP:
                c = localCells[i] ? 'S' : 's';
                break;
        }

        if (direction_ == Directions::HORIZONTAL) {
            positions.emplace_back(Coordinate{center.first, center.second - (length / 2) + i}, c);
        } else {
            positions.emplace_back(Coordinate{center.first - (length / 2) + i, center.second}, c);
        }
    }

    return positions;
}

std::vector<Coordinate> Ship::raw_positions() const {
    std::vector<Coordinate> positions;

    int length = static_cast<int>(cells().size());  // unsigned int to int.

    std::pair<int, int> center = Coordinate::coordinates_to_indexes(center_);

    for (int i = 0; i < length; i++) {
        if (direction_ == Directions::HORIZONTAL) {
            positions.emplace_back(center.first, center.second - (length / 2) + i);
        } else {
            positions.emplace_back(center.first - (length / 2) + i, center.second);
        }
    }

    return positions;
}
