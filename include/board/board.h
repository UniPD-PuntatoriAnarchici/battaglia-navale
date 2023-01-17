/**
 * @author Tiberio Filippo
 */
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

#include "./../coordinate/coordinate.h"

/**
 * Board Class
 * Generalized version of board.
 *
 * @author Tiberio Filippo
 * @interface pure virtual
 *
 */
class Board {
public:
    /**
     * Type enum class
     * define an internal namespace Type and define two lables: ATTACKBOARD & DEFENSEBOARD
     *
     * @details useful labeling in project workflow
     */
    enum class Type {
        ATTACKBOARD, DEFENSEBOARD
    };

    /**
     * @pure virtual get_all
     * @return an array of <Coordinate,char> pairs containing the position of the board
     * @details derived class will define the correct implementation: attackboard and defenceboard are organized in different ADTs.
     */
    virtual std::vector<std::pair<Coordinate, char>> get_all() const = 0;

    /**
     * @pure virtual get_all_raw
     * get_all "stub-like"
     * @return an array of Coordinate
     * similar to get_all return only the coordinate, useful in all stl method: I don't need to define a custom compare function
     */
    virtual std::vector<Coordinate> get_all_raw() const = 0;

    /**
     * is_valid:
     * verifies f a coordinate is valid.
     * @param c [Coordinate]
     * @return bool, true if valid
     */
    bool is_valid(Coordinate &c) const;

    /**
     * Constexpr: define the side lenght of the board
     */
    static constexpr int side_length = 12;
};

#endif  // BOARD_H