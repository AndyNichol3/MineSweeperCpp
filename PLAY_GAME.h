#ifndef PLAY_GAME_H
#define PLAY_GAME_H
#include <vector>

int printBoolBoard(const std::vector<std::vector<bool>> &boolGameBoard,
                   const std::vector<std::vector<int>> &gameBoard,
                   int maxNumberOfRows, int maxNumberOfColumns);

void recursiveRevealExplosion(std::vector<std::vector<int>> &gameBoard,
                              std::vector<std::vector<bool>> &boolGameBoard,
                              int X, int Y, int maxNumberOfRows,
                              int maxNumberOfColumns);

int getInputX(int maxNumberOfColumns);
int getInputY(int maxNumberOfRows);
void printRoundHeader(int round);
void printWin();
void printLose();

bool playGame(int maxNumberOfColumns, int maxNumberOfRows,
              std::vector<std::vector<bool>> &boolGameBoard,
              std::vector<std::vector<int>> &gameBoard, int maxNumOfMines);

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