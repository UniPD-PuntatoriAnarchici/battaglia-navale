//
// Created by filip on 25/12/2022.
//

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <ostream>
#include "ship.h"

class Battleship : public Ship {
    static constexpr char character_ = 'C';
    static constexpr int length_ = 5;

public:
    explicit Battleship(Coordinate center = Coordinate{}, Ship::Directions direction = Ship::Directions::HORIZONTAL) {
        cells_ = std::vector<bool>(length_);
        reset_cells();
        center_ = center;
        direction_ = direction;
    }

public:
    bool action(Coordinate dest, Defenseboard &avversario, Attackboard &self) override {
        return true;
    }

    static char character() {
        return character_;
    }

    static int length() {
        return length_;
    }

    const std::vector<bool> &get_cells() const {
        return cells_;
    }

    void reset_cells() {
        for (int i = 0; i < length_; i++)
            cells_[i] = true;
    }

};

std::ostream &operator<<(std::ostream &os, const Battleship &battleship);

#endif //BATTLESHIP_H
