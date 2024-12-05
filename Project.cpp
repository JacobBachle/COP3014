#include <iostream>
#include <vector>
#include <iomanip>
#include <string>   // For function getValidCoordinate

using namespace std;

const int BOARD_SIZE = 10;
const int empty = 0;
const int occupied = 1;
const int missed = 2; //if board has this as an element, a player chose to hit a position where it was empty
const int hit = 3; //if board has this as an element, a player chose to hit a position where it was occupied

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

void printPlayerBoard(int (&boardPlayer)[BOARD_SIZE][BOARD_SIZE]) {
    cout << "   "; // Spacing to align with the board
    for (int j = 0; j < BOARD_SIZE; j++) {
        cout << " " << j << "  "; // Labels columns with numbers (1, 2, 3, ...)
    }
    cout << endl;
    cout << "  " << "_________________________________________" << endl;

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
    cout << "   "; // Spacing to align with the board
    for (int j = 0; j < BOARD_SIZE; j++) {
        cout << " " << j << "  "; // Labels columns with numbers (1, 2, 3, ...)
    }
    cout << endl;
    cout << "  " << "_________________________________________" << endl;

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

bool getValidCoordinate(int& coord) {
    string input;
    while (true) {
        cin >> input; // Read the input as a string
        
        // Check if input is a single digit (0-9) by ensuring it's numeric and has length 1
        if (input.length() == 1 && isdigit(input[0])) {
            coord = input[0] - '0'; // Convert char to int
            return true;
        } else {
            cout << "Invalid input. Please enter a number between 0 and 9: ";
        }
    }
}

void placeShipsPlayer (int (&boardPlayer)[BOARD_SIZE][BOARD_SIZE]) {
    int shipsSize[] = {5,4,3,3,2}; //Change these to change ships to be placed. Each element is one ship.
    int numShips = sizeof(shipsSize) / sizeof(shipsSize[0]); //shipsSize length calculation
    for (int i = 0; i < numShips; i++) {
        int currShipsSize = shipsSize[i]; //Iterated for each element in shipsSize and sets currShipsSize to the current element in the array of ships to be placed.
        bool placed = false; //Will be false until the currShip is placed on players board

        while (!placed) {
            cout << "Place ship with size " << shipsSize[i] << endl;
            cout << "Enter starting row. Input should be (0 - " << BOARD_SIZE - 1 << "): ";
            int currRow;
            getValidCoordinate(currRow);  // Use the getValidCoordinate function for valid input
            cout << endl;
            cout << "Enter starting column. Input should be (0 - " << BOARD_SIZE - 1 << "): ";
            int currCol;
            getValidCoordinate(currCol);  // Use the getValidCoordinate function for valid input
            cout << endl;

            cout << "Enter orientation (0 for up, 1 for right, 2 for down, 3 for left): ";
            int orientation;
            getValidCoordinate(orientation);  // Use the getValidCoordinate function for valid input
            cout << endl;

            bool valid = true;
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

            if (valid) {
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
                cout << "Ship placed successfully!" << endl;
                printPlayerBoard(boardPlayer);
            }
            else {
                cout << "Invalid position, please try again!" << endl;
            }
        }
    }
}

void printWhitespace()  {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void PlayerTurn(int (&playerBoard)[BOARD_SIZE][BOARD_SIZE], int (&opponentBoard)[BOARD_SIZE][BOARD_SIZE], const string& playerName, const string& opponentName) {
    int currRow;
    int currColumn;

    cout << "\n" << playerName << "'s Turn\n";
    cout << "------------------------------" << endl;
    cout << "Your board:" << endl;
    printPlayerBoard(playerBoard);

    cout << opponentName << "'s board:" << endl;
    printPlayerBoardCensored(opponentBoard);

    bool validGuess = false; // Flag to ensure a valid square is chosen
    while (!validGuess) {
        cout << "Enter row number (0 - 9): ";
        getValidCoordinate(currRow); // Ensures valid input for row

        cout << "Enter column number (0 - 9): ";
        getValidCoordinate(currColumn); // Ensures valid input for column

        if (opponentBoard[currRow][currColumn] == 2 || opponentBoard[currRow][currColumn] == 3) {
            cout << "You have already guessed this square. Please try again." << endl;
        } else {
            validGuess = true; // Valid square
        }
    }

    if (opponentBoard[currRow][currColumn] == 0) {
        cout << "Miss!" << endl;
        opponentBoard[currRow][currColumn] = 2; // Mark the miss on the opponent's board
    } else if (opponentBoard[currRow][currColumn] == 1) {
        cout << "Hit!" << endl;
        opponentBoard[currRow][currColumn] = 3; // Mark the hit on the opponent's board
    }

    // Check if the opponent has lost (no ships left)
    bool opponentHasShipsLeft = false;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (opponentBoard[i][j] == 1) {
                opponentHasShipsLeft = true;
                break;
            }
        }
        if (opponentHasShipsLeft) break;
    }

    if (!opponentHasShipsLeft) {
        cout << opponentName << " has lost! " << playerName << " wins!" << endl;
        gameWin = true;
    }
}

int main() {

    // Initialize both boards to empty (0 means empty)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            boardPlayer1[i][j] = 0;
            boardPlayer2[i][j] = 0;
        }
    }

    // Place ships for Player 1
    cout << "Welcome Player 1!" << endl;
    cout << "Place your ships" << endl;
    printPlayerBoard(boardPlayer1);
    placeShipsPlayer(boardPlayer1);

    printWhitespace();
    printWhitespace(); // Spaces boards so player 2 dosent see player 1's full board

    // Place ships for Player 2
    cout << "Welcome Player 2!" << endl;
    cout << "Place your ships" << endl;
    printPlayerBoard(boardPlayer2);
    placeShipsPlayer(boardPlayer2);

    printWhitespace();
    printWhitespace();
    string player1Name;
    string player2Name;
    cout << "Enter Player 1's name: ";
    cin >> player1Name;
    cout << "Enter Player 2's name: ";
    cin >> player2Name;

    while (!gameWin) {//ends when there is a winning board (some board has no 1's in any element)
        // Player 1's turn
        PlayerTurn(boardPlayer1, boardPlayer2, player1Name, player2Name);
        if (gameWin) break;

        // Player 2's turn
        PlayerTurn(boardPlayer2, boardPlayer1, player2Name, player1Name);
    }

    return 0;
}
