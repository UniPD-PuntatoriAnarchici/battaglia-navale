//
// Created by Filippo Tiberio on 24/12/2022.
//
#include "./../../include/ship/ship.h"

int Ship::get_life() const {
    int counter = 0;
    for (bool cell : cells_) {
        if (cell) counter++;
    }

    return counter;
}