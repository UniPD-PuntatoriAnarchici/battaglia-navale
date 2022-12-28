//
// Created by Filippo Tiberio on 24/12/2022.
//

#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <ostream>

#include "./../coordinate/coordinate.h"

class Attackboard;

class Defenseboard;

class Ship {
public:
    enum class Directions {
        HORIZONTAL, VERTICAL
    };

    friend std::ostream &operator<<(std::ostream &os, const Ship::Directions &direction) {
        os << (((int) direction) == 0 ? "HORIZONTAL" : "VERTICAL");
        return os;
    }

    bool is_alive() const;

    /**
     * Virtual!
     */
    virtual ~Ship() = default;

    static const int length() {
        return length_;
    }

    const Coordinate &center() const {
        return center_;
    }

    void set_center(const Coordinate &center) {
        center_ = center;
    }

    Directions direction() const {
        return direction_;
    }

    void set_direction(Directions direction) {
        direction_ = direction;
    }

    int get_life() const;


protected:
    static constexpr char character_ = ' ';
    static constexpr int length_ = 0;

    Coordinate center_;
    Directions direction_;
    std::vector<bool> cells_;

    virtual bool action(Coordinate dest, Defenseboard &avversario,
                        Attackboard &self) = 0;

private:

};


#endif  // SHIP_H
