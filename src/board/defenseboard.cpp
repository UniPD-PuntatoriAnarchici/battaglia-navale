/**
 * @author Galiazzo Matteo
 */

#include "./../../include/board/defenseboard.h"

/**
 * Get all positions occupied by the ships on the board and the type of ship in that position
 * @details returns every smart pointer on the vector and calls the ship's positions
 * @implements @pure virtual Board::get_all()
 * @return [std::vector<std::pair<Coordinate, char>>] containing <key, value>s of the vector of smart pointers
 */
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

/**
 * Get all positions occupied by the ships on the board
 * @details returns every smart pointer on the vector and calls the ship's raw positions
 * @return [std::vector<Coordinate>] containing all positions occupied by the ships
 */
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

/**
 * Get all positions occupied by the ships except the one which has the center in the coordinate passed to the function
 * member
 * @param excluded_ship_center center Coordinate of the ship to be exclued
 * @details return all occupied positions except the one which has the center in the coordinate passed to the function
 * member
 * @return [std::vector<Coordinate>] containing all positions occupied by the ships except the one with the center passed
 * to the function member
 */
std::vector<Coordinate> Defenseboard::get_all_but_one_raw(Coordinate excluded_ship_center) const {
    std::vector<Coordinate> occupied_positions;

    for (auto &ship : ships_) {
        auto tmp = ship->raw_positions();
        if (ship->is_alive() && ship->center() != excluded_ship_center) {
            occupied_positions.insert(occupied_positions.end(), tmp.begin(), tmp.end());
        }
    }

    std::sort(occupied_positions.begin(), occupied_positions.end(), [](Coordinate a, Coordinate b) { return (a < b); });

    return occupied_positions;
}

/**
 * Checks if a game is lost
 * @details checks that the armor of each ship is > 0
 * @return [bool] true if all ships are at 0 armor, false if there are some ships with alive armor
 */
bool Defenseboard::is_lost() const {
    for (auto &ship : ships_) {
        int current_armor = ship->armor();
        if (current_armor > 0) return false;
    }
    return true;
}

/**
 * Places a ship in the board
 * @details adds a Ship to the vector of smart pointers if there is still space
 * @return [bool] true if placement ended succesfully, false if it didn't
 */
bool Defenseboard::place_ship(const Ship &ship) {
    if (ships_.size() >= 8) throw FULL_BOARD_EXCEPTION{};
    ships_.push_back(std::unique_ptr<Ship>(ship.clone()));
    return true;
}

/**
 * Checks if a Coordinate is occupied
 * @param c Coordinate to check
 * @return true if position is occupied, false if it's not
 */
bool Defenseboard::is_occupied(Coordinate &c) const {
    std::vector<Coordinate> opponent_postions = get_all_raw();
    auto found = std::find(opponent_postions.begin(), opponent_postions.end(), c);
    return found != opponent_postions.end();
}

/**
 * Checks if a Ship is alive
 * @param c Coordinate of the ship to check
 * @return true if it's alive, false if it's not
 */
bool Defenseboard::is_alive(Coordinate &c) const {
    for (auto &ship : ships_) {
        std::vector<std::pair<Coordinate, char>> tmp = ship->positions();
        for (auto &pair : tmp) {
            if (pair.first == c && (pair.second == 'c' || pair.second == 'e' || pair.second == 's')) return false;
        }
    }
    return true;
}

/**
 * Hits a Ship
 * @param c Coordinate of the ship to hit
 * @return [bool] true if i hitted, false if i didn't
 */
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

/**
 * Heals a Ship
 * @param c Coordinate of the ship to heal
 * @return [bool] true if i healed, false if i didn't
 */
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

/**
 * Returns the unique pointer to the ship passed to the function member
 * @details finds the ship based on the Coordinate passed to the function member
 * @param c center Coordinate of the ship to find and return
 * @return [std::unique_ptr<Ship>] of the ship if it has been found, [NO_SHIP] (nullptr) if the ship hasn't been found
 */
const std::unique_ptr<Ship> &Defenseboard::ship_at(Coordinate c) const {
    for (auto &ship : ships_) {
        if (ship->center() == c && ship->is_alive()) {
            return ship;
        }
    }
    return NO_SHIP;
}

/**
 * Returns the ship at a certain index
 * @details returns the ship at a certain index of the vector (useful for the cpu player)
 * @param i int index of the ship at the index to return
 * @return [std::unique_ptr<Ship>] of the ship if it has been found, nullptr if it has not
 */
const std::unique_ptr<Ship> &Defenseboard::ship_at_index(int i) const {
    if (i > 7) throw std::invalid_argument("There are only 8 ships!");
    if (!ships_.at(i)->is_alive()) return NO_SHIP;
    return ships_.at(i);
}

/**
 * returns the ships in the log format
 * @details the log format is direction + center [horizontal/vertical] + [Coordinate center]
 * @return std::string with all the ships in the log format
 */
std::string Defenseboard::to_log_format() const {
    std::string buffer;
    for (auto &ship : ships_) {
        buffer += (ship->direction() == Ship::Directions::HORIZONTAL) ? "H" : "V";
        buffer += ship->center().to_string() + " ";
    }
    return buffer;
}

bool Defenseboard::remove_ship(Ship &ship){
    int c=0;
    for (auto i = ships_.begin(); i != ships_.end(); i++){
        if (ships_.at(c)->center()==ship.center()){
            ships_.erase(i);
            return true;
        }
        c++;
    }
    return false;
    
}
