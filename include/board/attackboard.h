#ifndef ATTACKBOARD_H
#define ATTACKBOARD_H

#include <vector>
#include <map>

#include "board.h"

class Attackboard : public Board {
public:

    Attackboard();

    std::vector<std::pair<Coordinate,char>> get_all() override;

    void clear_board() {
        cells_.clear();
    }

    int num_elements() const;

    void hit(Coordinate c);
    void miss(Coordinate c);
    void reveal(Coordinate c);

    void clear_hits();
    void clear_misses();
    void clear_reveals();

private:
    std::map<Coordinate, char> cells_;

};

#endif