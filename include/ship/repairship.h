/**
 * @author Rampin Matteo
 */

#ifndef RAPAIRSHIP_H
#define RAPAIRSHIP_H

#include <ostream>

#include "ship.h"

/**
 * Repairship class
 *
 * @action moves the Repairship and repairs ships in a 3x3
 *
 * @extends Ship
 * @author Rampin Matteo
 */
class Repairship : public Ship {
   public:
    static constexpr char CHARACTER = 'S';
    static constexpr int LENGTH = 3;

    /**
     * @Override virtual destructor
     * @details
     * We use an array of smart pointer in defenseboard.
     * In order to prevent problems with implicit destructors and implicit calls to the destructors we chose to completely
     * define destructors and define the ship's one as pure virtual. In this way we ensure the correct execution of the
     * destroying chain.
     */
    ~Repairship() override;

    /**
     * Explicit default constructor
     * @param center [Coordinate] default value is invalid.
     * @param direction [Directions] default value is Horizontal
     */
    explicit Repairship(Coordinate center = Coordinate{}, Ship::Directions direction = Ship::Directions::HORIZONTAL);

    /**
     * Action of the Repairship
     * @details moves the repairship and repairs ships in a 3x3
     * @param dest Coordinate where the submarine will move and repair
     * @param self_defense Defenseboard the board where the submarine is in and where it repairs the ships
     * @param self_attack Attackboard of the other player
     * @param opponent Defenseboard of the other player
     * @return [bool] true if the action finished succesfully
     */
    bool action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) override;

    /**
     * Clones a Repairship by returning a new pointer to it 
     * @return [Ship] pointer to Repairship
     */
    Ship *clone() const override { return new Repairship{*this}; }
};
/**
 * Print of Repairship
 * @overload operator<<
 * @param   os             : output stream
 * @param   repairship     : repairship to print
 * @return {std::ostream}  : reference of the output stream
 */
std::ostream &operator<<(std::ostream &os, const Repairship &repairship);

#endif