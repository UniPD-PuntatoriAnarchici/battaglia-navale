//
// Created by Filippo Tiberio on 24/12/2022.
//
#include "./../../include/ship/ship.h"

bool Ship::is_alive() const {
    return armor_ != 0;
}

