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
      std::vector<Submarine> place_submarines();
      std::vector<Coordinate> split(const std::string &s);
      int ship_length(int n1, int n2);
};

#endif