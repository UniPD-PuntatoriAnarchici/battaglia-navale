#ifndef RAPAIRSHIP_H
#define RAPAIRSHIP_H

#include <ostream>

#include "ship.h"

class Repairship : public Ship{
    public:
    static constexpr char CHARACTER = 'S';
    static constexpr int LENGTH = 3;

    explicit Repairship(Coordinate center = Coordinate{},Ship::Directions direction = Ship::Directions::HORIZONTAL){
      cells_ = std::vector<bool>(LENGTH);
        center_ = center;
        direction_ = direction;
        armor_ = LENGTH;
        reset_cells();
    }
    
    bool action(Coordinate dest, Defenseboard &opponent, Attackboard &self) override {
        return true;
    }
};

std::ostream &operator<<(std::ostream &os, const Repairship &battleship);

#endif