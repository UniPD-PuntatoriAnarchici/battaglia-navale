#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <sstream>

#include "player.h"

class Humanplayer : public Player {
   public:
    Humanplayer() {}
    bool place_ships();
    void turn();
    std::vector<Submarine> place_submarines();
    bool check_delta(int n1, int n2);
    std::vector<Coordinate> split(const std::string &s);

   private:
};

// bool place_ships(); + overload
// place ships_ con le stringhe

#endif  // HUMANPLAYER_H
