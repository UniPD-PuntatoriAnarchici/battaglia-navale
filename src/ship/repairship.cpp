/**
 * @author Rampin Matteo
 */

#include "./../../include/ship/repairship.h"

#include "./../../include/board/defenseboard.h"

std::ostream &operator<<(std::ostream &os, const Repairship &battleship) {
    std::vector<bool> cells = battleship.cells();

    os << "Repairship with center in " << battleship.center() << "and direction: " << battleship.direction() << ", has "
       << battleship.armor() << "/" << Repairship::LENGTH << " armor: [";

    for (bool cell: cells) {
        os << (cell ? Repairship::CHARACTER : (char) (Repairship::CHARACTER + 32));
    }

    os << "]";

    return os;
}

bool Repairship::action(Coordinate dest, Defenseboard &self_defense, Attackboard &self_attack, Defenseboard &opponent) {
    if (!this->is_alive()) return false;
    if (!dest.is_valid()) return false;
    if (self_defense.is_occupied(dest)) return false;
    
    if (this->direction_==Ship::Directions::HORIZONTAL){
        if (dest.col()+1>12||dest.col()-1<1) return false; 
    }else{
        if (dest.row()+1>12||dest.row()-1<1) return false;
    }
    

        std::vector<Coordinate> current_grid = self_defense.get_all_but_one_raw(this->center());
        Repairship tmp{dest, this->direction()};
        //tmp.set_armor(this->armor());
        
        for (auto position: tmp.raw_positions()) {
           
            if (!self_defense.is_valid(position)){
                return false;
            }
            if (std::find(current_grid.begin(), current_grid.end(), position) != current_grid.end()){
                return false;
            }
        }
        if (this->armor()!=3){
            
            int c=0;
            for (auto i = cells_.begin(); i != cells_.end(); i++)
            {
                tmp.cells_.at(c)=this->cells_.at(c);
                c++;
            }  
        }
        
        if (self_defense.remove_ship(*this)){
            self_defense.place_ship(tmp);
        }    
    

    if (direction() == Ship::Directions::HORIZONTAL) {
        int start_col = dest.col();
        if (start_col - 1 > 0) start_col--;
        int end_col = dest.col();
        if (end_col + 1 <= 12) end_col++;

        for (int i = start_col; i <= end_col; i++) {
            if (dest.row() - 1 > 0) {
                Coordinate to_check_1(dest.row() - 1, i);
                if (self_defense.is_occupied(to_check_1) && self_defense.is_alive(to_check_1)) {
                    self_defense.heal(to_check_1);
                }
            }
            if (dest.row() + 1 <= 12) {
                Coordinate to_check_2(dest.row() + 1, i);
                if (self_defense.is_occupied(to_check_2) && self_defense.is_alive(to_check_2)) {
                    self_defense.heal(to_check_2);
                }
            }
        }
    } else {
        int start_row = dest.row();
        if (start_row - 1 > 0) start_row--;
        int end_row = dest.col();
        if (end_row + 1 <= 12) end_row++;

        for (int i = start_row; i <= end_row ; i++) {
            if (dest.col() - 1 > 0) {
                Coordinate to_check_1(dest.row() - 1, i);
                if (self_defense.is_occupied(to_check_1) && self_defense.is_alive(to_check_1)) {
                    self_defense.heal(to_check_1);
                }
            }
            if (dest.col() + 1 <= 12) {
                Coordinate to_check_2(dest.row() + 1, i);
                if (self_defense.is_occupied(to_check_2) && self_defense.is_alive(to_check_2)) {
                    self_defense.heal(to_check_2);
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
