/**
 * @author Rampin Matteo
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <queue>
#include <string>
#include <vector>

#include "./../board/attackboard.h"
#include "./../board/defenseboard.h"
#include "./../utils/colors.h"

/**
 * Ship Class
 * Generalized version of ship.
 *
 *
 */
class Player {
   public:

    /**
     * Pure virtual destructor
     * @details
     * We use 2 smart pointer of Player type in replay.
     * To avoid problems with destruction of object we decided to implement all the destructors
     *
     * @related Replay, HumanPlayer, CpuPlayer
     */
    virtual ~Player() = 0;

    /**
     * Function that place all ships
     */
    void place_all_ships();

    /**
     * @pure virtual turn
     * @param  other Player to execute action
     * @details derived class will define the implementation : execute the turn of the player
     */
    virtual void turn(Player &other) = 0;

    /**
     * Places a ship on the board
     * @pure virtual place_ship
     * @param  enum of the class Ship, used to identify the type of ship to place down
     * @details derived class will define the implementation : place ship on board
     */
    virtual void place_ship(const Ship::Type ship_type) = 0;

    /**
     * Function that return historical moves
     * @return {std::vector<std::string>}  : history of the invoking player 
     */
    std::vector<std::string> player_history();

    /**
     * 
     * @param  {std::string} action : add to player_history_ the action
     * @return {int}                : Returns the number of elements in the vector
     */
    int add_to_player_history(const std::string &action);
    
    /**
     * print the board passed as parameter
     * @param  {Board::Type} boardtype : Type of board to be printed (DefenseBoard/Attackboard)
     * @param  {std::ostream} os       : Output stream object
     */
    void print_board(const Board::Type boardtype, std::ostream &os = std::cout);

    /**
     * Prints Defenseboard and Attackboard
     */
    void print_boards();

    /**
     * print the boards side by side
     * @param  {std::ostream} os : output stream object to print output operations
     */
    void print_boards_inline(std::ostream &os = std::cout);

    /**
     * checks if there are live ships
     * @return {bool}  : true if there are live ships,false otherwise
     */
    bool is_alive() const;
    /**
     * Function that return defenseboard
     * @return {Defenseboard}  : player's defenseboard
     */
    Defenseboard &get_defense_board() { return defense_board_; }  // NON può essere const: devo colpirla.

    /**
     * check if a ship goes beyond the board,check if the positions where the ship should be placed are occupied
     * @param  {Coordinate} center          : Ship's center
     * @param  {int} length                 : Ship's length
     * @param  {Ship::Directions} direction : Ship's direction (vertical/horizontal)
     * @return {bool}                       : true if it can be placed,false otherwise
     */
    bool valid_ship_placement(Coordinate center, int length, Ship::Directions direction);

   protected:
    /**
     * Player's Defenseboard
     */
    Defenseboard defense_board_;

    /**
     * Player's Attackboard
     */
    Attackboard attack_board_;

    /**
     * player's move history
     */
    std::vector<std::string> player_history_;

   private:
};

#endif  // PLAYER_H