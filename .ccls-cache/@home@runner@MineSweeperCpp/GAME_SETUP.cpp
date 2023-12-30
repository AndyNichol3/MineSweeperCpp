#include "GAME_SETUP.h"
#include "PLAY_GAME.h"
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\e[0;36m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"

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

void fillWithMines(vector<vector<int>> &gameBoard, int userStartRow,
                   int userStartCol, int maxNumOfMines, int maxNumberOfRows,
                   int maxNumberOfColumns) {
  int numOfMines = 0;

  srand(time(NULL));
  bool check = true;

  int randX = -2, randY = -2;
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

void calcGameBoardInts(vector<vector<int>> &gameBoard, int x, int y,
                       int maxNumberOfRows, int maxNumberOfColumns) {
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

void fillWithInts(vector<vector<int>> &gameBoard, int maxNumberOfRows,
                  int maxNumberOfColumns) {
  for (int i = 0; i < maxNumberOfRows; i++) {
    for (int j = 0; j < maxNumberOfColumns; j++) {
      if (gameBoard[i][j] == -1) {
        // cout << "flag 2" << endl;
        calcGameBoardInts(gameBoard, i, j, maxNumberOfRows, maxNumberOfColumns);
      }
    }
  }
}

void initalizeGameBoard(vector<vector<bool>> &boolGameBoard,
                        vector<vector<int>> &gameBoard, int maxNumberOfRows,
                        int maxNumberOfColumns, int maxNumOfMines) {

  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);

  printRoundHeader(1);

  cout << "Enter Starting Point (-1 to exit): " << endl;
  int userStartCol = getInputX(maxNumberOfColumns);
  int userStartRow = getInputY(maxNumberOfRows);

  cout << endl;

  boolGameBoard[userStartRow][userStartCol] = true;

  fillWithMines(gameBoard, userStartRow, userStartCol, maxNumOfMines,
                maxNumberOfRows, maxNumberOfColumns);
  fillWithInts(gameBoard, maxNumberOfRows, maxNumberOfColumns);
  recursiveRevealExplosion(gameBoard, boolGameBoard, userStartRow, userStartCol,
                           maxNumberOfRows, maxNumberOfColumns);
  printBoolBoard(boolGameBoard, gameBoard, maxNumberOfRows, maxNumberOfColumns);
}