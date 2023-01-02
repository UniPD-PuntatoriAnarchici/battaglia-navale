//
// Created by Matteo Galiazzo on 25/12/2022
//
#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
#include <ostream>

// coordinate can go from 1 to 12
// letter can go from A to N (no J and K)
// TODO: implement checks for coordinates validity
class Coordinate {
public:

    class INVALID_COORDINATE : public std::exception {
        const char *what() const noexcept override {
            return "Invalid coordinate: Row can go from A to N (no J and K) and Cols can go from 1 to 12";
        }
    };

    Coordinate() : row_{1}, col_{1} {}

    Coordinate(int row, int col) : row_{row}, col_{col} {
        if (!is_valid())
            throw INVALID_COORDINATE{};
    }

    Coordinate(char row, int col) : col_{col} {
        if (row == 'J' || row == 'K')
            throw INVALID_COORDINATE{};

        row_ = char_to_customRow(row);

        if (!is_valid())
            throw INVALID_COORDINATE{};
    }

    explicit Coordinate(const std::string &coordinate) {
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

    int row() const {
        return row_;
    }

    void set_row(int row) {
        int oldRow = row_;
        row_ = row;

        if (!is_valid()) {
            row_ = oldRow;
            throw INVALID_COORDINATE{};
        }
    }

    int col() const {
        return col_;
    }

    void set_col(int col) {
        int oldCol = col_;
        col_ = col;

        if (!is_valid()) {
            col_ = oldCol;
            throw INVALID_COORDINATE{};
        }
    }

    static std::pair<int, int> coordinates_to_indexes(Coordinate c);

    static std::pair<char, int> indexes_to_coordinates(Coordinate c);

    bool operator<(const Coordinate &b) const;

    bool equals(int r, int c) const;

    bool operator==(const Coordinate &b) const;

    bool is_valid() const {
        if (row_ < 1 || row_ > 12)
            return false;

        if (col_ < 1 || col_ > 12)
            return false;

        return true;
    }

private:
    int row_{};
    int col_{};
    static constexpr char row_letters_[] = {'A', 'B', 'C', 'D', 'E', 'F',
                                            'G', 'H', 'I', 'L', 'M', 'N'};

private:

    static int char_to_customRow(char row) {
        int tmpRow = 0;
        if (row == 'J' || row == 'K')
            return -1;

        tmpRow = (int) (row - 'A') + 1;

        if (row >= 'J')
            tmpRow -= 2;

        return tmpRow;
    }

    static char customRow_to_char(int row) {
        char tmpRow = 'A' - 1;
        if (row < 1 || row > 12)
            return '#';

        tmpRow += row;

        if (row >= 9)
            tmpRow += 2;

        return tmpRow;
    }
};

std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);




#endif


