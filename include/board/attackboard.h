/**
 * @author Tiberio Filippo
 */

#ifndef ATTACKBOARD_H
#define ATTACKBOARD_H

#include <vector>
#include <map>

#include "board.h"

/**
 * AttackBoard Class
 * @details to mantain the attackboard the more clean as possibile:
 *  - we decided to use an stl std::map (and not a 12x12 matrix) to save positions: this allow to not loop when clearing board
 *  - we decided to store data as key:Coordinate, value:char for a perfect iteraction with Player::print_inline_boards() and Ship::positions
 *
 * @copy_constructor as default
 * @copy_operator as default
 *
 * @author Tiberio Filippo
 * @extends Board
 */
class Attackboard : public Board {
public:

    /**
     * Default constructor
     * @details default, no need to initialize with a value, neither in replay is required.
     */
    Attackboard();

    /**
     * Get all position of the board
     * @details linearize the sorted map in an arry
     * @implements @pure virtual Board::get_all()
     * @return [std::vector<std::pair<Coordinate, char>>] containing <key,value>s of the sorted map.
     */
    std::vector<std::pair<Coordinate, char>> get_all() const override;

    /**
     * Get all position of the board without the char
     * @details return all map keys
     * @implements @pure virtual Board::get_all_row()
     * @return [std::vector<Coordinate>] containing keys of the sorted map.
     */
    std::vector<Coordinate> get_all_raw() const override;

    /**
     * Inline_ clear_board
     * @details reset the std::map
     */
    void clear_board() {
        cells_.clear();
    }

    /** return the size of the map
     * useful for @test
     * @return number of elemets
     */
    int num_elements() const;

    /**
     * Set a cell as hit
     * @param c Coordinate to be set as hit
     * @details if not blank update
     */
    void hit(Coordinate c);

    /**
     * Set a cell as missed
     * @param c Coordinate to be set as missed
     * @details if not blank update
     */
    void miss(Coordinate c);

    /**
     * Set a cell as revealed
     * @param c Coordinate to be set as revealed
     * @details if not blank update
     * - if ship alive: set Y, otherwise set X as hit.
     * - not calling Hit in order to avoid overhead due to recalling another function with an argument passed by value
     */
    void reveal(Coordinate c, bool is_alive);

    /**
     * Clear a single cell of the board
     * @param c Coordinate to be cleared
     */
    void clear(Coordinate c);

    /**
     * Clear all hits of from the board
     * @details uses iterator to iterate all the map and delete specific object
     * @alternative_solution: call find and clear until find not iterator::end(), [worst]
     */
    void clear_hits();

    /**
     * Clear all misses of from the board
     * @details uses iterator to iterate all the map and delete specific object
     * @alternative_solution: call find and clear until find not iterator::end(), [worst]
     */
    void clear_misses();

    /**
     * Clear all reveals of from the board
     * @details uses iterator to iterate all the map and delete specific object
     * @alternative_solution: call find and clear until find not iterator::end(), [worst]
     */
    void clear_reveals();


private:
    /**
     * stl std::map <Coordinate, Char>
     */
    std::map<Coordinate, char> cells_;

};

#endif