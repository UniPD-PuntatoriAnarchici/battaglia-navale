#ifndef RAPAIRSHIP_H
#define RAPAIRSHIP_H

#include <ostream>

#include "ship.h"

class Repairship : public Ship {
   public:
    static constexpr char CHARACTER = 'S';
    static constexpr int LENGTH = 3;

    ~Repairship() override;

    explicit Repairship(Coordinate center = Coordinate{},
                        Ship::Directions direction = Ship::Directions::HORIZONTAL) ;

    bool action(Coordinate dest, Defenseboard &opponent, Attackboard &self) override {
        return true;
    }

    Ship *clone() const override { return new Repairship{*this}; }
};

std::ostream &operator<<(std::ostream &os, const Repairship &battleship);

#endif