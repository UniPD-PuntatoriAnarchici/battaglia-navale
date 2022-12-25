//
// Created by filip on 26/12/2022.
//
#include "coordinate.h"

std::pair<int, int> Coordinate::coordinate_to_index(Coordinate c) {
//TODO!
    return std::make_pair(c.row() - 'A', c.col());
}