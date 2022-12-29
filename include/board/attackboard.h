#ifndef ATTACKBOARD_H
#define ATTACKBOARD_H

#include <vector>

#include "board.h"

class Battleship;  // TODO others
class Submarine;

class Attackboard : public Board {
   public:
    Attackboard();

    std::vector<Coordinate> get_all();

   private:
      std::vector<Battleship> place_battleships();
      std::vector<Coordinate> split(const std::string &s);
};

#endif