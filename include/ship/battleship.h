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
     * @param direction [Directions] default value is Horizontal
     */
    explicit Battleship(Coordinate center = Coordinate{},
                        Ship::Directions direction = Ship::Directions::HORIZONTAL);

    /**
     * action: shoots at a Coordinate of the opponent's defense grid
     * @return [bool] true if action is valid
     */
    bool action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) override;

    /**
     * Ship is pure virtual so not instantiable.
     * To create a copy of a specific ship and return a pointer to generic ship a clone method is useful.
     * @return pointer to [Ship]
     */
    Ship *clone() const override { return new Battleship{*this}; }
};

/**
 * @overload operator<<
 */
std::ostream &operator<<(std::ostream &os, const Battleship &battleship);

#endif  // BATTLESHIP_H
