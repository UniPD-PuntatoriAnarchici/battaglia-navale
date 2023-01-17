/**
 * @author Tiberio Filippo
 */
#include "./../../include/board/attackboard.h"

//region constructors

/**
 * Default constructor
 * @details default, no need to initialize with a value, neither in replay is required.
 */
Attackboard::Attackboard() = default;

//endregion constructors

//region position getters

/**
 * Get all position of the board
 * @details linearize the sorted map in an arry
 * @implements @pure virtual Board::get_all()
 * @return [std::vector<std::pair<Coordinate, char>>] containing <key,value>s of the sorted map.
 */
std::vector<std::pair<Coordinate, char>> Attackboard::get_all() const {
    std::vector<std::pair<Coordinate, char>> vector{};

    for (auto el: cells_) {
        vector.emplace_back(el.first, el.second);
    }
    return vector;
}

/**
 * Get all position of the board without the char
 * @details return all map keys
 * @implements @pure virtual Board::get_all_row()
 * @return [std::vector<Coordinate>] containing keys of the sorted map.
 */
std::vector<Coordinate> Attackboard::get_all_raw() const {
    std::vector<Coordinate> vector{};

    for (auto el: cells_) {
        vector.push_back(el.first);
    }
    return vector;
}

//endregion position getters

/** return the size of the map
 * useful for @test
 * @return number of elemets
 */
int Attackboard::num_elements() const { return static_cast<int>(cells_.size()); }

//region setter

/**
 *
 * @param c
 */
void Attackboard::hit(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    cells_[c] = 'X';
}

/**
 * Set a cell as missed
 * @param c Coordinate to be set as missed
 * @details if not blank update
 */
void Attackboard::miss(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    cells_[c] = 'O';
}

/**
 * Set a cell as revealed
 * @param c Coordinate to be set as revealed
 * @details if not blank update
 * - if ship alive: set Y, otherwise set X as hit.
 * - not calling Hit in order to avoid overhead due to recalling another function with an argument passed by value
 */
void Attackboard::reveal(Coordinate c, bool is_alive) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};
    cells_[c] = (is_alive) ? 'Y' : 'X';
}

/**
 * Clear a single cell of the board
 * @param c Coordinate to be cleared
 */
void Attackboard::clear(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};
    cells_.erase(c);
}

//endregion setter

//region clearer

/**
 * Clear all hits of from the board
 * @details uses iterator to iterate all the map and delete specific object
 * @alternative_solution: call find and clear until find not iterator::end(), [worst]
 */
void Attackboard::clear_hits() {
    for (auto el = cells_.begin(); el != cells_.end();) {
        if (el->second == 'X') {
            el = cells_.erase(el); //erease current and go to next
        } else {
            el++;
        }
    }
}

/**
 * Clear all misses of from the board
 * @details uses iterator to iterate all the map and delete specific object
 * @alternative_solution: call find and clear until find not iterator::end(), [worst]
 */
void Attackboard::clear_misses() {
    for (auto el = cells_.begin(); el != cells_.end();) {
        if (el->second == 'O') {
            el = cells_.erase(el); //erease current and go to next
        } else {
            el++;
        }
    }
}

/**
 * Clear all reveals of from the board
 * @details uses iterator to iterate all the map and delete specific object
 * @alternative_solution: call find and clear until find not iterator::end(), [worst]
 */
void Attackboard::clear_reveals() {
    for (auto el = cells_.begin(); el != cells_.end();) {
        if (el->second == 'Y') {
            el = cells_.erase(el); //erease current and go to next
        } else {
            el++;
        }
    }
}
//endregion clearer
