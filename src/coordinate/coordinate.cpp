/**
 * @author Tiberio Filippo
 */

#include "./../../include/coordinate/coordinate.h"

//region constructors

/**
* int-int constructor:
* @param row int row from 1 to 12
* @param col int col from 1 to 12
*/
Coordinate::Coordinate(int row, int col) : row_{row}, col_{col} {
    if (!is_valid())
        throw INVALID_COORDINATE{};
}

/**
 * int-int constructor:
 * @param row char row from A to N (no J and K)
 * @param col int col from 1 to 12
 */
Coordinate::Coordinate(char row, int col) : col_{col} {
    if (row == 'J' || row == 'K')
        throw INVALID_COORDINATE{};

    row_ = char_to_customRow(row);

    if (!is_valid())
        throw INVALID_COORDINATE{};
}

/**
 * explicit constructor: automatically cast string to coordinate
 * @param coordinate std::string string in coordinate format.
 */
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
/**
 * row_ setter. Check for validity
 * @param row int
 */
void Coordinate::set_row(int row) {
    int oldRow = row_;
    row_ = row;

    if (!is_valid()) {
        row_ = oldRow;
        throw INVALID_COORDINATE{};
    }
}

/**
 * Inline col_ getter
 * @return int
 */
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
/**
 * Converter Coordinate->std::pair<int, int>
 * @param c coordinate src
 * @return std::pair<int, int> result
 */
std::pair<int, int> Coordinate::coordinates_to_indexes(Coordinate c) {
    return std::make_pair(c.row(), c.col());
}

/**
 * Converter Coordinate->std::pair<char, int>
 * @param c coordinate src
 * @return std::pair<char, int> result
 */
std::pair<char, int> Coordinate::indexes_to_coordinates(Coordinate c) {
    return std::make_pair(customRow_to_char(c.row()), c.col());
}

/**
 * Splitter: tokenize a string to extract coordinate
 * @param s string
 * @return std::vector<Coordinate>
 */
std::vector<Coordinate> Coordinate::split_coordinates(const std::string &s) {
    std::vector<Coordinate> coordinates;
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, ' ')) coordinates.emplace_back(item);
    return coordinates;
}
//endregion converters

//region operators
/**
 * Operator < overload: allow to sort grid by row,col
 * @param b coordinate
 * @return bool this greater than b
 */
bool Coordinate::operator<(const Coordinate &b) const {
    if (row_ < b.row_)
        return true;
    if (b.row_ < row_)
        return false;
    return col_ < b.col_;

}

/**
 * Operator == overload: allow to check coordinate equality
 * @param b coordinate
 * @return boolean this equals b
 */
bool Coordinate::operator==(const Coordinate &b) const {
    return row_ == b.row_ &&
           col_ == b.col_;
}

bool Coordinate::operator!=(const Coordinate &b) const {
    return !(b == *this);
}

/**
 * Operator < overload: allow to write in stream
 * @param os stream reference
 * @param coordinate coordinate
 * @return stream reference
 */
std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate) {
    std::pair<char, int> customCoord = Coordinate::indexes_to_coordinates(coordinate);

    os << "Coordinate: (" << customCoord.first << ", " << customCoord.second << "), [" << coordinate.row() << ", "
       << coordinate.col() << "] ";
    return os;
}
//endregion

//region utilities
/**
 * Exporter to string
 * @return coordinate as string
 */
std::string Coordinate::to_string() const {
    std::pair<char, int> customCoord = Coordinate::indexes_to_coordinates(*this);
    return std::string(1, customCoord.first) + std::to_string(customCoord.second);
}

/**
 * Check coordinate validity
 * @return bool
 */
bool Coordinate::is_valid() const {
    if (row_ < 1 || row_ > 12)
        return false;

    if (col_ < 1 || col_ > 12)
        return false;

    return true;
}
//endregion utilities

//region helpers
/**
* Converter
* @return char row converted to corresponding int
*/
int Coordinate::char_to_customRow(char row) {
    int tmpRow = 0;
    if (row == 'J' || row == 'K')
        return -1;

    tmpRow = (int) (row - 'A') + 1;

    if (row >= 'J')
        tmpRow -= 2;

    return tmpRow;
}

/**
 * Converter
 * @return int row converted to corresponding char
 */
char Coordinate::customRow_to_char(int row) {
    char tmpRow = 'A' - 1;
    if (row < 1 || row > 12)
        return '#';

    tmpRow += row;

    if (row > 9)
        tmpRow += 2;

    return tmpRow;
}
//endregion helpers

