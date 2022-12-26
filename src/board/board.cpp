#include "./../../include/board/board.h"

bool Board::is_valid(Coordinate &c){ 
    // TODO: CHECK IF FIXED, AT THIS TIME C.ROW IS CHAR, MUST BE INT
    return c.col() > 0 && c.col() < side_length && c.row() > 0 && c.row() < side_length;
}

bool Board::is_occupied(Coordinate &c){
    // TODO: IMPLEMENT
    return false;
}