//
// Created by filip on 25/12/2022.
//

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "ship.h"

class Battleship : public Ship {
    static constexpr char character_ = 'C';
    static constexpr int length_ = 5;
    std::vector<bool> cells_;

public:
    Battleship() {
        cells_ = std::vector<bool>(length_);
        reset_cells();
    }

public:
    bool action(Coordinate dest, Defenseboard & avversario, Attackboard & self) override {
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

#endif //BATTLESHIP_H
