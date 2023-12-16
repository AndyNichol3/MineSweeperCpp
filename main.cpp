// minesweeper

// fix row, collum issue

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
                   int userStartCol, int maxNumOfMines, int kRows,
                   int kCollums);
void printGameBoardTesting(const vector<vector<int>> &gameBoard,
                           const vector<vector<bool>> &boolGameBoard);
void fillWithInts(vector<vector<int>> &gameBoard, int kRows, int kCollums);
void calcGameBoardInts(vector<vector<int>> &gameBoard, int x, int y, int kRows,
                       int kCollums);
int printBoolBoard(const vector<vector<bool>> &boolGameBoard,
                   const vector<vector<int>> &gameBoard, int kRows,
                   int kCollums);
void zeroGameBoard(vector<vector<int>> &gameBoard,
                   vector<vector<bool>> &boolGameBoard, int kRows,
                   int kCollums);
void recursiveRevealExplosion(vector<vector<int>> &gameBoard,
                              vector<vector<bool>> &boolGameBoard, int X, int Y,
                              int kRows, int kCollums);
void printGameRules();
int getUserDifficulty();
int getInputX(int kCollums);
int getInputY(int kRows);
void printRoundHeader(int round); 
void printWin(); 
void printLose();

int main() {

  // define variable
  int kRows = 0, kCollums = 0, maxNumOfMines = 0, displaySubtract = 0;
  int revealTally = 0, round = 1;
  bool gameOver = false, win = false;

  printGameWelcome();

  int difficulty = getUserDifficulty();

  switch (difficulty) {
  case 1: {
    kRows = 9;
    kCollums = 9;
    maxNumOfMines = 10;
    break;
  }
  case 2: {
    kRows = 16;
    kCollums = 16;
    maxNumOfMines = 40;
    break;
  }
  case 3: {
    kRows = 16;
    kCollums = 30;
    maxNumOfMines = 99;
    break;
  }
  }

  displaySubtract = kRows - 1;
  int maxDisplay = kRows * kCollums;

  vector<vector<int>> gameBoard(kRows, vector<int>(kCollums));
  vector<vector<bool>> boolGameBoard(kRows, vector<bool>(kCollums));

  zeroGameBoard(gameBoard, boolGameBoard, kRows, kCollums);
  printBoolBoard(boolGameBoard, gameBoard, kRows, kCollums);

  printRoundHeader(round);

  cout << "Enter Starting Point (-1 to exit): " << endl;
  int userStartCol = getInputX(kCollums);
  int userStartRow = getInputY(kRows);

  cout << endl;

  boolGameBoard[userStartRow][userStartCol] = true;

  fillWithMines(gameBoard, userStartRow, userStartCol, maxNumOfMines, kRows, kCollums);
  fillWithInts(gameBoard, kRows, kCollums);
  recursiveRevealExplosion(gameBoard, boolGameBoard, userStartRow, userStartCol, kRows, kCollums);
  printBoolBoard(boolGameBoard, gameBoard, kRows, kCollums);

  
  while (gameOver == false) {

    round++;

    printRoundHeader(round);

    bool revealedTile = false;
    int userRow = -2, userCol = -2;


    while (!revealedTile) {
      
      cout << "Enter Next Point (-1 to exit): " << endl;
      userCol = getInputX(kCollums);
      userRow = getInputY(kRows);


      if (boolGameBoard[userRow][userCol] == true) {
        cout << "You have already revealed this tile!\n" << endl;
      } 
      else {
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
                                 kRows, kCollums);
      }
    }

    revealTally = printBoolBoard(boolGameBoard, gameBoard, kRows, kCollums);

    if (revealTally == (maxDisplay - maxNumOfMines)) {
      gameOver = true;
      win = true;
    }
  }

  if (win == true){
    printWin();

  } 
  else {
    printLose(); 
  }
}

int printBoolBoard(const vector<vector<bool>> &boolGameBoard,
                   const vector<vector<int>> &gameBoard, int kRows,
                   int kCollums) {
  int revealTally = 0;

  cout << endl;
  cout << RED << "   +----------------------------+" << endl;

  for (int i = 0; i < kRows; ++i) {
    cout << RED << setw(2) << kRows - 1 - i << " |";
    for (int j = 0; j < kCollums; ++j) {
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
  for (int i = 0; i < kCollums; ++i) {
    cout << RED << setw(3) << i;
  }
  cout << endl;

  return revealTally;
}

void printGameBoardTesting(const vector<vector<int>> &gameBoard,
                           const vector<vector<bool>> &boolGameBoard) {

  cout << right;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << setw(3) << gameBoard[i][j];
    }
    cout << endl;
  }
}

void fillWithMines(vector<vector<int>> &gameBoard, int userStartRow,
                   int userStartCol, int maxNumOfMines, int kRows,
                   int kCollums) {
  int numOfMines = 0;

  srand(time(NULL));
  int randX = -1, randY = -1;

  while (numOfMines <= maxNumOfMines) {
    bool check = true;
    randX = rand() % (kRows - 1);
    randY = rand() % (kCollums - 1);

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

      // randX = kRows - 1 - randX;
      // cout << randY << " " << randX << endl;

      if (numOfMines == maxNumOfMines) {
        break;
      }
    }
  }
}

void zeroGameBoard(vector<vector<int>> &gameBoard,
                   vector<vector<bool>> &boolGameBoard, int kRows,
                   int kCollums) {

  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kCollums; j++) {
      gameBoard[i][j] = 0;
      boolGameBoard[i][j] = false;
    }
  }
}

void calcGameBoardInts(vector<vector<int>> &gameBoard, int x, int y, int kRows,
                       int kCollums) {
  int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < 8; i++) {
    int updateRow = x + defIndexX[i];
    int updateCol = y + defIndexY[i];

    if (updateRow >= 0 && updateRow < kRows && updateCol >= 0 &&
        updateCol < kCollums) {
      if (gameBoard[updateRow][updateCol] != -1) {
        gameBoard[updateRow][updateCol]++;
      }
    }
  }
}

void fillWithInts(vector<vector<int>> &gameBoard, int kRows, int kCollums) {
  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kCollums; j++) {
      if (gameBoard[i][j] == -1) {
        // cout << "flag 2" << endl;
        calcGameBoardInts(gameBoard, i, j, kRows, kCollums);
      }
    }
  }
}

void recursiveRevealExplosion(vector<vector<int>> &gameBoard,
                              vector<vector<bool>> &boolGameBoard, int X, int Y,
                              int kRows, int kCollums) {
  int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < 8; i++) {

    int updateRow = X + defIndexX[i];
    int updateCol = Y + defIndexY[i];

    if (updateRow >= 0 && updateRow < kRows && updateCol >= 0 &&
        updateCol < kCollums && !boolGameBoard[updateRow][updateCol]) {
      boolGameBoard[updateRow][updateCol] = true;
      if (gameBoard[updateRow][updateCol] == 0) {
        recursiveRevealExplosion(gameBoard, boolGameBoard, updateRow, updateCol,
                                 kRows, kCollums);
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

int getInputX(int kCollums) {
  bool validInput = false;
  int userIn = -2;

  while (!validInput) {

    cout << "X (0-" << kCollums - 1 << "): ";
    if (!(cin >> userIn)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else if (userIn >= kCollums || userIn < -1) {
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

int getInputY(int kRows) {
  bool validInput = false;
  int userIn = -2;

  while (!validInput) {
    cout << "Y (0-" << kRows - 1 << "): ";
    if (!(cin >> userIn)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else if (userIn >= kRows || userIn < 0) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      validInput = true;
    }
  }

  userIn = kRows - 1 - userIn;
  return userIn;
}

void printRoundHeader(int round){

  cout << WHITE << "_____________________________________\n" << endl;
  cout << RED << "                ROUND " << round <<endl;
  cout << WHITE << "_____________________________________\n" << RESET << endl;

}
  void printWin(){
    cout << WHITE << "\n_____________________________________\n" << endl;
    cout << RED << "               YOU WIN!" << endl;
    cout << WHITE << "_____________________________________\n" << RESET << endl;
  }
  void printLose(){
    cout << WHITE << "\n_____________________________________\n" << endl;
    cout << RED << "               YOU LOSE!" << endl;
    cout << WHITE << "_____________________________________\n" << RESET << endl;

  }