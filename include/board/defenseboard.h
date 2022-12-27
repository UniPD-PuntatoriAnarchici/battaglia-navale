//#ifndef DEFENSEBOARD_H
//#define DEFENSEBOARD_H
//
//#include "board.h"
//
//class Defenseboard : public Board {
//public:
//    bool is_lost();
//
//    std::vector<Coordinate> get_all() override {
//        return std::vector<Coordinate>(1);
//    }
//
//private:
//};
//
//#endif //DEFENSEBOARD_H

#ifndef DEFENSEBOARD_H
#define DEFENSEBOARD_H

#include <vector>

#include "board.h"

class Defenseboard : public Board {
public:
    Defenseboard();

    std::vector<Coordinate> get_all() override {
        return std::vector<Coordinate>(1);
    }

private:
};

#endif //DEFENSEBOARD_H