//
// Created by Filippo Tiberio on 26/12/2022.
//
#include "./../../include/coordinate/coordinate.h"

//region constructors
Coordinate::Coordinate(int row, int col) : row_{row}, col_{col} {
    if (!is_valid())
        throw INVALID_COORDINATE{};
}

Coordinate::Coordinate(char row, int col) : col_{col} {
    if (row == 'J' || row == 'K')
        throw INVALID_COORDINATE{};

    row_ = char_to_customRow(row);

    if (!is_valid())
        throw INVALID_COORDINATE{};
}

Coordinate::Coordinate(const std::string &coordinate) {
    if (coordinate.empty() || coordinate.length() < 2)
        throw INVALID_COORDINATE{};

    row_ = char_to_customRow(coordinate.at(0));

    if (coordinate.length() == 2) {
        col_ = (int) (coordinate.at(1) - '0');
    } else {
        col_ = std::stoi(coordinate.substr(1, coordinate.length()));
    }

    if (!is_valid())
        throw INVALID_COORDINATE{};
}
//endregion

//region setters
void Coordinate::set_row(int row) {
    int oldRow = row_;
    row_ = row;

    if (!is_valid()) {
        row_ = oldRow;
        throw INVALID_COORDINATE{};
    }
}

void Coordinate::set_col(int col) {
    int oldCol = col_;
    col_ = col;

    if (!is_valid()) {
        col_ = oldCol;
        throw INVALID_COORDINATE{};
    }
}
//endregion setters

//region converters
std::pair<int, int> Coordinate::coordinates_to_indexes(Coordinate c) {
    return std::make_pair(c.row(), c.col());
}

std::pair<char, int> Coordinate::indexes_to_coordinates(Coordinate c) {
    return std::make_pair(customRow_to_char(c.row()), c.col());
}
//endregion converters

//region operators
bool Coordinate::operator<(const Coordinate &b) const {
    if (row_ < b.row_)
        return true;
    if (b.row_ < row_)
        return false;
    return col_ < b.col_;

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
//endregion

//region utilities
std::string Coordinate::to_string() {
    std::pair<char, int> customCoord = Coordinate::indexes_to_coordinates(*this);
    return std::string(1, customCoord.first) + std::to_string(customCoord.second);
}

bool Coordinate::is_valid() const {
    if (row_ < 1 || row_ > 12)
        return false;

    if (col_ < 1 || col_ > 12)
        return false;

    return true;
}
//endregion utilities

//region helpers
int Coordinate::char_to_customRow(char row) {
    int tmpRow = 0;
    if (row == 'J' || row == 'K')
        return -1;

    tmpRow = (int) (row - 'A') + 1;

    if (row >= 'J')
        tmpRow -= 2;

    return tmpRow;
}

char Coordinate::customRow_to_char(int row) {
    char tmpRow = 'A' - 1;
    if (row < 1 || row > 12)
        return '#';

    tmpRow += row;

    if (row >= 9)
        tmpRow += 2;

    return tmpRow;
}
//endregion helpers

