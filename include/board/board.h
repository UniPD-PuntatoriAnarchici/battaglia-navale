/**
 * @author Tiberio Filippo
 */
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

#include "./../coordinate/coordinate.h"

class Board {
public:
    enum class Type {
        ATTACKBOARD, DEFENSEBOARD
    };

    virtual std::vector<std::pair<Coordinate, char>> get_all() const = 0;

    virtual std::vector<Coordinate> get_all_raw() const = 0;

    bool is_valid(Coordinate &c);

    static constexpr int side_length = 12;
};

#endif  // BOARD_H