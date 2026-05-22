#include <iostream>
#include <cstdlib>
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

void initializeMap(char map[][COLS], Player &p, int &exitX, int &exitY);
void displayMap(char map[][COLS], struct Player p, int exitX, int exitY);

int main() {
    
    Player p = {1, 1, 100};
    char map[ROWS][COLS];
    bool isRunning = true;
    char keyInput;
    int exitX = 8; int exitY = 8;

    initializeMap(map, p, exitX, exitY);

    while (isRunning) {
      system("cls");
      displayMap(map, p, exitX, exitY);
      cout << "Enter a move (W/A/S/D): ";
      cin >> keyInput;

      // positioning of P
      switch (keyInput) {
      case 'W': case 'w':
        if (p.y > 0 && map[p.y - 1][p.x] != '#') {
          p.y--;
        }
        break;
      case 'S': case 's':
        if (p.y < ROWS - 1 && map[p.y + 1][p.x] != '#') {
          p.y++;
        }
        break;
      case 'A': case 'a':
        if (p.x > 0 && map[p.y][p.x - 1] != '#' ) {
          p.x--;
        }
        break;
      case 'D': case 'd':
        if (p.x < COLS - 1 && map[p.y][p.x + 1] != '#') {
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

      if (p.y == exitY && p.x == exitX) {
        cout << "You damn lucky! you escaped the dungeon!\n";
        isRunning = false; 
      }
    }

    return 0;
}

void initializeMap(char map[][COLS], Player &p, int &exitX, int &exitY) {
  for (int i = 0; i < ROWS; i++) { // !rows = Y axis
    for (int j = 0; j < COLS; j++) { // !columns = X axis 
      map[i][j] = '.';
    }
  }

  map[2][2] = 'P';
  map[4][5] = 'X';

  // ceiling and floor
  for (int j = 0; j < COLS; j++) {
    map[0][j] = '#';
    map[ROWS - 1][j] = '#';
  }

  // left and right walls
  for (int i = 0; i < ROWS; i++) {
    map[i][0] = '#';
    map[i][COLS - 1] = '#';
  }
 
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (map[i][j] == 'P') {
        p.y = i;
        p.x = j;
        map[i][j] = '.';
      }

      if (map[i][j] == 'X') {
        exitY = i;
        exitX = j;
      }
    }
  }
  
}

void displayMap(char map[][COLS], struct Player p, int exitX, int exitY) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      
      if (i == p.y && j == p.x) {
        cout << 'P';
      } else {
        cout << map[i][j];
      }
      
    }
    cout << "\n";
  }
}