//
// Created by Filippo Tiberio on 26/12/2022.
//
#include "./../../include/coordinate/coordinate.h"

std::pair<int, int> Coordinate::coordinates_to_indexes(Coordinate c) {
    return std::make_pair(c.row(), c.col());
}

std::pair<char, int> Coordinate::indexes_to_coordinates(Coordinate c) {

    return std::make_pair(customRow_to_char(c.row()), c.col());
}

std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate) {
    std::pair<char, int> customCoord = Coordinate::indexes_to_coordinates(coordinate);

    os << "Coordinate: (" << customCoord.first << ", " << customCoord.second << "), [" << coordinate.row() << ", "
       << coordinate.col() << "] ";
    return os;
}
