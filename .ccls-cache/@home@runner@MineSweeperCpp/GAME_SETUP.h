#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include <vector>

// include

// programs
void printGameRules();
void printGameWelcome();
int getUserDifficulty();

void fillWithMines(std::vector<std::vector<int>> &gameBoard, int userStartRow,
                   int userStartCol, int maxNumOfMines, int maxNumberOfRows,
                   int maxNumberOfColumns);

void fillWithInts(std::vector<std::vector<int>> &gameBoard, int maxNumberOfRows,
                  int maxNumberOfColumns);
void calcGameBoardInts(std::vector<std::vector<int>> &gameBoard, int x, int y,
                       int maxNumberOfRows, int maxNumberOfColumns);

void initalizeGameBoard(std::vector<std::vector<bool>> &boolGameBoard,
                        std::vector<std::vector<int>> &gameBoard,
                        int maxNumberOfRows, int maxNumberOfColumns,
                        int maxNumOfMines);

#endif