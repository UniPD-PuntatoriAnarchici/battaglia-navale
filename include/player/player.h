#ifndef PLAYER_H
#define PLAYER_H

#include <queue>
#include <string>
#include <vector>

#include "./../board/attackboard.h"
#include "./../board/defenseboard.h"

class Player {
   public:
    virtual void turn() = 0;
    virtual bool place_ships() = 0;
    std::vector<std::string> history();
    void print_defense_board();

   protected:
    Defenseboard defense_board_;
    Attackboard attack_board_;

   private:
};

#endif  // PLAYER_H