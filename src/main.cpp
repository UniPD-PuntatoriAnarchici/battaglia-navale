#include <iostream>
#include <queue>

#include "./../include/board/attackboard.h"

#ifdef __linux__

#elif __APPLE__

#else

#include <windows.h>

#endif

using namespace std;

void test_dev_matteo_galiazzo() {
    cout << "=== dev-matteo-galiazzo ===" << endl;

    Submarine s1{};
    cout << s1 << endl;

    Submarine s2{Coordinate{3, 3}, Ship::Directions::VERTICAL};
    cout << s2 << endl;

    Attackboard ab;
}

void test_dev_filippo_tiberio() {
#ifdef __linux__

#elif __APPLE__

#else
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    cout << endl
         << "=== dev-filippo-tiberio ===" << endl;

    // region Coordinate
    Coordinate c1{};
    cout << c1;

    Coordinate c2{"B4"};
    cout << c2;

    //    try {
    //        Coordinate c3{"J4"};
    //        cout << c3;
    //    } catch (const std::exception &e) {
    //        cerr << e.what() << endl;
    //    }
    //
    //    try {
    //        Coordinate c4{"Z4"};
    //        cout << c4;
    //    } catch (const std::exception &e) {
    //        cerr << e.what() << endl;
    //    }
    //
    //    try {
    //        Coordinate c5{"4"};
    //        cout << c5;
    //    } catch (const std::exception &e) {
    //        cerr << e.what() << endl;
    //    }
    //
    //    try {
    //        Coordinate c6{"B14"};
    //        cout << c6;
    //    } catch (const std::exception &e) {
    //        cerr << e.what() << endl;
    //    }

    Coordinate c7{"C7"};
    cout << c7;

    Coordinate c8{"N12"};
    cout << c8;

    // endregion

    cout << endl
         << "----------------" << endl;

    Battleship b1{};
    cout << b1 << endl;
    cout << "Battleship b1 positions: ";
    try {
        std::vector<Coordinate> positions1 = b1.positions();
        for (auto p : positions1) {
            cout << p << " ";
        }
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }
    cout << endl;

    Battleship b2{Coordinate{3, 3}, Ship::Directions::VERTICAL};
    cout << b2 << endl;

    cout << "Battleship b2 positions: ";
    std::vector<Coordinate> positions2 = b2.positions();
    for (auto p : positions2) {
        cout << p << " ";
    }
    cout << endl;

    Battleship b3{Coordinate{9, 4}, Ship::Directions::HORIZONTAL};
    cout << b3 << endl;

    cout << "Battleship b3 positions: ";
    std::vector<Coordinate> positions3 = b3.positions();
    for (auto p : positions3) {
        cout << p << " ";
    }
    cout << endl;

    struct minpQElements {
        Coordinate c;
        char toPrint{' '};
        bool isCenter{false};

        explicit minpQElements(const Coordinate &c, char toPrint = ' ',
                               bool isCenter = true)
            : c(c), toPrint(toPrint), isCenter(isCenter) {}
    };

    auto lambda = [](minpQElements a, minpQElements b) { return !(a.c < b.c); };
    std::priority_queue<minpQElements, std::vector<minpQElements>,
                        decltype(lambda)>
        pQ(lambda);

    for (auto p : positions2) {
        if (p == b2.center()) {
            pQ.push(minpQElements{p, 'a', true});
        } else {
            pQ.push(minpQElements{p, 'a', false});
        }
    }

    for (auto p : positions3) {
        if (p == b3.center()) {
            pQ.push(minpQElements{p, 'a', true});
        } else {
            pQ.push(minpQElements{p, 'a', false});
        }
    }

    minpQElements el = pQ.top();
    for (int i = 1; i <= 12; i++) {
        cout << (char)(i < 10 ? '@' + i : '@' + i + 2) << " |";
        for (int j = 1; j <= 12; j++) {
            if (el.c.equals(i, j)) {
                if (el.isCenter) {
#if defined(__linux__) || defined(__APPLE__)
                    cout << " \033[1;34m" << el.toPrint << "\033[0m |";
#else
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << " " << el.toPrint;
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << " |";
#endif

                } else {
                    cout << " " << el.toPrint << " |";
                }

                pQ.pop();
                el = pQ.top();
            } else {
                cout << "   |";
            }
        }
        cout << endl;
    }
    cout << "-> ";
    for (int j = 1; j <= 12; j++) {
        if (j < 10) {
            cout << "  " << j << " ";
        } else {
            cout << " " << j << " ";
        }
    }
    cout << endl;
}

void test_dev_matteo_rampin() { cout << "=== dev-matteo-rampin ===" << endl; }

int main() {
    std::cout << "MAIN" << std::endl;
    test_dev_matteo_galiazzo();
    test_dev_filippo_tiberio();
    return 0;
}
