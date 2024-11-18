#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int BOARD_SIZE = 10;
const int empty = 0;
const int occupied = 1;
const int missed = 2; //if board has this as an element, a player choosed to hit a position where it was empty
const int hit = 3; //if board has this as an element, a player choosed to hit a position where it was occupied

bool gameWin = false;
int boardPlayer1[BOARD_SIZE][BOARD_SIZE];
int boardPlayer2[BOARD_SIZE][BOARD_SIZE];

/*
1 Aircraft Carrier, 5 spots
1 Battleship, 4 spots
1 Destroyer, 3 spots
1 Submarine, 3 spots
1 Patrol Boat, 2 spots
*/

void placeShipsPlayer1 () {
    //
}

void printPlayer1Board() {
    // Prints the appropriate symbol according to each int element.
    for(int i = 0; i < BOARD_SIZE; i ++) {
        for(int j = 0; j < BOARD_SIZE; j ++) {
            if(boardPlayer1[i][j] == 0) {
                cout << " " << "_";
            }
            else if (boardPlayer1[i][j] == 1) {
                cout << " "  << "*";
            }
            else if (boardPlayer1[i][j] == 2) {
                cout << " " << "o";
            }
            else if (boardPlayer1[i][j] == 3) {
                cout << " " << "x";
            }
            }
          cout << endl;
        }
    }

void placeShipsPlayer2 () {
    //
}

void printPlayer2Board() {
        // Prints the appropriate symbol according to each int element - Anthony.
    for(int i = 0; i < BOARD_SIZE; i ++) {
        for(int j = 0; j < BOARD_SIZE; j ++) {
            if(boardPlayer2[i][j] == 0) {
                cout << " " << "_";
            }
            else if (boardPlayer2[i][j] == 1) {
                cout << " "  << "*";
            }
            else if (boardPlayer2[i][j] == 2) {
                cout << " " << "o";
            }
            else if (boardPlayer2[i][j] == 3) {
                cout << " " << "x";
            }
            }
          cout << endl;
        }
    }

bool isBoardWin(int board[BOARD_SIZE][BOARD_SIZE]) {
    //Board is a winning board if no occupied elements are left, note occupied elemts are have a value of 1
    //Board is a winning board if no element in the array is 1
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == occupied) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    while (gameWin == false) {

        gameWin = true; //TO BE REMOVED, only present so loop is not infinite
    }
    return 0;
}
