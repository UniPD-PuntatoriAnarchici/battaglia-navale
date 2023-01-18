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

    void place_all_ships();

    virtual void turn(Player &other) = 0;

    virtual void place_ship(const Ship::Type ship_type) = 0;

    std::vector<std::string> player_history();

    int add_to_player_history(const std::string &action);

    void print_board(const Board::Type boardtype, std::ostream &os = std::cout);

    void print_boards();

    void print_boards_inline(std::ostream &os = std::cout);

    bool is_alive() const;

    Defenseboard &get_defense_board() { return defense_board_; }  // NON può essere const: devo colpirla.

    bool valid_ship_placement(Coordinate center, int length, Ship::Directions direction);

   protected:
    Defenseboard defense_board_;
    Attackboard attack_board_;

    std::vector<std::string> player_history_;

   private:
};

#endif  // PLAYER_H