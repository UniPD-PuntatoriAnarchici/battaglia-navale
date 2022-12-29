#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "./../board/defenseboard.h"
#include "./../board/attackboard.h"

class Player {
public:
    virtual void turn() = 0;

    std::vector<std::string> history();

private:
    Defenseboard DefenseBoard;

    Attackboard AttackBoard;
};

#endif //PLAYER_H