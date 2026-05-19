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

void initializeMap(char map[][COLS]);
void displayMap(char map[][COLS], struct Player p, int exitX, int exitY);

int main() {
    
    Player p = {1, 1, 100};
    char map[ROWS][COLS];
    bool isRunning = true;
    char keyInput;
    int exitX = 8; int exitY = 8;

    initializeMap(map);

    while (isRunning) {
      displayMap(map, p, exitX, exitY);
      cout << "Enter a move (W/A/S/D): ";
      cin >> keyInput;

      // positioning of P
      switch (keyInput) {
      case 'W': case 'w':
        if (p.y > 0) {
          p.y--;
        }
        break;
      case 'S': case 's':
        if (p.y < ROWS - 1) {
          p.y++;
        }
        break;
      case 'A': case 'a':
        if (p.x > 0) {
          p.x--;
        }
        break;
      case 'D': case 'd':
        if (p.x < COLS - 1) {
          p.x++;
        }
        break;
      case 'Q': case 'q':
        cout << "You have exited the game.\n";
        isRunning = false;
        break;
      default:
        cout << "Notice: Press valid key (W/A/S/D/Q) | Q = Exit\n";
        break;
      }
    }
    

    return 0;
}

void initializeMap(char map[][COLS]) {
  for (int i = 0; i < ROWS; i++) { // !rows = Y axis
    for (int j = 0; j < COLS; j++) { // !columns = X axis 
      map[i][j] = '.';
    }
  }
}

void displayMap(char map[][COLS], struct Player p, int exitX, int exitY) {
  for (int i = 0; i < ROWS; i++) { // !rows = Y axis
    for (int j = 0; j < COLS; j++) { // !columns = X axis 
      
      if (i == p.y && j == p.x) {
        cout << "P";
      } else if (i == exitY && j == exitX) {
        cout << "X";
      }
      else {
        cout << map[i][j];
      }
      
    }
    cout << "\n";
  }
}