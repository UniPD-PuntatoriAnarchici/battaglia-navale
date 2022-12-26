#ifndef ATTACKBOARD_H
#define ATTACKBOARD_H

#include <vector>

#include "board.h"

class Attackboard : public Board {
   public:
    Attackboard();
    virtual std::vector<Coordinate> get_all();

   private:
};

#endif