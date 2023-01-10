#ifndef PLAYER_H
#define PLAYER_H

#include <queue>
#include <string>
#include <vector>

#include "./../board/attackboard.h"
#include "./../board/defenseboard.h"

class Player {
   public:
    virtual bool turn(Player &other) = 0;
    virtual bool place_ship(const Ship::Type ship_type) = 0;
    std::vector<std::string> history();
    void print_defense_board();
    void print_attack_board();
    void print_boards();
    Defenseboard &get_defense_board() { return defense_board_; } //NON può essere const: devo colpirla.

   protected:
    Defenseboard defense_board_;
    Attackboard attack_board_;

   private:
};

#endif  // PLAYER_H