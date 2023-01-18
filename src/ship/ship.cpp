/**
 * @author Tiberio Filippo
 */

#include "./../../include/ship/ship.h"

/**
 * Pure virtual destructor
 * @details
 * We use an array of smart pointer in defenseboard.
 * In order to prevent problems with implicit destructors and implicit calls to these, we opted to completely define destructors
 * and define the ship's one as pure virtual. In this way we ensure the correct execution of the destroying chain.
 */
Ship::~Ship() {}


/**
 * Check if ship is alive.
 * @details Check if ship is alive by checking the armor value. Doesn't iterate over cells
 * @return bool
 */
bool Ship::is_alive() const { return armor_ != 0; }

/**
 * Reset all ship's cells. (Do not restore armor!)
 */
void Ship::reset_cells() {
    for (auto &&cell: cells_) {
        cell = true;
    }
}

/**
 * Set ship as hit in a specific position
 * @throws Coordinate::INVALID_COORDINATE if coordinate doesn't belong to current ship
 * @param c [Coordinate]
 */
void Ship::hit(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    std::vector<Coordinate> ship_positions = raw_positions(); //Ship raw pos

    //Looking for a match in positions using iterators and stl std:find
    auto found = std::find(ship_positions.begin(), ship_positions.end(), c);

    if (found == ship_positions.end()) throw Coordinate::INVALID_COORDINATE{};

    if (cells_[found - ship_positions.begin()]) armor_--; //IF not previously hit, decrement armory

    cells_[found - ship_positions.begin()] = false; //and set cell
}

void Ship::heal() {
    armor_ = static_cast<int>(type_);
    reset_cells();
}

/**
 * Get all coordinate occupied by current ship: decorated with current status
 * @return [std::vector<std::pair<Coordinate, char>>]
 * @details decorate the position with the correct printing char, so the player will not need to interact with ships
 */
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

/**
 * Get all coordinate occupied by current ship
 * @return [std::vector<Coordinate>]
 */
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

/**
 * Ship's type getter
 */
Ship::Type Ship::type() const {
    return type_;
}
