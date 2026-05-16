#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// global constants for the map dimensions
const int ROWS = 10;
const int COLS = 10;

// player data structure
struct Player {
  int x;
  int y;
  int health;
};


int main() {
    
    Player p = {1, 1, 100};

    char map[ROWS][COLS];

    cout << "Dungeon skeleton compiled successfully." << endl;

    return 0;
}