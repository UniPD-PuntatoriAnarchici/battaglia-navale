//
// Created by Matteo Galiazzo on 25/12/2022
//

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

#include "./../coordinate/coordinate.h"

struct minpQElements {
    Coordinate c;
    char toPrint{' '};
    bool isCenter{false};

    explicit minpQElements(const Coordinate &c, char toPrint = ' ', bool isCenter = true)
        : c(c), toPrint(toPrint), isCenter(isCenter) {}
};

class Board {
   public:
    virtual std::vector<Coordinate> get_all() = 0;

    bool is_valid(Coordinate &c);

    bool is_occupied(Coordinate &c);

    static constexpr int side_length = 12;
};

#endif  // BOARD_H