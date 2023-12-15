// minesweeper

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;

void printRules();
int initalizeGameBoard(int gameBoard[9][9], bool boolGameBoard[9][9],
                       int revealTally);
void fillWithMines(int gameBoard[9][9], int userStartX, int userStartY);
void printGameBoardTesting(int gameBoard[9][9], bool boolGameBoard[9][9]);
void fillWithInts(int gameBoard[9][9]);
void calcGameBoardInts(int gameBoard[9][9], int x, int y);
void printBoolBoard(bool boolGameBoard[9][9], int gameBoard[9][9]);
void zeroGameBoard(int gameBoard[9][9], bool boolGameBoard[9][9]);
void recursiveRevealExplosion(int gameBoard[9][9], bool boolGameBoard[9][9],
                              int X, int Y);
void printGameRules();



int main() {

  bool gameOver = false;
  bool win = false;

  printRules();

  int gameBoard[9][9];
  bool boolGameBoard[9][9];
  int revealTally = 0;

  revealTally = initalizeGameBoard(gameBoard, boolGameBoard, revealTally);
  printBoolBoard(boolGameBoard, gameBoard);
  cout << endl;

  // printGameBoardTesting(gameBoard, boolGameBoard);
  // cout << endl << revealTally << endl;

  while (gameOver == false) {

    int userX = 0, userY = 0;
    cout << "enter coordinates: " << endl;
    cout << "x: ";
    cin >> userX;
    cout << "y: ";
    cin >> userY;

    // add condition to make sure within bounds

    if (gameBoard[userX][userY] == -1) {
      gameOver = true;
      cout << "you hit a mine!" << endl;
      boolGameBoard[userX][userY] = true;

    } else {
      boolGameBoard[userX][userY] = true;
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

void printBoolBoard(bool boolGameBoard[9][9], int gameBoard[9][9]) {
    // Print column labels
    std::cout <<RED<< "   ";
    for (int i = 0; i < 9; ++i) {
        std::cout << std::setw(3) << i; // Column numbers
    }
    std::cout << std::endl;

    // Print separator bar
    std::cout << "   +----------------------------+" << std::endl;

    // Print rows with labels and game board contents
    for (int i = 0; i < 9; ++i) {
        std::cout<< RED << std::setw(2) << i << " |"; // Row number
        for (int j = 0; j < 9; ++j) {
            if (boolGameBoard[i][j]) {
                std::cout << WHITE<< std::setw(3) << gameBoard[i][j]; // Revealed cell value  
            } else {
                std::cout<< WHITE << std::setw(3) << "-"; // Unrevealed cell
            }
        }
        std::cout<<RED << " |" << std::endl;
    }

    // Print separator bar
    std::cout << RED << "   +----------------------------+" <<RESET<< std::endl;
}

void printRules() {
  cout <<RED<< "\n\n-------------------------------------" << endl;
  cout <<WHITE<< "       Welcome to Minesweeper!       " << endl;
  cout <<RED<< "-------------------------------------\n" <<RESET<< endl;
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
      cout << "-------------------------------------\n" << endl;
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
void printGameBoardTesting(int gameBoard[9][9], bool boolGameBoard[9][9]) {

  cout << right;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << setw(3) << gameBoard[i][j];
    }
    cout << endl;
  }
}
void fillWithMines(int gameBoard[9][9], int userStartX, int userStartY) {
  int numOfMines = 0;
  int maxNumOfMines = 10;
  srand(time(NULL));
  int randX = -1, randY = -1;

  while (numOfMines <= maxNumOfMines) {
    bool check = true;
    randX = rand() % 9;
    randY = rand() % 9;

    int defIndexX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int defIndexY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
      int updateRow = userStartX + defIndexX[i];
      int updateCol = userStartY + defIndexY[i];

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
void zeroGameBoard(int gameBoard[9][9], bool boolGameBoard[9][9]) {
  // fill baord with 0
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      gameBoard[i][j] = 0;
      boolGameBoard[i][j] = false;
    }
  }
}
void calcGameBoardInts(int gameBoard[9][9], int x, int y) {
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
void fillWithInts(int gameBoard[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (gameBoard[i][j] == -1) {
        // cout << "flag 2" << endl;
        calcGameBoardInts(gameBoard, i, j);
      }
    }
  }
}
int initalizeGameBoard(int gameBoard[9][9], bool boolGameBoard[9][9],
                       int revealTally) {

  // get coords
  zeroGameBoard(gameBoard, boolGameBoard);
  printBoolBoard(boolGameBoard, gameBoard);

  cout << "\nEnter Starting Point: ";
  int userStartX = -1;
  int userStartY = -1;
  cout << "\nX (0-8): ";
  cin >> userStartX;
  cout << "Y (0-8): ";
  cin >> userStartY;
  cout << endl; 

  // initalize game board
  //cout << "zeroing game board" << endl;


  // gameBoard[userStartX][userStartY] = -2;
  boolGameBoard[userStartX][userStartY] = true;

  // fill game board with mines
  //cout << "filling game board with mines" << endl;
  fillWithMines(gameBoard, userStartX, userStartY);

 // cout << "calculating baord" << endl;
  fillWithInts(gameBoard);

  recursiveRevealExplosion(gameBoard, boolGameBoard, userStartX, userStartY);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (boolGameBoard[i][j]) {
        revealTally++;
      }
    }
  }

  return revealTally;
}

void recursiveRevealExplosion(int gameBoard[9][9], bool boolGameBoard[9][9],
                              int X, int Y) {
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

void printGameRules(){
  cout << endl <<"eventuall, we'll add rules later\n" << endl;
}