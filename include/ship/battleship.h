/**
 * @author Tiberio Filippo
 */

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <ostream>

#include "ship.h"

/**
 * Battleship Class
 *
 * @action shoots at a Coordinate of the opponent's defense grid
 *
 * @extends Ship
 * @author Tiberio Filippo
 */
class Battleship : public Ship {
public:
    static constexpr char CHARACTER = 'C';
    static constexpr int LENGTH = 5;

    /**
     * @Override virtual destructor
     * @details
     * We use an array of smart pointer in defenseboard.
     * In order to prevent problems with implicit destructors and implicit calls to these, we opted to completely define destructors
     * and define the ship's one as pure virtual. In this way we ensure the correct execution of the destroying chain.
     */
    ~Battleship() override;

    /**
     * Explicit default constructor
     * @param center [Coordinate] default value is invalid.
     * @param direction
     */
    explicit Battleship(Coordinate center = Coordinate{},
                        Ship::Directions direction = Ship::Directions::HORIZONTAL);

    bool action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) override;

    Ship *clone() const override { return new Battleship{*this}; }
};

std::ostream &operator<<(std::ostream &os, const Battleship &battleship);

#endif  // BATTLESHIP_H
