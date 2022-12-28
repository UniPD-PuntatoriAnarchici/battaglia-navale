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
};

#endif