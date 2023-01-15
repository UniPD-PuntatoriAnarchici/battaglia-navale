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

    ~Battleship() override;

    explicit Battleship(Coordinate center = Coordinate{},
                        Ship::Directions direction = Ship::Directions::HORIZONTAL);

    bool action(Coordinate dest, Defenseboard &opponent, Attackboard &self) override;

    Ship *clone() const override { return new Battleship{*this}; }
};

std::ostream &operator<<(std::ostream &os, const Battleship &battleship);

#endif  // BATTLESHIP_H
