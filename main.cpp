// minesweeper

// fix the boundaries for difficulty level
// comment and documentation
// fix variable naming
// remove redunancy
// split into many files studio.h


// headers
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

// custom color values
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\e[0;36m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"

using namespace std;

// functions
void printGameWelcome();

void fillWithMines(vector<vector<int>> &gameBoard, int userStartRow,
                   int userStartCol, int maxNumOfMines, int maxNumberOfRows,
                   int maxNumberOfColumns);

void fillWithInts(vector<vector<int>> &gameBoard, int maxNumberOfRows, int maxNumberOfColumns);
void calcGameBoardInts(vector<vector<int>> &gameBoard, int x, int y, int maxNumberOfRows,
                       int maxNumberOfColumns);
int printBoolBoard(const vector<vector<bool>> &boolGameBoard,
                   const vector<vector<int>> &gameBoard, int maxNumberOfRows,
                   int maxNumberOfColumns);
void zeroGameBoard(vector<vector<int>> &gameBoard,
                   vector<vector<bool>> &boolGameBoard, int maxNumberOfRows,
                   int maxNumberOfColumns);
void recursiveRevealExplosion(vector<vector<int>> &gameBoard,
                              vector<vector<bool>> &boolGameBoard, int X, int Y,
                              int maxNumberOfRows, int maxNumberOfColumns);
void printGameRules();
int getUserDifficulty();
int getInputX(int maxNumberOfColumns);
int getInputY(int maxNumberOfRows);
void printRoundHeader(int round);
void printWin();
void printLose();
void initalizeGameBoard(vector<vector<bool>> &boolGameBoard,
                        vector<vector<int>> &gameBoard, int maxNumberOfRows, int maxNumberOfColumns,
                        int maxNumOfMines);
bool playGame(int maxNumberOfColumns, int maxNumberOfRows, vector<vector<bool>> &boolGameBoard,
              vector<vector<int>> &gameBoard, int maxNumOfMines);

int main() {


  // define variable
  int maxNumberOfRows = 0, maxNumberOfColumns = 0, maxNumOfMines = 0, displaySubtract = 0;
  int round = 1;

  // print the game header,
  // also includes rule menu which keeps user until decides to start
  printGameWelcome();

  // get the user difficulty
  // 1 easy 2 meduim 3 hard
  int difficulty = getUserDifficulty();

  // define some constasnts based on the difficulty
  switch (difficulty) {
  case 1: {
    maxNumberOfRows = 9;
    maxNumberOfColumns = 9;
    maxNumOfMines = 10;
    break;
  }
  case 2: {
    maxNumberOfRows = 16;
    maxNumberOfColumns = 16;
    maxNumOfMines = 40;
    break;
  }
  case 3: {
    maxNumberOfRows = 16;
    maxNumberOfColumns = 30;
    maxNumOfMines = 99;
    break;
  }
  }

  // create the definition for some display variables
  displaySubtract = maxNumberOfRows - 1;

  // creates the game baords
  // one to hold the ints and one to hold the bools
  vector<vector<int>> gameBoard(maxNumberOfRows, vector<int>(maxNumberOfColumns));
  vector<vector<bool>> boolGameBoard(maxNumberOfRows, vector<bool>(maxNumberOfColumns));

  // handles all of the creation, and the round 1 of them game
  // since the game cannot be lost on round one and the variables
  // are not reused anywhere else
  initalizeGameBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns, maxNumOfMines);

  bool win = playGame(maxNumberOfColumns, maxNumberOfRows, boolGameBoard, gameBoard, maxNumOfMines);

  if (win == true) {
    printWin();

  } else {
    printLose();
  }
}

int printBoolBoard(const vector<vector<bool>> &boolGameBoard,
                   const vector<vector<int>> &gameBoard, int maxNumberOfRows,
                   int maxNumberOfColumns) {
  int revealTally = 0;

  cout << endl;
  cout << RED << "   +----------------------------+" << endl;

  for (int i = 0; i < maxNumberOfRows; ++i) {
    cout << RED << setw(2) << maxNumberOfRows - 1 - i << " |";
    for (int j = 0; j < maxNumberOfColumns; ++j) {
      if (boolGameBoard[i][j]) {
        revealTally++;
        switch (gameBoard[i][j]) {
        case 0:
          cout << WHITE << setw(3) << gameBoard[i][j];
          break;
        case 1:
          cout << BLUE << setw(3) << gameBoard[i][j];
          break;
        case 2:
          cout << GREEN << setw(3) << gameBoard[i][j];
          break;
        case 3:
          cout << RED << setw(3) << gameBoard[i][j];
          break;
        default:
          cout << RED << setw(3) << gameBoard[i][j];
          break;
        }
      } else {
        cout << WHITE << setw(3) << "-";
      }
    }
    cout << RED << " |" << endl;
  }

  cout << RED << "   +----------------------------+" << RESET << endl;
  cout << RED << "    ";
  for (int i = 0; i < maxNumberOfColumns; ++i) {
    cout << RED << setw(3) << i;
  }
  cout << endl;

  return revealTally;
}



void fillWithMines(vector<vector<int>> &gameBoard, int userStartRow,
                   int userStartCol, int maxNumOfMines, int maxNumberOfRows,
                   int maxNumberOfColumns) {
  int numOfMines = 0;

  srand(time(NULL));
  int randX = -1, randY = -1;

  while (numOfMines <= maxNumOfMines) {
    bool check = true;
    randX = rand() % (maxNumberOfRows - 1);
    randY = rand() % (maxNumberOfColumns - 1);

    int defIndexX[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int defIndexY[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    for (int i = 0; i < 9; i++) {
      int updateRow = userStartRow + defIndexX[i];
      int updateCol = userStartCol + defIndexY[i];

      if (gameBoard[randX][randY] != 0 ||
          (randX == updateRow && randY == updateCol)) {

        check = false;
        break;
      }
    }
    if (check == true) {
      gameBoard[randX][randY] = -1;
      numOfMines++;

      // randX = maxNumberOfRows - 1 - randX;
      // cout << randY << " " << randX << endl;

      if (numOfMines == maxNumOfMines) {
        break;
      }
    }
  }
}

void zeroGameBoard(vector<vector<int>> &gameBoard,
                   vector<vector<bool>> &boolGameBoard, int maxNumberOfRows,
                   int maxNumberOfColumns) {

  for (int i = 0; i < maxNumberOfRows; i++) {
    for (int j = 0; j < maxNumberOfColumns; j++) {
      gameBoard[i][j] = 0;
      boolGameBoard[i][j] = false;
    }
  }
}

void calcGameBoardInts(vector<vector<int>> &gameBoard, int x, int y, int maxNumberOfRows,
                       int maxNumberOfColumns) {
  int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < 8; i++) {
    int updateRow = x + defIndexX[i];
    int updateCol = y + defIndexY[i];

    if (updateRow >= 0 && updateRow < maxNumberOfRows && updateCol >= 0 &&
        updateCol < maxNumberOfColumns) {
      if (gameBoard[updateRow][updateCol] != -1) {
        gameBoard[updateRow][updateCol]++;
      }
    }
  }
}

void fillWithInts(vector<vector<int>> &gameBoard, int maxNumberOfRows, int maxNumberOfColumns) {
  for (int i = 0; i < maxNumberOfRows; i++) {
    for (int j = 0; j < maxNumberOfColumns; j++) {
      if (gameBoard[i][j] == -1) {
        // cout << "flag 2" << endl;
        calcGameBoardInts(gameBoard, i, j, maxNumberOfRows, maxNumberOfColumns);
      }
    }
  }
}

void recursiveRevealExplosion(vector<vector<int>> &gameBoard,
                              vector<vector<bool>> &boolGameBoard, int X, int Y,
                              int maxNumberOfRows, int maxNumberOfColumns) {
  int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < 8; i++) {

    int updateRow = X + defIndexX[i];
    int updateCol = Y + defIndexY[i];

    if (updateRow >= 0 && updateRow < maxNumberOfRows && updateCol >= 0 &&
        updateCol < maxNumberOfColumns && !boolGameBoard[updateRow][updateCol]) {
      boolGameBoard[updateRow][updateCol] = true;
      if (gameBoard[updateRow][updateCol] == 0) {
        recursiveRevealExplosion(gameBoard, boolGameBoard, updateRow, updateCol,
                                 maxNumberOfRows, maxNumberOfColumns);
      }
    }
  }
}

void printGameWelcome() {
  cout << RED << "\n\n-------------------------------------" << endl;
  cout << WHITE << "       Welcome to Minesweeper!       " << endl;
  cout << RED << "-------------------------------------\n" << RESET << endl;
  bool startGame = false;
  while (startGame == false) {

    cout << "Press 1 For Rules or 2 To Start: " << endl;
    int userStartGame = 0;
    cin >> userStartGame;
    if (userStartGame == 1) {
      // add actual rules later
      cout << "Here are the Rules " << endl;
      printGameRules();
    } else if (userStartGame == 2) {

      cout << "Here we go! \n" << endl;
      // cout << "-------------------------------------\n" << endl;
      startGame = true;
      break;
    } else {
      //  cout << "invalid input" << endl;
      // cout << "\nInvalid input. Please try again.\n" << endl;
      cin.clear(); // Clear error flags
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

void printGameRules() {
  cout << endl << "eventuall, we'll add rules later\n" << endl;
}

int getUserDifficulty() {
  int difficulty = 0;
  while (difficulty != 1 && difficulty != 2 && difficulty != 3) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    cout << "Chose Your Difficulty: " << endl;
    cout << "1. Easy    2. Medium    3. Hard" << endl;
    cin >> difficulty;
  }
  return difficulty;
}

int getInputX(int maxNumberOfColumns) {
  bool validInput = false;
  int userIn = -2;

  while (!validInput) {

    cout << "X (0-" << maxNumberOfColumns - 1 << "): ";
    if (!(cin >> userIn)) {
      cout << "Invalid input. Please enter a number." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else if (userIn >= maxNumberOfColumns || userIn < -1) {
      cout << "Input out of range. Please enter a number in range 0-"
           << maxNumberOfColumns - 1 << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      if (userIn == -1) {
        exit(0);
      }
      validInput = true;
    }
  }
  return userIn;
}

int getInputY(int maxNumberOfRows) {
  bool validInput = false;
  int userIn = -2;

  while (!validInput) {
    cout << "Y (0-" << maxNumberOfRows - 1 << "): ";
    if (!(cin >> userIn)) {
      cout << "Invalid input. Please enter a number." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else if (userIn >= maxNumberOfRows || userIn < 0) {
      cout << "Input out of range. Please enter a number in range 0-"
           << maxNumberOfRows - 1 << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      validInput = true;
    }
  }

  userIn = maxNumberOfRows - 1 - userIn;
  return userIn;
}

void printRoundHeader(int round) {

  cout << WHITE << "_____________________________________\n" << endl;
  cout << RED << "                ROUND " << round << endl;
  cout << WHITE << "_____________________________________\n" << RESET << endl;
}
void printWin() {
  cout << WHITE << "\n_____________________________________\n" << endl;
  cout << RED << "               YOU WIN!" << endl;
  cout << WHITE << "_____________________________________\n" << RESET << endl;
}
void printLose() {
  cout << WHITE << "\n_____________________________________\n" << endl;
  cout << RED << "               YOU LOSE!" << endl;
  cout << WHITE << "_____________________________________\n" << RESET << endl;
}

void initalizeGameBoard(vector<vector<bool>> &boolGameBoard,
                        vector<vector<int>> &gameBoard, int maxNumberOfRows, int maxNumberOfColumns,
                        int maxNumOfMines) {

  zeroGameBoard(gameBoard, boolGameBoard, maxNumberOfRows, maxNumberOfColumns);
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);

  printRoundHeader(1);

  cout << "Enter Starting Point (-1 to exit): " << endl;
  int userStartCol = getInputX(maxNumberOfColumns);
  int userStartRow = getInputY(maxNumberOfRows);

  cout << endl;

  boolGameBoard[userStartRow][userStartCol] = true;

  fillWithMines(gameBoard, userStartRow, userStartCol, maxNumOfMines, maxNumberOfRows,
                maxNumberOfColumns);
  fillWithInts(gameBoard, maxNumberOfRows, maxNumberOfColumns);
  recursiveRevealExplosion(gameBoard, boolGameBoard, userStartRow, userStartCol,
                           maxNumberOfRows, maxNumberOfColumns);
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);
}

bool playGame(int maxNumberOfColumns, int maxNumberOfRows, vector<vector<bool>> &boolGameBoard,
              vector<vector<int>> &gameBoard, int maxNumOfMines) {

  bool gameOver = false, win = false;
  int round = 1, revealTally = 0;
  int maxDisplay = maxNumberOfRows * maxNumberOfColumns;
  while (gameOver == false) {

    round++;

    printRoundHeader(round);

    bool revealedTile = false;
    int userRow = -2, userCol = -2;

    while (!revealedTile) {

      cout << "Enter Next Point (-1 to exit): " << endl;
      userCol = getInputX(maxNumberOfColumns);
      userRow = getInputY(maxNumberOfRows);

      if (boolGameBoard[userRow][userCol] == true) {
        cout << "You have already revealed this tile!\n" << endl;
      } else {
        revealedTile = true;
        break;
      }
    }

    if (gameBoard[userRow][userCol] == -1) {
      gameOver = true;
      cout << "you hit a mine!" << endl;
      boolGameBoard[userRow][userCol] = true;

    } else {
      boolGameBoard[userRow][userCol] = true;
      if (gameBoard[userRow][userCol] == 0) {
        recursiveRevealExplosion(gameBoard, boolGameBoard, userRow, userCol,
                                 maxNumberOfRows, maxNumberOfColumns);
      }
    }

    revealTally = printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);

    if (revealTally == (maxDisplay - maxNumOfMines)) {
      gameOver = true;
      win = true;
    }
  }

  return win;
}