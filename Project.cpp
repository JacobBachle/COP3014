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



void printPlayerBoard(int (&boardPlayer)[10][10]) {
    // Print column labels (1, 2, 3, etc.)
    cout << "   "; // Spacing to align with the board
    for (int j = 0; j < BOARD_SIZE; j++) {
        cout << " " << j << "  "; // Labels columns with numbers (1, 2, 3, ...)
    }
    cout << endl;
    cout << "  " << "_________________________________________" << endl;

    // Prints the appropriate symbol according to each int element and row labels
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << "|"<< " "; // Row label (0, 1, 2, ...)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (boardPlayer[i][j] == 0) {
                cout << " - " << "|"; // Empty spot
            }
            else if (boardPlayer[i][j] == 1) {
                cout << " * " << "|"; // Ship
            }
            else if (boardPlayer[i][j] == 2) {
                cout << " o " << "|";// Miss
            }
            else if (boardPlayer[i][j] == 3) {
                cout  << " x " << "|"; // Hit
            }
        }
        cout << endl; // New line after each row
    }
    cout << endl;
}

void printPlayerBoardCensored(int (&boardPlayer)[BOARD_SIZE][BOARD_SIZE]) {
     // Print column labels (1, 2, 3, etc.)
    cout << "   "; // Spacing to align with the board
    for (int j = 0; j < BOARD_SIZE; j++) {
        cout << " " << j << "  "; // Labels columns with numbers (1, 2, 3, ...)
    }
    cout << endl;
    cout << "  " << "_________________________________________" << endl;

    // Prints the appropriate symbol according to each int element and row labels
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << "|"<< " "; // Row label (0, 1, 2, ...)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (boardPlayer[i][j] == 0) {
                cout << " - " << "|"; // Empty spot
            }
            else if (boardPlayer[i][j] == 1) {
                cout << " - " << "|"; // Ship (hidden)
            }
            else if (boardPlayer[i][j] == 2) {
                cout << " o " << "|"; // Miss
            }
            else if (boardPlayer[i][j] == 3) {
                cout  << " x " << "|"; // Hit
            }
        }
        cout << endl; // New line after each row
    }
    cout << endl;
}

void placeShipsPlayer (int (&boardPlayer)[10][10]) {
    int shipsSize[] = {5,4,3,3,2}; //Change these to change ships to be placed. Each element is one ship.

    for (int i = 0; i < 5; i++) {
        int currShipsSize = shipsSize[i]; //Iterated for each element in shipsSize and sets currShipsSize to the current element in the array of ships to be placed.
        bool placed = false; //Will be false until the currShip is placed on players board

        while (!placed) {
            cout << "Place ship with size " << shipsSize[i] << endl;
            cout << "Enter starting row. Input should be (0 - " << BOARD_SIZE - 1 << "): ";
            int currRow;
            cin >> currRow;
            cout << endl;
            cout << "Enter starting column. Input should be (0 - " << BOARD_SIZE - 1 << "): ";
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
                        if (boardPlayer[i][currCol] == 1) {
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
                        if (boardPlayer[currRow][j] == 1) {
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
                        if (boardPlayer[i][currCol] == 1) {
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
                        if (boardPlayer[currRow][j] == 1) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            else {
                valid = false;
                cout << "Invalid orientation. Please enter a new orientation (0 for up, 1 for right, 2 for down, 3 for left): ";
                cin >> orientation;
                cout << endl;
            }

            if (valid) {// If current ship can be placed, sets the corrosponding element to 1 according to row, col, and orientation
                if (orientation == 0) {
                    for (int i = currRow; i > currRow - currShipsSize; i--) {
                        boardPlayer[i][currCol] = 1;
                    }
                    placed = true;
                }
                if (orientation == 1) {
                    for (int j = currCol; j < currCol + currShipsSize; j++) {
                        boardPlayer[currRow][j] = 1;
                    }
                    placed = true;
                }
                if (orientation == 2) {
                    for (int i = currRow; i < currRow + currShipsSize; i++) {
                        boardPlayer[i][currCol] = 1;
                    }
                    placed = true;
                }
                if (orientation == 3) {
                    for (int j = currCol; j > currCol - currShipsSize; j--) {
                        boardPlayer[currRow][j] = 1;
                    }
                    placed = true;
                }
                cout << "Ships placed sucessfully" << endl;
                printPlayerBoard(boardPlayer);
            }
            else { //if placed is not true at the point, position or orientaiton is invalid, looped to the start.
                cout << "Invalid position" << endl; 
            }
            

        }
    }
}

void PrintWhitespace()  {
    cout << "\n\n\n\n\n\n\n\n\n\n";
}


void Player1Turn()  { //player 1 takes their turn
int turnRow;    // get row coordinate for player 2 board from input
int turnColumn; // get column coordinate for player 2 board from input 
    cout << "Your board:"  << endl;
       printPlayerBoard(boardPlayer1); //prints player 1 board

    cout << "Opponent's board:" << endl;
       printPlayerBoardCensored(boardPlayer2); //prints player 2 board but only shows player 1 previous turns

    cout << "Enter row number 0 - 9: ";
    cin >> turnRow;

    cout << endl << "Enter column number 0 - 9: ";
    cin >> turnColumn;
    cout << endl;

    if (boardPlayer2[turnRow][turnColumn] == missed || boardPlayer2[turnRow][turnColumn] == hit)  {
        cout << "You've already tried that. Enter a new set of coordinates." << endl;
        cout << "Enter row number 0 - 9: ";
        cin >> turnRow;
        cout << endl << "Enter column number 0 - 9: ";
        cin >> turnColumn;
        cout << endl;
    // prompts player 1 to enter new coordinates if they tried the same coordinates as a previous turn
    }
    else if (turnColumn < 0 || turnColumn > 9 || turnRow < 0 || turnRow > 9)  {
        cout << "Invalid input.\n" << "Enter row number 0 - 9: ";
        cin >> turnRow;
        cout << endl << "Enter column number 0 - 9: ";
        cin >> turnColumn;
        cout << endl;
    // prompts player 1 to enter new coordinates if they went outside of the board
    }
    else if (boardPlayer2[turnRow][turnColumn] == occupied)  {
        cout << "You hit Player 2's ship!" << endl;
        boardPlayer2[turnRow][turnColumn] = hit; //update opponent's board
    }
    else if (boardPlayer2[turnRow][turnColumn] == empty)  {
        cout << "You missed!" << endl;
        boardPlayer2[turnRow][turnColumn] = missed; //update opponent's board
    }

    PrintWhitespace(); //print newlines so player 2 doesn't see player 2's board 

    cout << "Player 2's turn" << endl;
}

void Player2Turn()  { //player 2 takes their turn
int turnRow;    //get row coordinate for player 1 board from input
int turnColumn; //get column coordinate for player 1 board from input
    cout << "Your board:"  << endl;
       printPlayerBoard(boardPlayer2); //prints player 2 board

    cout << "Opponent's board:" << endl;
       printPlayerBoardCensored(boardPlayer1); //prints player 1 board but only shows player 2 previous turns


    cout << "Enter row number 0 - 9: ";
    cin >> turnRow;

    cout << endl << "Enter column number 0 - 9: ";
    cin >> turnColumn;
    cout << endl;

    if (boardPlayer1[turnRow][turnColumn] == missed || boardPlayer1[turnRow][turnColumn] == hit)  {
        cout << "You've already tried that. Enter a new set of coordinates." << endl;
        cout << "Enter row number 0 - 9: ";
        cin >> turnRow;
        cout << endl << "Enter column number 0 - 9: ";
        cin >> turnColumn;
        cout << endl;
    // prompts player 2 to enter new coordinates if they tried the same coordinates as a previous turn
    }
    else if (turnColumn < 0 || turnColumn > 9 || turnRow < 0 || turnRow > 9)  {
        cout << "Invalid input.\n" << "Enter row number 0 - 9: ";
        cin >> turnRow;
        cout << endl << "Enter column number 0 - 9: ";
        cin >> turnColumn;
        cout << endl;
    // prompts player 2 to enter new coordinates if they went outside of the board
    }
    else if (boardPlayer1[turnRow][turnColumn] == occupied)  {
        cout << "You hit Player 2's ship!" << endl;
        boardPlayer1[turnRow][turnColumn] = hit; //update opponent's board
    }
    else if (boardPlayer1[turnRow][turnColumn] == empty)  {
        cout << "You missed!" << endl;
        boardPlayer1[turnRow][turnColumn] = missed; //update opponent's board
    }


    PrintWhitespace(); //print new lines so player 2 doesn't see player 2's board

    cout << "Player 1's turn" << endl;
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

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
             boardPlayer1[x][y] = 0; //initalise every element of player1's board with 0
             boardPlayer2[x][y] = 0; //initalise every element of player2's board with 0
        }
    }    

    printPlayerBoard(boardPlayer1);
    placeShipsPlayer(boardPlayer1);

    PrintWhitespace();

    printPlayerBoard(boardPlayer2);
    placeShipsPlayer(boardPlayer2);

    while (gameWin == false) {

        Player1Turn();
        if (isBoardWin(boardPlayer2)) {
            gameWin = true;
            cout << "Player 1 wins!" << endl;
        }

        Player2Turn();
        if (isBoardWin(boardPlayer1)) {
            gameWin = true;
            cout << "Player 2 wins!" << endl;
        }

        //gameWin = true; //TO BE REMOVED, only present so loop is not infinite
    }
    return 0;
}
