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

void placeShipsPlayer1 (int boardPlayer1[BOARD_SIZE][BOARD_SIZE]) {
    int shipsSize = {5,4,3,3,2};
    int shipsQuantity = {1, 1, 1, 1, 1};

    for (int i = 0; i < shipsQuantity.size(); i++) {
        int currShipsSize = shipsSize[i];
        bool placed = false;

        while (!placed) {
            cout << "Place ship with size " << shipsSize[i] << endl;
            cout << "Enter starting row and column. Input should be (0 - " << BOARD_SIZE << "): ";
            int currRow;
            int currCol;
            cin >> row >> col;

            cout << "Enter orientation (0 for up, 1 for right, 2 for down, 3 for left) ";
            int orientation;
            cin >> orientation;

            bool valid = false;
            while (valid == false) {
                if (orientation == 0) {
                    if ((currRow - currShipsSize) > 0) {
                        valid = true;
                    }
                }
                else if (orientation == 1) {
                    if ((currCol + currShipsSize) < BOARD_SIZE) {
                        valid = true;
                    }
                }
                else if (orientation == 2) {
                    if ((currRow + currShipsSize) < BOARD_SIZE) {
                        valid = true;
                    }
                }
                else if (orientation == 3) {
                    if ((currCol - currShipsSize) > 0) {
                        valid = true;
                    }
                }

                if (!valid) {
                    cout << "Input goes out of bound. Would you like to change the orientation (input 1) or change the starting row and column (input 2): ";
                    int change;
                    cin >> change;
                    if (change == 1) {
                        cout << "Input new orientation (0 for up, 1 for right, 2 for down, 3 for left): "
                        cin >> orientation;
                    }
                    if (change == 2) {
                        cout << "Input new starting row and column (row column): "
                        cin >> currRow;
                        cin >> currCol;
                    }
                    if ((change != 1) && (change != 2)) {
                        cout << "Please input either 1 or 2"
                        cin >> change;
                    }
                }
                //If reached this point it is assumed that there is a currRow, currCol, and orientation that is valid for the ship size
                if (orientation == 0) {
                    for (int i = currRow; i > currRow - currShipsSize; i--) {
                        boardPlayer1[i][currCol] = 1;
                    }
                }
                if (orientation == 1) {
                    for (int j = currCol; j < currCol + currShipsSize; j++) {
                        boardPlayer1[currRow][j] = 1;
                    }
                }
                if (orientation == 2) {
                    for (int i = currRow; i < currRow + currShipsSize; i++) {
                        boardPlayer1[i][currCol] = 1;
                    }
                }
                if (orientation == 3) {
                    for (int j = currCol; j > currCol - currShipsSize; j--) {
                        boardPlayer1[currRow][j] = 1;
                    }
                }
            }
            

        }
    }
}

void printPlayer1Board() {
    // Print column labels (1, 2, 3, etc.)
    cout << "    "; // Extra space for row label alignment
    for (int j = 0; j < BOARD_SIZE; j++) {
        cout << " " << j + 1; // Labels columns with numbers (1, 2, 3, ...)
    }
    cout << endl;

    // Prints the appropriate symbol according to each int element and row labels
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i + 1 << " "; // Row label (1, 2, 3, ...)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (boardPlayer1[i][j] == 0) {
                cout << " " << "_"; // Empty spot
            }
            else if (boardPlayer1[i][j] == 1) {
                cout << " " << "*"; // Ship
            }
            else if (boardPlayer1[i][j] == 2) {
                cout << " " << "o"; // Hit
            }
            else if (boardPlayer1[i][j] == 3) {
                cout << " " << "x"; // Miss
            }
        }
        cout << endl; // New line after each row
    }
}

void placeShipsPlayer2 () {
    //
}

void printPlayer2Board() {
    // Print column labels (1, 2, 3, etc.)
    for (int j = 0; j < BOARD_SIZE; j++) {
        cout << " " << j + 1; // Labels columns with numbers (1, 2, 3, ...)
    }
    cout << endl;

    // Print the rows with labels (1, 2, 3, etc.)
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i + 1 << " "; // Row label (1, 2, 3, ...)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (boardPlayer2[i][j] == 0) {
                cout << " " << "_";  // Empty spot
            }
            else if (boardPlayer2[i][j] == 1) {
                cout << " " << "*";  // Ship
            }
            else if (boardPlayer2[i][j] == 2) {
                cout << " " << "o";  // Hit
            }
            else if (boardPlayer2[i][j] == 3) {
                cout << " " << "x";  // Miss
            }
        }
        cout << endl; // New line after each row
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
