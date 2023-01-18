/**
 * @author Matteo Galiazzo
 */

#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <ostream>

#include "ship.h"

/**
 * Submarine class
 *
 * @action moves the submarine and scans the surrounding cells in a 5x5
 *
 * @extends Ship
 * @author Galiazzo Matteo
 */
class Submarine : public Ship {
   public:
    static constexpr char CHARACTER = 'E';
    static constexpr int LENGTH = 1;

    /**
     * @Override virtual destrucctor
     * @details
     * We use an array of smart pointer in defenseboard.
     * In order to prevent problems with implicit destructors and implicit calls to the destructors we chose to completely
     * define destructors and define the ship's one as pure virtual. In this way we ensure the correct execution of the
     * destroying chain.
     */
    ~Submarine() override;

    /**
     * Explicit default constructor
     * @param center [Coordinate] default value is invalid
     * @param direction not useful in submarine but required since it extends ship
     */
    explicit Submarine(Coordinate center = Coordinate{}, Ship::Directions direction = Ship::Directions::HORIZONTAL);

    /**
     * Action of the submarine
     * @details moves the submarine and scans the surrounding cells in a 5x5
     * @param dest Coordinate where the submarine will move and scan
     * @param self_defense Defenseboard the board where the submarine is in
     * @param self_attack Attackboard where the submarine will show the scanning results
     * @param opponent Defenseboard where the submarine will perform the scan
     * @return [bool] true if the action finished succesfully
     */
    bool action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) override;

    /**
     * Clones a Submarine by returning a new pointer to it
     * @details Function member used to place a submarine in the board, returns a new submarine
     * @return [Ship] pointer to Submarine
     */
    Ship *clone() const override { return new Submarine{*this}; }
};

/**
 * Print of the submarine
 * @details detailed submarine print
 * @param os output stream
 * @param submarine to print
 * @return [std::ostream] reference of the output stream
 */
std::ostream &operator<<(std::ostream &os, const Submarine &submarine);

#endif  // SUBMARINE_H
