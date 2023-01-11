//
// Created by Filippo Tiberio on 24/12/2022.
//

#ifndef SHIP_H
#define SHIP_H

#include <ostream>
#include <vector>
#include <algorithm>

#include "./../coordinate/coordinate.h"

class Attackboard;

class Defenseboard;

class Ship {
public:

    //region directions
    enum class Directions {
        HORIZONTAL, VERTICAL
    };

    friend std::ostream &operator<<(std::ostream &os, const Ship::Directions &direction) {
        os << (((int) direction) == 0 ? "HORIZONTAL" : "VERTICAL");
        return os;
    }
    //endregion directions

    enum class Type {
        BATTLESHIP, REPAIRSHIP, SUBMARINE
    };

    bool is_alive() const;

    /**
     * Virtual!
     */
    virtual ~Ship() = default;

    const Coordinate &center() const { return center_; }

    void set_center(const Coordinate &center) { center_ = center; }

    Directions direction() const { return direction_; }

    void set_direction(Directions direction) { direction_ = direction; }

    const std::vector<bool> &cells() const { return cells_; }

    void reset_cells();

    int armor() const { return armor_; }

    void set_armor(int armor) { armor_ = armor; }

    void hit(Coordinate c);

    void heal(Coordinate c);

    std::vector<std::pair<Coordinate, char>> positions() const;

    std::vector<Coordinate> raw_positions() const;

    virtual Ship *clone() const = 0;

    virtual bool action(Coordinate dest, Defenseboard &opponent, Attackboard &self) = 0;

protected:
    static constexpr char CHARACTER = ' ';
    static constexpr int LENGTH = 0;

    Coordinate center_;
    Directions direction_;
    std::vector<bool> cells_;
    int armor_;
    Type type_;

private:
};

#endif  // SHIP_H
