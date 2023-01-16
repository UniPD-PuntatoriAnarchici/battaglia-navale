//
// Created by Matteo Galiazzo on 25/12/2022
//
#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
#include <ostream>
#include <vector>
#include <sstream>

/**
 * Coordinate class
 * coordinate can go from 1 to 12
 * letter can go from A to N (no J and K)
 *
 * Implemented with two ints.
 *
 * Print correctly by using ints as chars
 */
class Coordinate {
public:

    /**
     * INVALID COORDINATE EXCEPTION
     */
    class INVALID_COORDINATE : public std::exception {
        const char *what() const noexcept override {
            return "Invalid coordinate: Row can go from A to N (no J and K) and Cols can go from 1 to 12";
        }
    };

    /**
     * Default constructor:
     * Set coordinate to default A1 (1,1)
     */
    Coordinate() : row_{1}, col_{1} {}

    /**
    * int-int constructor:
    * @param row int row from 1 to 12
    * @param col int col from 1 to 12
    */
    Coordinate(int row, int col);

    /**
     * int-int constructor:
     * @param row char row from A to N (no J and K)
     * @param col int col from 1 to 12
     */
    Coordinate(char row, int col);

    /**
     * explicit constructor: automatically cast string to coordinate
     * @param coordinate std::string string in coordinate format.
     */
    explicit Coordinate(const std::string &coordinate);

    /**
     * Inline row_ getter
     * @return int
     */
    int row() const {
        return row_;
    }

    /**
     * row_ setter. Check for validity
     * @param row int
     */
    void set_row(int row);

    /**
     * Inline col_ getter
     * @return int
     */
    int col() const {
        return col_;
    }

    /**
     * col_ setter. Check for validity
     * @param row int
     */
    void set_col(int col);

    /**
     * Converter Coordinate->std::pair<int, int>
     * @param c coordinate src
     * @return std::pair<int, int> result
     */
    static std::pair<int, int> coordinates_to_indexes(Coordinate c);

    /**
     * Converter Coordinate->std::pair<char, int>
     * @param c coordinate src
     * @return std::pair<char, int> result
     */
    static std::pair<char, int> indexes_to_coordinates(Coordinate c);

    /**
     * Operator < overload: allow to sort grid by row,col
     * @param b coordinate
     * @return bool this greater than b
     */
    bool operator<(const Coordinate &b) const;

    /**
     * Operator == overload: allow to check coordinate equality
     * @param b coordinate
     * @return boolean this equals b
     */
    bool operator==(const Coordinate &b) const;
    bool operator!=(const Coordinate &b) const;


    /**
     * Check coordinate validity
     * @return bool
     */
    bool is_valid() const;

    /**
     * Exporter to string
     * @return coordinate as string
     */
    std::string to_string() const;

    /**
     * Converter
     * @return int row converted to corresponding char
     */
    static char customRow_to_char(int row);

    /**
     * Converter
     * @return char row converted to corresponding int
     */
    static int char_to_customRow(char row);

    /**
     * Splitter: tokenize a string to extract coordinate
     * @param s string
     * @return std::vector<Coordinate>
     */
    static std::vector<Coordinate> split_coordinates(const std::string &s);



private:
    int row_{};
    int col_{};

};

/**
 * Operator < overload: allow to write in stream
 * @param os stream reference
 * @param coordinate coordinate
 * @return stream reference
 */
std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);




#endif


