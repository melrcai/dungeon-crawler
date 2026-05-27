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

void initializeMap(char map[][COLS], Player &p, int &exitX, int &exitY, int &totalTreasure);
void displayMap(char map[][COLS], struct Player p, int exitX, int exitY);

int main() { 
    
    Player p = {1, 1, 100};
    char map[ROWS][COLS];
    bool isRunning = true;
    char keyInput;
    int exitX = 0; int exitY = 0;
    int totalTreasure = 0;  

    initializeMap(map, p, exitX, exitY, totalTreasure);

    while (isRunning) {
      system("cls");
      displayMap(map, p, exitX, exitY);
      cout << "Health: " << p.health << "\n";
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
        cout << "Notice: Press valid key (W/A/S/D/Q) | Q = Abandon\n";
        break;
      }

      // coordinate of the player is the same as the coordinate of the treasure chest
      if (map[p.y][p.x] == '$') {
        p.health += 10;
        map[p.y][p.x] = '.'; // remove the treasure from the map
        totalTreasure--;
        cout << "Cha-ching! You lucky bastard! You found a treasure chest! +10 health\n";
        cout << "Health: " << p.health << "\n";

        cin.ignore(1000, '\n');
        cin.get(); 
      }

      // coordinate of the player is the same as the coordinate of the exit
      if (p.y == exitY && p.x == exitX) {
        if (totalTreasure == 0) {
            system("cls");
            displayMap(map, p, exitX, exitY);
            cout << "You damn lucky! You collected all the treasures and escaped the dungeon!\n";
            isRunning = false; 
        } else {
            cout << "The exit door is locked! You must collect the remaining " << totalTreasure << " coins first!\n";
            cout << "Press enter to continue...";
            cin.ignore(1000, '\n');
            cin.get(); 
        }
      }
      if (map[p.y][p.x] == 'T') {
        p.health -= 20;
        cout << "Ouch! You stepped on a trap! -20 health\n";
        cout << "Press enter to continue...";
        cin.ignore(1000, '\n');
        cin.get(); 

        if (p.health <= 0) {
          system("cls");
          displayMap(map, p, exitX, exitY);
          cout << "Uh oh! You have died you clumsy fool! Better luck next time!\n";
          isRunning = false;
        }
      }
    }
    return 0;
}

void initializeMap(char map[][COLS], Player &p, int &exitX, int &exitY, int &totalTreasure) {

  // to track the total no. of treasure chests in the map
  totalTreasure = 0;
  
  for (int i = 0; i < ROWS; i++) { // !rows = Y axis
    for (int j = 0; j < COLS; j++) { // !columns = X axis 
      map[i][j] = '.';
    }
  }

  // left and right walls
  for (int i = 0; i < ROWS; i++) {
    map[i][0] = '#';
    map[i][COLS - 1] = '#';
  }
  // ceiling and floor
  for (int j = 0; j < COLS; j++) {
    map[0][j] = '#';
    map[ROWS - 1][j] = '#';
  }
 
  map[2][2] = 'P';
  map[4][5] = 'X';

  // treasure chests
  map[3][4] = '$';
  map[6][2] = '$';
  map[7][8] = '$';

  // traps
  map[5][3] = 'T';
  map[4][4] = 'T';
  map[1][7] = 'T';

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // find the player position  
      if (map[i][j] == 'P') {
        p.y = i;
        p.x = j;
        map[i][j] = '.'; // need to clear the 'P' from the map 
      }

      if (map[i][j] == 'X') {
        exitY = i;
        exitX = j;
      }

      // count the total number of treasure chests in the map
      if (map[i][j] == '$') {
        totalTreasure++;
      } 

      if (map[i][j] == 'T') {
       p.y = i;
       p.x = j;
// !       map[i][j] = '.'; // remove the trap from the map after triggering it
     } 
    }
  }
  
}

void displayMap(char map[][COLS], struct Player p, int exitX, int exitY) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      
      if (i == p.y && j == p.x) {
        cout << 'P';
      } else if (map[i][j] == 'T') { // hide the trap from the player
        cout << '.';                 // ! else if (i == 'T' && j == 'T') { cout << '.'; } doesnt work  
      } else {                       // ? prolly because T is a char and not an int, so it cannot be compared with the coordinates of the player
        cout << map[i][j];
      }
      
    }
    cout << "\n";
  }
}