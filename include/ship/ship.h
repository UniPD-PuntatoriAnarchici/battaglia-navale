/**
 * @author Tiberio Filippo
 */

#ifndef SHIP_H
#define SHIP_H

#include <ostream>
#include <vector>
#include <algorithm>

#include "./../coordinate/coordinate.h"

/**
 * Forward reference to Attackboard
 */
class Attackboard;

/**
 * Forward reference to Defenseboard
 * - Defenseboard has ships
 * - Ships do an action on a defenseboard
 *  => cyclic dependency.
 */
class Defenseboard;

/**
 * Ship Class
 * Generalized version of ship.
 *
 * @author Tiberio Filippo
 * @interface pure virtual
 *
 */
class Ship {
public:
    /**
     * DEAD_SHIP [Exception]
     * throwed when an action is called over a dead ship.
     *
     * @deprecated Now game manager and player treat an invalid action with true/false return value
     */
    class DEAD_SHIP : public std::exception {
        const char *what() const noexcept override {
            return "Can't call an action on a dead ship!";
        }
    };

    //region directions
    /**
     * Directions enum class
     * define an internal namespace Directions and define two lables: HORIZONTAL & VERTICAL
     *
     * @details Uses a friend operator<<
     */
    enum class Directions {
        HORIZONTAL, VERTICAL
    };

    /**
     * operator<< [friend]
     * "literalise" enum
     */
    friend std::ostream &operator<<(std::ostream &os, const Ship::Directions &direction) {
        os << (((int) direction) == 0 ? "HORIZONTAL" : "VERTICAL");
        return os;
    }
    //endregion directions

    /**
     * Type enum class
     * define an internal namespace Type and define three lables: BATTLESHIP, REPAIRSHIP & SUBMARINE
     *
     * @details useful labeling in project workflow
     */
    enum class Type {
        BATTLESHIP = 5, REPAIRSHIP = 3, SUBMARINE = 1
    };

    /**
     * Check if ship is alive.
     * @details Check if ship is alive by checking the armor value. Doesn't iterate over cells
     * @return bool
     */
    bool is_alive() const;

    /**
     * Pure virtual destructor
     * @details
     * We use an array of smart pointer in defenseboard.
     * In order to prevent problems with implicit destructors and implicit calls to these, we opted to completely define destructors
     * and define the ship's one as pure virtual. In this way we ensure the correct execution of the destroying chain.
     */
    virtual ~Ship() = 0;

    /**
     * Ship's type getter
     */
    Type type() const;

    /**
     * Center getter [inline]
     * @return const reference to [Coordinate]
     */
    const Coordinate &center() const { return center_; }

    /**
     * Center setter [inline]
     * @param center [Coordinate] not checking the validity: Coord can't be created or set invalid
     */
    void set_center(const Coordinate &center) { center_ = center; }

    /**
     * Direction getter [inline]
     * @return [Directions] copy
     */
    Directions direction() const { return direction_; }

    /**
     * Direction setter [inline]
     * @param direction [Directions]
     */
    void set_direction(Directions direction) { direction_ = direction; }

    /**
     * Get ship's status cells [inline]
     * @return const reference to bool vector
     */
    const std::vector<bool> &cells() const { return cells_; }

    /**
     * Reset all ship's cells. (Do not restore armor!)
     */
    void reset_cells();

    /**
     * Armor getter
     * @return int
     */
    int armor() const { return armor_; }

    /**
     * Armor setter
     * @param armor int
     */
    void set_armor(int armor) { armor_ = armor; }

    /**
     * Set ship as hit in a specific position
     * @throws Coordinate::INVALID_COORDINATE if coordinate doesn't belong to current ship
     * @param c [Coordinate]
     */
    void hit(Coordinate c);

    /**
     * Reset armor and cells of the ship
     */
    void heal();

    /**
     * Get all coordinate occupied by current ship: decorated with current status
     * @return [std::vector<std::pair<Coordinate, char>>]
     */
    std::vector<std::pair<Coordinate, char>> positions() const;

    /**
     * Get all coordinate occupied by current ship
     * @return [std::vector<Coordinate>]
     */
    std::vector<Coordinate> raw_positions() const;

    /**
     * Ship is pure virtual so not instantiable.
     * To create a copy of a specific ship and return a pointer to generic ship a clone method is useful.
     * @return pointer to [Ship]
     */
    virtual Ship *clone() const = 0;

    /**
     * Pure virtual action, each ship will implement the correct one
     * @return [bool] true if action is valid
     */
    virtual bool
    action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) = 0;

protected:
    static constexpr char CHARACTER = ' ';
    static constexpr int LENGTH = 0;

    /**
     * Ship center
     */
    Coordinate center_;
    /**
     * Ship Direction
     */
    Directions direction_;
    /**
     * Ship cells containing the current status of the ship. (true = alive)
     */
    std::vector<bool> cells_;
    /**
     * Current armor
     */
    int armor_;
    /**
     * Ship type. Useful for labeling
     */
    Type type_;
};


#endif  // SHIP_H
