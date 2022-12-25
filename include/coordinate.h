//
// Created by Matteo Galiazzo on 25/12/2022
//
#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

// coordinate can go from 1 to 12
// letter can go from A to N (no J and K)
// TODO: implement checks for coordinates validity
class Coordinate {
public:
    Coordinate() : row_{'A'}, col_{1} {}

    Coordinate(char row, int col) : row_{row}, col_{col} {}

    explicit Coordinate(std::string coordinate) {
        row_ = coordinate.at(0);
        col_ = (int) coordinate.at(1);
    }

    char row() const {
        return row_;
    }

    void set_row(char row) {
        row_ = row;
    }

    int col() const {
        return col_;
    }

    void set_col(int col) {
        col_ = col;
    }

    static std::pair<int, int> coordinate_to_index(Coordinate c);

private:
    char row_;
    int col_;
    static constexpr char row_letters_[] = {'A', 'B', 'C', 'D', 'E', 'F',
                                            'G', 'H', 'I', 'L', 'M', 'N'};
};

#endif