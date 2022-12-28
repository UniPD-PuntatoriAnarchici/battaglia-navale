#include <iostream>

#include "./../include/board/attackboard.h"

using namespace std;

void test_dev_matteo_galiazzo() {
    cout << "=== dev-matteo-galiazzo ===" << endl;

    Submarine s1{};
    cout << s1 << endl;

    Submarine s2{Coordinate{3,3}, Ship::Directions::VERTICAL};
    cout << s2 << endl;
    
    Attackboard ab;
}

void test_dev_filippo_tiberio() {
    cout << endl << "=== dev-filippo-tiberio ===" << endl;

    //region Coordinate
    Coordinate c1{};
    cout << c1;

    Coordinate c2{"B4"};
    cout << c2;

    try {
        Coordinate c3{"J4"};
        cout << c3;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
    }

    try {
        Coordinate c4{"Z4"};
        cout << c4;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
    }

    try {
        Coordinate c5{"4"};
        cout << c5;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
    }

    try {
        Coordinate c6{"B14"};
        cout << c6;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
    }

    Coordinate c7{"C7"};
    cout << c7;

    Coordinate c8{"N12"};
    cout << c8;

    //endregion

    cout << endl << "----------------" << endl;

    Battleship b1{};
    cout << b1 << endl;

    Battleship b2{Coordinate{3,3}, Ship::Directions::VERTICAL};
    cout << b2 << endl;


}

void test_dev_matteo_rampin() { cout << "=== dev-matteo-rampin ===" << endl; }

int main() {
    std::cout << "MAIN" << std::endl;
    test_dev_matteo_galiazzo();
    test_dev_filippo_tiberio();
    return 0;
}
