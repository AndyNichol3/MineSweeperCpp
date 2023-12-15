// minesweeper

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\e[0;36m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"

using namespace std;

void printRules();
int initalizeGameBoard(vector<vector<int>> &gameBoard,
                       vector<vector<bool>> &boolGameBoard, int revealTally);
void fillWithMines(vector<vector<int>> &gameBoard, int userStartRow,
                   int userStartCol);
void printGameBoardTesting(const vector<vector<int>> &gameBoard,
                           const vector<vector<bool>> &boolGameBoard);
void fillWithInts(vector<vector<int>> &gameBoard);
void calcGameBoardInts(vector<vector<int>> &gameBoard, int x, int y);
void printBoolBoard(const vector<vector<bool>> &boolGameBoard,
                    const vector<vector<int>> &gameBoard);
void zeroGameBoard(vector<vector<int>> &gameBoard,
                   vector<vector<bool>> &boolGameBoard);
void recursiveRevealExplosion(vector<vector<int>> &gameBoard,
                              vector<vector<bool>> &boolGameBoard, int X,
                              int Y);
void printGameRules();

int main() {

  printRules();

  cout << endl;
  cout << "Chose Your Difficulty: " << endl;
  cout << "1. Easy    2. Medium    3. Hard" << endl;
  int difficulty = 0;
  cin >> difficulty;

  int kRows = 9, kCollums = 9;

  switch (difficulty) {
  case 1: {
    kRows = 9;
    kCollums = 9;

    break;
  }
  case 2: {
    kRows = 9;
    kCollums = 9;
    break;
  }
  case 3: {
    kRows = 9;
    kCollums = 9;
    break;
  }
  }

  bool gameOver = false;
  bool win = false;

  vector<vector<int>> gameBoard(kRows, vector<int>(kCollums));
  vector<vector<bool>> boolGameBoard(kRows, vector<bool>(kCollums));

  // int gameBoard[9][9];
  // bool boolGameBoard[9][9];
  int revealTally = 0;
  int round = 1;

  revealTally = initalizeGameBoard(gameBoard, boolGameBoard, revealTally);
  printBoolBoard(boolGameBoard, gameBoard);
  cout << endl;

  // printGameBoardTesting(gameBoard, boolGameBoard);
  // cout << endl << revealTally << endl;

  while (gameOver == false) {

    round++;

    cout << WHITE << "_____________________________________\n" << endl;
    cout << RED << "                ROUND " << round << endl;
    cout << WHITE << "_____________________________________\n" << RESET << endl;

    int userRow = 0, userCol = 0;
    cout << "Enter Next Point (-1 to exit): " << endl;
    cout << "X (0-8): ";
    cin >> userCol;
    if (userCol == -1) {
      exit(0);
    }
    cout << "Y (0-8): ";
    cin >> userRow;
    userRow = 8 - userRow;

    // add condition to make sure within bounds

    if (gameBoard[userRow][userCol] == -1) {
      gameOver = true;
      cout << "you hit a mine!" << endl;
      boolGameBoard[userRow][userCol] = true;

    } else {
      boolGameBoard[userRow][userCol] = true;
      if (gameBoard[userRow][userCol] == 0) {
        recursiveRevealExplosion(gameBoard, boolGameBoard, userRow, userCol);
      }
      revealTally++;
    }

    if (revealTally == 81) {
      gameOver = true;
      win = true;
    }

    printBoolBoard(boolGameBoard, gameBoard);
  }

  if (win == true) {
    cout << "you win!" << endl;
  } else {
    cout << "you lose!" << endl;
  }
}

void printBoolBoard(const vector<vector<bool>> &boolGameBoard,
                    const vector<vector<int>> &gameBoard) {
  // Print column labels

  // Print separator bar
  cout << endl;
  std::cout << RED << "   +----------------------------+" << std::endl;

  // Print rows with labels and game board contents

  for (int i = 0; i < 9; ++i) {
    std::cout << RED << std::setw(2) << 8 - i << " |"; // Row number
    for (int j = 0; j < 9; ++j) {
      if (boolGameBoard[i][j]) {
        switch (gameBoard[i][j]) {
          // std::cout << WHITE<< std::setw(3) << gameBoard[i][j];
        case 0:
          std::cout << WHITE << std::setw(3) << gameBoard[i][j];
          break;
        case 1:
          std::cout << BLUE << std::setw(3) << gameBoard[i][j];
          break;
        case 2:
          std::cout << GREEN << std::setw(3) << gameBoard[i][j];
          break;
        case 3:
          std::cout << RED << std::setw(3) << gameBoard[i][j];
          break;
        default:
          std::cout << RED << std::setw(3) << gameBoard[i][j];
          break;
        }
      } else {
        std::cout << WHITE << std::setw(3) << "-"; // Unrevealed cell
      }
    }
    std::cout << RED << " |" << std::endl;
  }

  // Print separator bar

  std::cout << RED << "   +----------------------------+" << RESET << std::endl;
  std::cout << RED << "    ";
  for (int i = 0; i < 9; ++i) {
    std::cout << RED << std::setw(3) << i; // Column numbers
  }
  std::cout << std::endl;
}

void printRules() {
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
      std::cout << "\nInvalid input. Please try again.\n" << std::endl;
      std::cin.clear(); // Clear error flags
      std::cin.ignore();
    }
  }
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
                   int userStartCol) {
  int numOfMines = 0;
  int maxNumOfMines = 10;
  srand(time(NULL));
  int randX = -1, randY = -1;

  while (numOfMines <= maxNumOfMines) {
    bool check = true;
    randX = rand() % 9;
    randY = rand() % 9;

    int defIndexX[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int defIndexY[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    for (int i = 0; i < 9; i++) {
      int updateRow = userStartRow + defIndexX[i];
      int updateCol = userStartCol + defIndexY[i];

      if (gameBoard[randX][randY] != 0 ||
          (randX == updateRow && randY == updateCol)) {
        // cout << "flag 1" << endl;
        check = false;
        break;
      }
    }
    if (check == true) {
      gameBoard[randX][randY] = -1;
      numOfMines++;
      if (numOfMines == maxNumOfMines) {
        break;
      }
    }
  }
}
void zeroGameBoard(vector<vector<int>> &gameBoard,
                   vector<vector<bool>> &boolGameBoard) {
  // fill baord with 0
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      gameBoard[i][j] = 0;
      boolGameBoard[i][j] = false;
    }
  }
}
void calcGameBoardInts(vector<vector<int>> &gameBoard, int x, int y) {
  int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < 8; i++) {
    int updateRow = x + defIndexX[i];
    int updateCol = y + defIndexY[i];

    if (updateRow >= 0 && updateRow < 9 && updateCol >= 0 && updateCol < 9) {
      if (gameBoard[updateRow][updateCol] != -1) {
        // cout << "flag 3" << endl;
        gameBoard[updateRow][updateCol]++;
      }
    }
  }
}

void fillWithInts(vector<vector<int>> &gameBoard) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (gameBoard[i][j] == -1) {
        // cout << "flag 2" << endl;
        calcGameBoardInts(gameBoard, i, j);
      }
    }
  }
}
int initalizeGameBoard(vector<vector<int>> &gameBoard,
                       vector<vector<bool>> &boolGameBoard, int revealTally) {

  // get coords
  zeroGameBoard(gameBoard, boolGameBoard);
  printBoolBoard(boolGameBoard, gameBoard);

  cout << WHITE << "_____________________________________\n" << endl;
  cout << RED << "                ROUND 1" << endl;
  cout << WHITE << "_____________________________________\n" << RESET << endl;

  cout << "\nEnter Starting Point: ";
  int userStartRow = -1;
  int userStartCol = -1;
  cout << "\nX (0-8): ";
  cin >> userStartCol;
  cout << "Y (0-8): ";
  cin >> userStartRow;
  userStartRow = 8 - userStartRow;
  cout << endl;

  // initalize game board
  // cout << "zeroing game board" << endl;

  // gameBoard[userStartRow][userStartCol] = -2;
  boolGameBoard[userStartRow][userStartCol] = true;

  // fill game board with mines
  // cout << "filling game board with mines" << endl;
  fillWithMines(gameBoard, userStartRow, userStartCol);

  // cout << "calculating baord" << endl;
  fillWithInts(gameBoard);

  recursiveRevealExplosion(gameBoard, boolGameBoard, userStartRow,
                           userStartCol);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (boolGameBoard[i][j]) {
        revealTally++;
      }
    }
  }

  return revealTally;
}

void recursiveRevealExplosion(vector<vector<int>> &gameBoard,
                              vector<vector<bool>> &boolGameBoard, int X,
                              int Y) {
  int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < 8; i++) {

    int updateRow = X + defIndexX[i];
    int updateCol = Y + defIndexY[i];

    if (updateRow >= 0 && updateRow < 9 && updateCol >= 0 && updateCol < 9 &&
        !boolGameBoard[updateRow][updateCol]) {
      boolGameBoard[updateRow][updateCol] = true;
      if (gameBoard[updateRow][updateCol] == 0) {
        recursiveRevealExplosion(gameBoard, boolGameBoard, updateRow,
                                 updateCol);
      }
    }
  }
}

void printGameRules() {
  cout << endl << "eventuall, we'll add rules later\n" << endl;
}