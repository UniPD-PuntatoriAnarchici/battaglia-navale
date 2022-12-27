//
// Created by Matteo Galiazzo on 25/12/2022
//

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include "./../coordinate/coordinate.h"
#include "./../ship/battleship.h"


class Board {
public:
    virtual std::vector<Coordinate> get_all() = 0;

    bool is_valid(Coordinate &c);

    bool is_occupied(Coordinate &c);

    static constexpr int side_length = 12;

private:
    // declaring array of smart pointers (ships) with 7 ships:
    // battle (3) repair (3) and submarine (2)
    std::array<std::unique_ptr<Ship>, 7> ships;
};

#endif //BOARD_H