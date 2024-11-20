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

void placeShipsPlayer1 () {
    int shipsSize[] = {5,4,3,3,2}; //Change these to change ships to be placed. Each element is one ship.

    for (int i = 0; i < 5; i++) {
        int currShipsSize = shipsSize[i]; //Iterated for each element in shipsSize and sets currShipsSize to the current element in the array of ships to be placed.
        bool placed = false; //Will be false until the currShip is placed on players board

        while (!placed) {
            cout << "Place ship with size " << shipsSize[i] << endl;
            cout << "Enter starting row. Input should be (0 - " << BOARD_SIZE << "): ";
            int currRow;
            cin >> currRow;
            cout << endl;
            cout << "Enter starting column. Input should be (0 - " << BOARD_SIZE << "): ";
            int currCol;
            cin >> currCol; //input starting row and col
            cout << endl;

            cout << "Enter orientation (0 for up, 1 for right, 2 for down, 3 for left) ";
            int orientation;
            cin >> orientation;
            cout << endl;

            bool valid = true;
            /*
            Checks if the row or col will go out of bounds because of the orientation.
            Then checks if there is already a 1 (ship placed) at the element expected to be placed.
            */
            if (orientation == 0) {
                if ((currRow - currShipsSize) < 0) {
                    valid = false;
                }
                else {
                    for (int i = currRow; i > currRow - currShipsSize; i--) {
                        if (boardPlayer1[i][currCol] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            else if (orientation == 1) {
                if ((currCol + currShipsSize) > BOARD_SIZE) {
                    valid = false;
                }
                else {
                    for (int j = currCol; j < currCol + currShipsSize; j++) {
                        if (boardPlayer1[currRow][j] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            else if (orientation == 2) {
                if ((currRow + currShipsSize) > BOARD_SIZE) {
                    valid = false;
                }
                else {
                    for (int i = currRow; i < currRow + currShipsSize; i++) {
                        if (boardPlayer1[i][currCol] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            else if (orientation == 3) {
                if ((currCol - currShipsSize) < 0) {
                    valid = false;
                }
                else {
                    for (int j = currCol; j > currCol - currShipsSize; j--) {
                        if (boardPlayer1[currRow][j] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }

            if (valid) {// If current ship can be placed, sets the corrosponding element to 1 according to row, col, and orientation
                if (orientation == 0) {
                    for (int i = currRow; i > currRow - currShipsSize; i--) {
                        boardPlayer1[i][currCol] = 1;
                    }
                    placed = true;
                }
                if (orientation == 1) {
                    for (int j = currCol; j < currCol + currShipsSize; j++) {
                        boardPlayer1[currRow][j] = 1;
                    }
                    placed = true;
                }
                if (orientation == 2) {
                    for (int i = currRow; i < currRow + currShipsSize; i++) {
                        boardPlayer1[i][currCol] = 1;
                    }
                    placed = true;
                }
                if (orientation == 3) {
                    for (int j = currCol; j > currCol - currShipsSize; j--) {
                        boardPlayer1[currRow][j] = 1;
                    }
                    placed = true;
                }
                cout << "Ships placed sucessfully" << endl;
                printPlayer1Board();
            }
            else { //if placed is not true at the point, position or orientaiton is invalid, looped to the start.
                cout << "Invalid position" << endl; 
            }
            

        }
    }
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

void placeShipsPlayer2 () {
    int shipsSize[] = {5,4,3,3,2};

    for (int i = 0; i < 5; i++) {
        int currShipsSize = shipsSize[i];
        bool placed = false;

        while (!placed) {
            cout << "Place ship with size " << shipsSize[i] << endl;
            cout << "Enter starting row. Input should be (0 - " << BOARD_SIZE << "): ";
            int currRow;
            cin >> currRow;
            cout << endl;
            cout << "Enter starting column. Input should be (0 - " << BOARD_SIZE << "): ";
            int currCol;
            cin >> currCol; //input starting row and col
            cout << endl;

            cout << "Enter orientation (0 for up, 1 for right, 2 for down, 3 for left) ";
            int orientation;
            cin >> orientation;
            cout << endl;

            bool valid = true;
            if (orientation == 0) {
                if ((currRow - currShipsSize) < 0) {
                    valid = false;
                }
                else {
                    for (int i = currRow; i > currRow - currShipsSize; i--) {
                        if (boardPlayer2[i][currCol] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            else if (orientation == 1) {
                if ((currCol + currShipsSize) > BOARD_SIZE) {
                    valid = false;
                }
                else {
                    for (int j = currCol; j < currCol + currShipsSize; j++) {
                        if (boardPlayer2[currRow][j] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            else if (orientation == 2) {
                if ((currRow + currShipsSize) > BOARD_SIZE) {
                    valid = false;
                }
                else {
                    for (int i = currRow; i < currRow + currShipsSize; i++) {
                        if (boardPlayer2[i][currCol] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            else if (orientation == 3) {
                if ((currCol - currShipsSize) < 0) {
                    valid = false;
                }
                else {
                    for (int j = currCol; j > currCol - currShipsSize; j--) {
                        if (boardPlayer2[currRow][j] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }

            if (valid) {
                if (orientation == 0) {
                    for (int i = currRow; i > currRow - currShipsSize; i--) {
                        boardPlayer2[i][currCol] = 1;
                    }
                    placed = true;
                }
                if (orientation == 1) {
                    for (int j = currCol; j < currCol + currShipsSize; j++) {
                        boardPlayer2[currRow][j] = 1;
                    }
                    placed = true;
                }
                if (orientation == 2) {
                    for (int i = currRow; i < currRow + currShipsSize; i++) {
                        boardPlayer2[i][currCol] = 1;
                    }
                    placed = true;
                }
                if (orientation == 3) {
                    for (int j = currCol; j > currCol - currShipsSize; j--) {
                        boardPlayer2[currRow][j] = 1;
                    }
                    placed = true;
                }
                cout << "Ships placed sucessfully" << endl;
                printPlayer2Board();
            }
            else {
                cout << "Invalid position" << endl;
            }
            

        }
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

        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                boardPlayer1[x][y] = 0; //initalise every element of player1's board with 0
                boardPlayer2[x][y] = 0; //initalise every element of player2's board with 0
            }
        }    

        gameWin = true; //TO BE REMOVED, only present so loop is not infinite
    }
    return 0;
}
