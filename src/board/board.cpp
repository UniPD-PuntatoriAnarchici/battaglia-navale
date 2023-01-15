#include "./../../include/board/board.h"

bool Board::is_valid(Coordinate &c){
    return c.col() > 0 && c.col() < side_length && c.row() > 0 && c.row() < side_length;
}
