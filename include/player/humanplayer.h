#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include <sstream>

#include "player.h"

class Humanplayer : public Player {
   public:
    Humanplayer() {}
    bool place_ships();
    void turn();
    std::vector<Submarine> place_submarines();
    int ship_length(int n1, int n2);
    std::vector<Coordinate> split(const std::string &s);

   private:
};

// bool place_ships(); + overload
// place ships con le stringhe

#endif