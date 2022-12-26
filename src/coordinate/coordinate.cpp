//
// Created by Filippo Tiberio on 26/12/2022.
//
#include "./../../include/coordinate/coordinate.h"

std::pair<int, int> Coordinate::coordinate_to_index(Coordinate c) {
//TODO!
    return std::make_pair(c.row() - 'A', c.col());
}