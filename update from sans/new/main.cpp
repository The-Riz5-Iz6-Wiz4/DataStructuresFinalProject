#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <chrono>

using namespace std;

void spaceConsole(int lineSize){
    for (int i = 0; i < lineSize; i++){
        cout << "" << endl;
    }

}

class Player
{
private:
    //track number of this player ship's
    //track the position of the player's ship's
    //track the number of player's ship's that are destroyed



//    const static int BoardSize = 10;
//    const static int BoardSize = 10;
    const static int BoardSize = 10;
    const static int maximumShips = 10;

    const static int NOSHIP = 0;
    const static int ATTACKED = 1;
    const static int SHIP = 2;
    const static int DESTROYED = 3;

    int matrixBoard[BoardSize][BoardSize]; //keep track of positions of player's ships

    //need variable to identify type of player
    bool isCpu;

    //need variable to get number of ships
    int numOfShips = 0; //player and cpu has this attribute

    int coord;
    struct coordPair {
        int xCoord;
        int yCoord;
    };

        //method to clear the board of ships(sets everything to 0)
    void clearGrid() {
        for (int x = 0; x < BoardSize; x++) {
            for (int y = 0; y < BoardSize; y++) {
                matrixBoard[x][y] = 0;
            }
        }
    }


        //method to set ships onto the board
    void setShips() {
        if (isCpu == false){
            //setting the player's ship coord
            cout << "You need to set 10 ships!" << endl;
            while (numOfShips < maximumShips) {
                //spaceConsole();
                int setXCoord = takeInputBoard("To set ship coordinate, please enter X: ");
                int setYCoord = takeInputBoard("Please enter Y: ");
//                cout << "To set ship coordinate, please enter X: " << endl;
//                cin >> setXCoord;
//                cout << "Please enter Y: " << endl;
//                cin >> setYCoord;

                if (matrixBoard[setXCoord][setYCoord] != SHIP) {                            //if matrix board does not contain a ship
                    numOfShips++;                                                           //add one to the num of ships counter
                    matrixBoard[setXCoord][setYCoord] = SHIP;
                    spaceConsole(5);                                                        //set that location to a ship
                    displayBoard();
                    cout << "You have to set " << maximumShips - numOfShips << " more ships" << endl;
                }
                else {                                                                      //if matrix is occupied with a ship already
                    cout << "A ship is already placed there, please try again!" << endl;
                }

            }

        }
        else {
            //
            while (numOfShips < maximumShips) {
                int xPosition = rand() % 10;
                int yPosition = rand() % 10;

                if (matrixBoard[xPosition][yPosition] != SHIP) {
                    numOfShips++;
                    matrixBoard[xPosition][yPosition] = SHIP;
                }
            }
        }


    }



public:

    //constructor method for Player
    Player(bool _isCpu) {
        isCpu = _isCpu;
        clearGrid();
        setShips();
        //coord = 0;
        //maximumShips = 10;
    }

    //getter for number of ships
    int getNumOfShips(){
        return numOfShips;
    }

    //method to show the grid
    void showGrid() {
        cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
        cout << "-----------------------" << endl;
        for (int x = 0; x < BoardSize; x++)
        {
            cout << coord << "| ";
            coord++;
            for (int y = 0; y < BoardSize; y++)
            {
                cout << matrixBoard[x][y] << " ";
            }
            cout << endl;
        }
    }

    //method for finding number of ships : get back to this later
    int numberOfShips() {
        int c = 0;
        for (int x = 0; x < BoardSize; x++)
        {
            for (int y = 0; y < BoardSize; y++)
            {
                if (matrixBoard[x][y] == 1)
                {
                    c++;
                }
            }
        }
        return c;
    }


    //method to attack the target coordinates
    bool attack(Player *enemy, int newX, int newY) {
        //check the coordinate:
        //if coordinate is occupied with ship, destroy it
        if (enemy->matrixBoard[newX][newY] == SHIP) {
            enemy->matrixBoard[newX][newY] = DESTROYED;
            cout << "it destroyed" << " " << newX << " " << newY << endl;
            //enemy->displayBoard();
            return true;
        }
        //else if coordinate is not occupied with a ship, mark it as attacked
        else if (enemy->matrixBoard[newX][newY] == NOSHIP) {
            enemy->matrixBoard[newX][newY] = ATTACKED;
            cout << "it attacked" << " " << newX << " " << newY << endl;
            //enemy->displayBoard();
            return true;
        }
        //else if coordinate is already destroyed, tell user that the ship has already been destroy
        else if (enemy->matrixBoard[newX][newY] == DESTROYED) {
            if (isCpu == false) cout << "This ship has been destroyed." << endl;
            return false;
        }
        //else if coordinate is already attacked, tell user that they've already picked that location
        else if (enemy->matrixBoard[newX][newY] == ATTACKED) {
            if (isCpu == false) cout << "You've already attacked that location." << endl;
            return false;
        }
        //else unidentified location
        else {
            if (isCpu == false) cout << "Invalid location input. Please try again." << endl;
            return false;
        }
    }

    //display player object boards
    void displayBoard() {
        for (int i = 0; i < BoardSize; i++){
            for(int j = 0; j < BoardSize; j++){
                //check if the coordinate is a specific state or not
                if (isCpu == false) {
                    if (matrixBoard[i][j] == NOSHIP){
                       cout << " -";
                    }
                    else if (matrixBoard[i][j] == ATTACKED){
                        cout << " *";
                    }
                    else if (matrixBoard[i][j] == SHIP){
                        cout << " V";
                    }
                    else if (matrixBoard[i][j] == DESTROYED){
                        cout << " X";
                    }
                }
                else {
                    if (matrixBoard[i][j] == NOSHIP){
                       cout << " -";
                    }
                    else if (matrixBoard[i][j] == ATTACKED){
                        cout << " *";
                    }
                    else if (matrixBoard[i][j] == SHIP){
                        cout << " -";
                    }
                    else if (matrixBoard[i][j] == DESTROYED){
                        cout << " X";
                    }
                }

            }
            cout << "" << endl;
        }
    }

    //method to take user input. string prompt helps to display the prompt that is needed to be asked, and then take
    int takeInputBoard(string prompt) {
    //setup int value to return
        int input;
        string rawInput;
        cout << prompt << endl;
        cin >> rawInput;
        bool convertSuccess = false;

    //while loop to check if input is greater than rows and columns amount
    //input > BoardSize
        do {
            try {
                input = stoi(rawInput);
                while (input > BoardSize) {
                    cout << "Invalid input, please enter a number within the size of the board." << endl;
                    cin >> input;
                convertSuccess = true;
                }
            }
            catch (...) {
                cout << "Invalid input, please try a number." << endl;
                cin >> rawInput;
            }


        } while (!convertSuccess);


            //if (){
            //    break;
            //}


        return input - 1;

    }


    void doTurn(Player *enemy) {
        if (isCpu == false) {
            cout << "It's time for you to attack." << endl;

            int xInput;
            int yInput;

            do {
            //take input of player of the coordinates they want to attack
            xInput = takeInputBoard("Enter the x-coordinate that you want to attack: ");
            yInput = takeInputBoard("Enter the y-coordinate that you want to attack: ");
            //call attack function taking the coordinates as parameters
            } while (!attack(enemy, xInput, yInput));
        }
        else {
            int xCpuPos;
            int yCpuPos;
            do {
            //create random positions
            xCpuPos = rand() % 10;
            yCpuPos = rand() % 10;
            } while (!attack(enemy, xCpuPos, yCpuPos));

        }
    }


    //display the lose screen
    void displayLoseScreen(){
        cout << "" << endl;
    }

    //display the win screen
    void displayWinScreen(){
        cout << "" << endl;
    }


};


int main() {
    srand(time(0));
    //set up two Players: (player and cpu) and set up each's board
    Player player(false);
    Player cpu(true);

    //start turn based/game loop
    do {
        //first display the board; cpu board on top and player board under
        cpu.displayBoard();
        spaceConsole(1);
        player.displayBoard();
        spaceConsole(1);
        //ask player to attack
        player.doTurn(&cpu);
        //let cpu do its thing
        cpu.doTurn(&player);

    } while(player.getNumOfShips() > 0 && cpu.getNumOfShips() > 0);

    //check winner
    if (cpu.getNumOfShips() == 0) {

    }
    else if (player.getNumOfShips() == 0) {

    }

    //print the results

}




