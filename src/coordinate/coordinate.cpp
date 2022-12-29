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

bool Coordinate::operator<(const Coordinate &b) const {
    if (row_ < b.row_)
        return true;
    if (b.row_ < row_)
        return false;
    return col_ < b.col_;

}

bool Coordinate::equals(int r, int c) const {
    if (row_ == r && col_ == c)
        return true;

    return false;
}

bool Coordinate::operator==(const Coordinate &b) const {
    return row_ == b.row_ &&
           col_ == b.col_;
}

std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate) {
    std::pair<char, int> customCoord = Coordinate::indexes_to_coordinates(coordinate);

    os << "Coordinate: (" << customCoord.first << ", " << customCoord.second << "), [" << coordinate.row() << ", "
       << coordinate.col() << "] ";
    return os;
}
