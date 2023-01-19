/**
 * @author Galiazzo Matteo
 */

#ifndef DEFENSEBOARD_H
#define DEFENSEBOARD_H

#include <algorithm>
#include <memory>
#include <queue>

#include "./../ship/battleship.h"
#include "./../ship/repairship.h"
#include "./../ship/submarine.h"
#include "board.h"

/**
 * Defenseboard Class
 * @details to mantain the defenseboard as simple as possible and to avoid searching a 2x2 matrix (O(n^2) complexity) we
 * decided to use a std::vector of std::unique_ptr to Ship (our base class). In this way we can store all kinds of ships
 * without worrying about slicing.
 * Since we used smart pointers we decided to delete the copy and move constructor
 *
 * @author Galiazzo Matteo
 * @extends Board
 */
class Defenseboard : public Board {
   public:
    /**
     * we called the std::unique_ptr<Ship> null pointer NO_SHIP
     */
    const std::unique_ptr<Ship> NO_SHIP = nullptr;

    /**
     * Full board exception
     * @details Since you can't have infinite Ships in a defenseboard we made a custom exception to throw if the board is
     * full
     */
    class FULL_BOARD_EXCEPTION : public std::exception {
        const char *what() const noexcept override { return "Board is full, you can't add more ships"; }
    };

    /**
     * Default constructor
     * @details default, no need to initialize with a value, neither in replay is required.
     */
    Defenseboard() = default;

    /**
     * Copy constructor
     * @details deleted since we used smart pointers
     */
    Defenseboard(const Defenseboard &) = delete;

    /**
     * Move constructor
     * @details deleted since we used smart pointers
     */
    Defenseboard &operator=(Defenseboard const &) = delete;

    /**
     * Get all positions occupied by the ships on the board and the type of ship in that position
     * @details returns every smart pointer on the vector and calls the ship's positions
     * @implements @pure virtual Board::get_all()
     * @return [std::vector<std::pair<Coordinate, char>>] containing <key, value>s of the vector of smart pointers
     */
    std::vector<std::pair<Coordinate, char>> get_all() const override;

    /**
     * Get all positions occupied by the ships on the board
     * @details returns every smart pointer on the vector and calls the ship's raw positions
     * @return [std::vector<Coordinate>] containing all positions occupied by the ships
     */
    std::vector<Coordinate> get_all_raw() const override;

    /**
     * Get all positions occupied by the ships except the one which has the center in the coordinate passed to the function
     * member
     * @param excluded_ship_center center Coordinate of the ship to be exclued
     * @details return all occupied positions except the one which has the center in the coordinate passed to the function
     * member
     * @return [std::vector<Coordinate>] containing all positions occupied by the ships except the one with the center passed
     * to the function member
     */
    std::vector<Coordinate> get_all_but_one_raw(Coordinate excluded_ship_center) const;

    /**
     * Checks if a game is lost
     * @details checks that the armor of each ship is > 0
     * @return [bool] true if all ships are at 0 armor, false if there are some ships with alive armor
     */
    bool is_lost() const;

    /**
     * Places a ship in the board
     * @details adds a Ship to the vector of smart pointers if there is still space
     * @return [bool] true if placement ended succesfully, false if it didn't
     */
    bool place_ship(const Ship &ship);

    /**
     * Checks if the defenseboard is full
     * @return [bool] true if board is full, false if it's not
     */
    bool is_full() const { return ships_.size() >= 8; }

    /**
     * Checks if a Coordinate is occupied
     * @param c Coordinate to check
     * @return true if position is occupied, false if it's not
     */
    bool is_occupied(Coordinate &c) const;

    /**
     * Checks if a cell is alive
     * @param c Coordinate of the ship to check
     * @return true if it's alive, false if it's not
     */
    bool is_alive(Coordinate &c) const;

    /**
     * Hits a Ship
     * @param c Coordinate of the ship to hit
     * @return [bool] true if i hitted, false if i didn't
     */
    bool hit(Coordinate &c);

    /**
     * Heals a Ship
     * @param c Coordinate of the ship to heal
     * @return [bool] true if i healed, false if i didn't
     */
    bool heal(Coordinate &c);

    /**
     * Returns the unique pointer to the ship passed to the function member
     * @details finds the ship based on the Coordinate passed to the function member
     * @param c center Coordinate of the ship to find and return
     * @return [std::unique_ptr<Ship>] of the ship if it has been found, [NO_SHIP] (nullptr) if the ship hasn't been found
     */
    const std::unique_ptr<Ship> &ship_at(Coordinate c) const;

    /**
     * Returns the ship at a certain index
     * @details returns the ship at a certain index of the vector (useful for the cpu player)
     * @param i int index of the ship at the index to return
     * @return [std::unique_ptr<Ship>] of the ship if it has been found, nullptr if it has not
     */
    const std::unique_ptr<Ship> &ship_at_index(int i) const;

    /**
     * Returns the ships in the log format
     * @details the log format is direction + center [horizontal/vertical] + [Coordinate center]
     * @return std::string with all the ships in the log format
     */
    std::string to_log_format() const;

    /**
     * Removes a ship from the defenseboard
     * @details calls erase() on the vector of smart pointers at the ship's index
     * @return [bool] true if a ship has been found, false if it hasn't
     */
    bool remove_ship(Ship &ship);

   private:
    /**
     * std::vector<std::unique_ptr<Ship>> that contains 3 battleships, 3 support ships and 2 submarines
     */
    std::vector<std::unique_ptr<Ship>> ships_;
};

#endif  // DEFENSEBOARD_H