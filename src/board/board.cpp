/**
 * @author Tiberio Filippo
 */

#include "./../../include/board/board.h"

/**
 * is_valid [const]
 * verifies f a coordinate is valid.
 * @param c [Coordinate]
 * @return bool, true if valid
 */

bool Board::is_valid(Coordinate &c) const {
    return c.col() > 0 && c.col() <= side_length && c.row() > 0 && c.row() <= side_length;
}
