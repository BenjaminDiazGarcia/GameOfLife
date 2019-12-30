#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <fstream>

#include "GameOfLife.h"

using namespace std;

bool** initialize();
void printBoard(bool**);
void deleteAll(bool**);
void copyBoard(bool**, bool**);
void determineCurrentState(bool**);
bool** readFile();

int main() {
    
    auto game = new GameOfLife();
    
    game->startGame();
    
	return 0;
}


