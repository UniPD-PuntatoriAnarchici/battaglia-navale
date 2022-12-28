#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <ostream>

#include "ship.h"

class Submarine : public Ship {
   public:
    static constexpr char CHARACTER = 'E';
    static constexpr int LENGTH = 1;

    explicit Submarine(
        Coordinate center = Coordinate{},
        Ship::Directions direction = Ship::Directions::HORIZONTAL) {
        cells_ = std::vector<bool>(LENGTH);
        center_ = center;
        direction_ = direction;
        armor_ = LENGTH;
        reset_cells();
    }

    bool action(Coordinate dest, Defenseboard &opponent,
                Attackboard &self) override {
        return true;
    }
};

std::ostream &operator<<(std::ostream &os, const Submarine &submarine);

#endif  // SUBMARINE_H
