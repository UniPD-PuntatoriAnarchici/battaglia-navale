#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include <sstream>

#include "player.h"

class Humanplayer : public Player {
   public:
    Humanplayer() {}
    bool place_ship(const Ship::Type ship_type);
    void turn();
    bool check_delta(int n1, int n2, const Ship::Type ship_type);
    std::vector<Coordinate> split(const std::string &s);

   private:
};

// bool place_ships(); + overload
// place ships_ con le stringhe

#endif