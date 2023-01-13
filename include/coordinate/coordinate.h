//
// Created by Matteo Galiazzo on 25/12/2022
//
#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
#include <ostream>

// coordinate can go from 1 to 12
// letter can go from A to N (no J and K)
class Coordinate {
public:

    class INVALID_COORDINATE : public std::exception {
        const char *what() const noexcept override {
            return "Invalid coordinate: Row can go from A to N (no J and K) and Cols can go from 1 to 12";
        }
    };

    Coordinate() : row_{1}, col_{1} {}

    Coordinate(int row, int col);

    Coordinate(char row, int col);

    explicit Coordinate(const std::string &coordinate);

    int row() const {
        return row_;
    }

    void set_row(int row);

    int col() const {
        return col_;
    }

    void set_col(int col);

    static std::pair<int, int> coordinates_to_indexes(Coordinate c);

    static std::pair<char, int> indexes_to_coordinates(Coordinate c);

    bool operator<(const Coordinate &b) const;

    bool operator==(const Coordinate &b) const;

    bool is_valid() const;

    std::string to_string();

    static char customRow_to_char(int row);
private:
    int row_{};
    int col_{};

private:

    static int char_to_customRow(char row);

};

std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);


#endif


