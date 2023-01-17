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
    virtual ~Player() = 0;

    void place_all_ships();

    virtual bool turn(Player &other) = 0;

    virtual bool place_ship(const Ship::Type ship_type) = 0;

    std::vector<std::string> player_history();

    int add_to_player_history(const std::string &action);

    void print_board(const Board::Type boardtype, std::ostream &os = std::cout);

    void print_boards();

    void print_boards_inline(std::ostream &os = std::cout);

    bool is_alive() const;

    Defenseboard &get_defense_board() { return defense_board_; }  // NON può essere const: devo colpirla.

protected:
    Defenseboard defense_board_;
    Attackboard attack_board_;

    std::vector<std::string> player_history_;

private:
};

#endif  // PLAYER_H