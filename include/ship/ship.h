//
// Created by Filippo Tiberio on 24/12/2022.
//

#ifndef SHIP_H 
#define SHIP_H

#include <vector>
#include "coordinate.h"

class Ship {
public:
    enum class Directions {
        HORIZONTAL, VERTICAL
    };

protected:
    static constexpr char character_ = ' ';
    static constexpr int length_ = 0;

    Coordinate center_;
    Directions direction_;
    std::vector<bool> cells_;

    virtual bool action() = 0;



private:
    int get_life() const;

};
#endif // SHIP_H
