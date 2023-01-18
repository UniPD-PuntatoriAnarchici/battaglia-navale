/**
 * @author Galiazzo Matteo
 */

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class Humanplayer : public Player {
   public:
    ~Humanplayer() override;

    /**
     * Default constructor
     * @details default, no need to initialize with a value
     */
    Humanplayer() = default;

    /**
     * Places a ship on the defenseboard
     * @param ship_type enum of the class Ship, used to identify the type of ship to place down
     * @details the function member asks for the details of the ship and places it down on the board
     */
    void place_ship(const Ship::Type ship_type) override;

    /**
     * Checks the ship length
     * @param n1 row/column of the ship, used to calculate the center
     * @param n2 row/column of the ship, used to calculate the center
     * @param ship_type used to identify the ship length
     * @return [bool] true if the length is the same as the ship type length, false if it's not
     */
    bool check_ship_length(int n1, int n2, const Ship::Type ship_type);

    /**
     * Calculates the center coordinate of a ship
     * @param c1
     * @param c2
     * @param direction used to know if the center is on a different row or a different column
     * @param ship_type used to identify the ship length
     * @return [Coordinate] the center coordinate of a ship
     */
    Coordinate get_ship_center(Coordinate c1, Coordinate c2, Ship::Directions direction, Ship::Type ship_type);

    /**
     * Executes the turn of a human player
     * @param other Player to execute action on his defenseboard
     * @details the function member asks for an action, processes it and save the result on the player history
     */
    void turn(Player &other) override;

    /**
     * Splits a string into 2 coordinates
     * @param s std::string to split
     * @return [std::vector<Coordinate>] with the coordinates
     */
    std::vector<Coordinate> split_coordinates(const std::string &s);

    /**
     * Splits a string in 2 strings
     * @param s std::string to split
     * @return [std::vector<std::string>] with the strings
     */
    std::vector<std::string> split_string(const std::string &s);

   private:
};

#endif  // HUMANPLAYER_H
