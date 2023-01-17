/**
 * @author Matteo Galiazzo
 */
#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <ostream>

#include "ship.h"

class Submarine : public Ship {
   public:
    static constexpr char CHARACTER = 'E';
    static constexpr int LENGTH = 1;

    explicit Submarine(Coordinate center = Coordinate{}, Ship::Directions direction = Ship::Directions::HORIZONTAL);

    ~Submarine() override;

    bool action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) override;

    Ship *clone() const override { return new Submarine{*this}; }
};

std::ostream &operator<<(std::ostream &os, const Submarine &submarine);

#endif  // SUBMARINE_H
