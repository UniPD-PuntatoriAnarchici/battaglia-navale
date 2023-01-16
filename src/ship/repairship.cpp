#include "./../../include/ship/repairship.h"

#include "./../../include/board/defenseboard.h"

std::ostream &operator<<(std::ostream &os, const Repairship &battleship) {
    std::vector<bool> cells = battleship.cells();

    os << "Repairship with center in " << battleship.center() << "and direction: " << battleship.direction() << ", has "
       << battleship.armor() << "/" << Repairship::LENGTH << " armor: [";

    for (bool cell : cells) {
        os << (cell ? Repairship::CHARACTER : (char)(Repairship::CHARACTER + 32));
    }

    os << "]";

    return os;
}
//need to try
bool Repairship::action(Coordinate dest, Defenseboard &opponent, Attackboard &self){
    //return true;
    if (!this->is_alive()) throw Ship::DEAD_SHIP{};
    if (!dest.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    if (this->center_ != dest){
        if (opponent.is_occupied(dest)) throw Coordinate::INVALID_COORDINATE{};
        if (this->direction_==Ship::Directions::HORIZONTAL){
            Coordinate col_plus=Coordinate(dest.row(),dest.col()+1);
            Coordinate col_minus=Coordinate(dest.row(),dest.col()-1);
            if(opponent.is_occupied(col_plus)||opponent.is_occupied(col_minus)) throw Coordinate::INVALID_COORDINATE{};
        }else{
            Coordinate row_plus=Coordinate(dest.row()+1,dest.col());
            Coordinate row_minus=Coordinate(dest.row()-1,dest.col());
            if(opponent.is_occupied(row_plus)||opponent.is_occupied(row_minus)) throw Coordinate::INVALID_COORDINATE{};
        }
        this->center_ = dest;
    }
    
    
    if (this->direction_==Ship::Directions::HORIZONTAL){
     
        for (int i = dest.col()-1; i <= dest.col()+1; i++){      
            if (dest.row()-1>0){
                Coordinate to_check_1(dest.row()-1,i);
                if (opponent.is_occupied(to_check_1) && opponent.is_alive(to_check_1)){
                    opponent.heal(to_check_1);
                }
            }
            if (dest.row()+1<=12){
                Coordinate to_check_2(dest.row()+1,i);
                if (opponent.is_occupied(to_check_2) && opponent.is_alive(to_check_2)){
                    opponent.heal(to_check_2);
                }              
            }
        } 
    }else{
        for (int i = dest.row()-1; i <= dest.row()+1; i++){      
            if (dest.col()-1>0){
                Coordinate to_check_1(dest.row()-1,i);
                if (opponent.is_occupied(to_check_1) && opponent.is_alive(to_check_1)){
                    opponent.heal(to_check_1);
                }
            }
            if (dest.col()+1<=12){
                Coordinate to_check_2(dest.row()+1,i);
                if (opponent.is_occupied(to_check_2) && opponent.is_alive(to_check_2)){
                    opponent.heal(to_check_2);
                }              
            }
        }
    }
    return true;      
}

//bool Repairship::action(Coordinate dest, Defenseboard &opponent, Attackboard &self) {
//    if (!this->is_alive()) throw Ship::DEAD_SHIP{};
//    if (!dest.is_valid()) throw Coordinate::INVALID_COORDINATE{};
//
//    return true;
//}

Repairship::~Repairship() {}

Repairship::Repairship(Coordinate center, Ship::Directions direction) {
    cells_ = std::vector<bool>(LENGTH);
    center_ = center;
    direction_ = direction;
    armor_ = LENGTH;
    type_ = Type::REPAIRSHIP;
    reset_cells();
}
