//
// Created by filip on 25/12/2022.
//

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <ostream>

#include "ship.h"

class Battleship : public Ship {
   public:
    static constexpr char CHARACTER = 'C';
    static constexpr int LENGTH = 5;
    static constexpr Type TYPE = Type::BATTLESHIP;

    explicit Battleship(Coordinate center = Coordinate{},
                        Ship::Directions direction = Ship::Directions::HORIZONTAL) {
        cells_ = std::vector<bool>(LENGTH);
        center_ = center;
        direction_ = direction;
        armor_ = LENGTH;
        reset_cells();
    }

    bool action(Coordinate dest, Defenseboard &opponent, Attackboard &self) override {
        return true;
    }

    Ship *clone() const override { return new Battleship{*this}; }
};

std::ostream &operator<<(std::ostream &os, const Battleship &battleship);

#endif  // BATTLESHIP_H
