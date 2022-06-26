#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <chrono>

using namespace std;




void spaceConsole(int lineSize){ //simulate clearing the console method
    for (int i = 0; i < lineSize; i++){
        cout << "" << endl;
    }

}

void hashtagConsole(int lineSize){ //create hashtag line method
    for (int i = 0; i < lineSize; i++){
        cout << "#";
    }
    cout << "" << endl;

}

void displayTitle(){ //displaying the title method
    spaceConsole(5);
    hashtagConsole(120);
    spaceConsole(1);
    //cout << "Battleships: C++ Remake" << endl;
    cout << R"(
     ________  ________  _________  _________  ___       _______   ________  ___  ___  ___  ________  ________
    |\   __  \|\   __  \|\___   ___\\___   ___\\  \     |\  ___ \ |\   ____\|\  \|\  \|\  \|\   __  \|\   ____\
    \ \  \|\ /\ \  \|\  \|___ \  \_\|___ \  \_\ \  \    \ \   __/|\ \  \___|\ \  \\\  \ \  \ \  \|\  \ \  \___|_
     \ \   __  \ \   __  \   \ \  \     \ \  \ \ \  \    \ \  \_|/_\ \_____  \ \   __  \ \  \ \   ____\ \_____  \
      \ \  \|\  \ \  \ \  \   \ \  \     \ \  \ \ \  \____\ \  \_|\ \|____|\  \ \  \ \  \ \  \ \  \___|\|____|\  \
       \ \_______\ \__\ \__\   \ \__\     \ \__\ \ \_______\ \_______\____\_\  \ \__\ \__\ \__\ \__\     ____\_\  \
        \|_______|\|__|\|__|    \|__|      \|__|  \|_______|\|_______|\_________\|__|\|__|\|__|\|__|    |\_________\
                                                                     \|_________|                       \|_________|
    )" << endl;
    cout << "                                         A C++ Remake" << endl;
    cout << "                               by Sandrian - Sulthan - Rayhan" << endl;
    spaceConsole(1);
    hashtagConsole(120);
    spaceConsole(5);

}

void winText(){ //ascii art text of winning method
    cout << R"(
      ___    ___ ________  ___  ___          ___       __   ___  ________
     |\  \  /  /|\   __  \|\  \|\  \        |\  \     |\  \|\  \|\   ___  \
     \ \  \/  / | \  \|\  \ \  \\\  \       \ \  \    \ \  \ \  \ \  \\ \  \
      \ \    / / \ \  \\\  \ \  \\\  \       \ \  \  __\ \  \ \  \ \  \\ \  \
       \/  /  /   \ \  \\\  \ \  \\\  \       \ \  \|\__\_\  \ \  \ \  \\ \  \
     __/  / /      \ \_______\ \_______\       \ \____________\ \__\ \__\\ \__\
    |\___/ /        \|_______|\|_______|        \|____________|\|__|\|__| \|__|
    \|___|/
    )" << endl;

}

void loseText(){ //ascii art text of losing method
    cout << R"(
      ___    ___ ________  ___  ___          ___       ________  ________  _______
     |\  \  /  /|\   __  \|\  \|\  \        |\  \     |\   __  \|\   ____\|\  ___ \
     \ \  \/  / | \  \|\  \ \  \\\  \       \ \  \    \ \  \|\  \ \  \___|\ \   __/|
      \ \    / / \ \  \\\  \ \  \\\  \       \ \  \    \ \  \\\  \ \_____  \ \  \_|/__
       \/  /  /   \ \  \\\  \ \  \\\  \       \ \  \____\ \  \\\  \|____|\  \ \  \_|\ \
     __/  / /      \ \_______\ \_______\       \ \_______\ \_______\____\_\  \ \_______\
    |\___/ /        \|_______|\|_______|        \|_______|\|_______|\_________\|_______|
    \|___|/                                                        \|_________|
    )" << endl;
}





class Player
{
private:
    const static int BoardSize = 10; //Declares the maximum board size
    const static int maximumShips = 10; //Declares the max amount of ships available

    const static int NOSHIP = 0; //int to show if there is no ship on the board
    const static int ATTACKED = 1; //int to show if a particular location has been attacked on the board
    const static int SHIP = 2; //int to show if there is a ship on a certain location on the board
    const static int DESTROYED = 3; //int to show if the position has a destroyed ship on the board

    int matrixBoard[BoardSize][BoardSize]; //keep track of positions of player's ships

    //need variable to identify type of player
    bool isCpu;

    //need variable to get number of ships
    int numOfShips = 0; //player and cpu has this attribute




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
        if (isCpu == false){ //checking if it's setting the ship for the player
            cout << "You need to set 10 ships!" << endl;
            spaceConsole(1);
            //setting the player's ship coordinate
            while (numOfShips < maximumShips) { //checking the amount of ships you have to set by comparing to the max value
                int setXCoord = takeInputBoard("To set ship coordinate, please enter X: ");
                int setYCoord = takeInputBoard("Please enter Y: ");

                if (matrixBoard[setXCoord][setYCoord] != SHIP) {     //if matrix board does not contain a ship
                    numOfShips++;                                    //add one to the num of ships counter
                    matrixBoard[setXCoord][setYCoord] = SHIP;        //set that location to a ship
                    spaceConsole(30);
                    displayBoard();                                  //display board to have a visual indicator of where the player sets their ship
                    cout << "You have to set " << maximumShips - numOfShips << " more ships" << endl;
                }
                else {      //if matrix is occupied with a ship already
                    cout << "A ship is already placed there, please try again!" << endl;
                }

            }

        }
        else { //checking if it's setting the ship for the cpu
            //have a randomizer create the cpu's set locations
            while (numOfShips < maximumShips) { //checking the amount of ships the cpu has to set by comparing to the max value
                int xPosition = rand() % maximumShips;
                int yPosition = rand() % maximumShips;

                if (matrixBoard[xPosition][yPosition] != SHIP) { //same as on line 62
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
    }

    //getter for number of ships
    int getNumOfShips(){
        return numOfShips;
    }


    //method to attack the target coordinates
    bool attack(Player *enemy, int newX, int newY) {
        //check the coordinate:
        //if coordinate is occupied with ship, destroy it
        if (enemy->matrixBoard[newX][newY] == SHIP) {
            enemy->matrixBoard[newX][newY] = DESTROYED;
            //cout << "it destroyed" << " " << newX << " " << newY << endl;
            enemy->numOfShips--;
            return true;
        }
        //else if coordinate is not occupied with a ship, mark it as attacked
        else if (enemy->matrixBoard[newX][newY] == NOSHIP) {
            enemy->matrixBoard[newX][newY] = ATTACKED;
            //cout << "it attacked" << " " << newX << " " << newY << endl;
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
                if (isCpu == false) { //checking if this is done for cpu or player
                    if (matrixBoard[i][j] == NOSHIP){ //if no ship
                       cout << " -";
                    }
                    else if (matrixBoard[i][j] == ATTACKED){ //if location is attacked already
                        cout << " *";
                    }
                    else if (matrixBoard[i][j] == SHIP){ //if there is a ship
                        cout << " V";
                    }
                    else if (matrixBoard[i][j] == DESTROYED){ //if the ship is destroyed
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
                convertSuccess = true;
            }
            catch (...) {
                cout << "Invalid input, please try a number." << endl;
                cin >> rawInput;
            }


        } while (!convertSuccess);

        while (input > BoardSize) {
            cout << "Invalid input, please enter a number within the size of the board." << endl;
            cin >> input;
            //if (){
            //    break;
            //}
        }

        return input - 1;

    }


    void doTurn(Player *enemy) { //enemy pointer
        if (isCpu == false) { //check for player
            spaceConsole(1);
            hashtagConsole(30);
            spaceConsole(1);
            cout << "It's time for you to attack." << endl;
            spaceConsole(1);
            hashtagConsole(30);
            spaceConsole(1);
            //cout << "You have " << numOfShips << endl;

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
            //create random positions in limit to the board size
            xCpuPos = rand() % BoardSize;
            yCpuPos = rand() % BoardSize;
            } while (!attack(enemy, xCpuPos, yCpuPos));

        }
    }


    //display the lose screen
    void displayLoseScreen(){
//        spaceConsole(1);
//        hashtagConsole(30);
        spaceConsole(1);
        cout << "Goddamnit. You lost to a randomizer. All your ships are lost. Try again next time." << endl;
        spaceConsole(1);
//        hashtagConsole(30);
//        spaceConsole(1);
    }

    //display the win screen
    void displayWinScreen(){
//        spaceConsole(1);
//        hashtagConsole(30);
        spaceConsole(1);
        cout << "Congratulations. You win! You successfully destroyed all enemy ships. Thank you for playing." << endl;
        spaceConsole(1);
//        hashtagConsole(30);
//        spaceConsole(1);
    }


};






int main() {
    srand(time(0)); //initializing the randomizer
    displayTitle();
    //set up two Players: (player and cpu) and set up each's board
    Player player(false); //creating player and cpu object
    Player cpu(true);

    //start turn based/game loop
    do {
        spaceConsole(30);
        //first display the board; cpu board on top and player board under
        cout << "The enemy has " << cpu.getNumOfShips() << " ship(s) left." << endl;
        cpu.displayBoard();
        spaceConsole(1);
        player.displayBoard();
        spaceConsole(1);
        cout << "You have " << player.getNumOfShips() << " ship(s) left" << endl;
        //ask player to attack
        player.doTurn(&cpu);
        //let cpu do its thing
        cpu.doTurn(&player);

    } while(player.getNumOfShips() > 0 && cpu.getNumOfShips() > 0);

    //check winner + print results
    if (cpu.getNumOfShips() == 0) { //if player wins
        spaceConsole(50);
        hashtagConsole(120);
        winText();
        hashtagConsole(120);
        //spaceConsole(1);
        cout << "CPU Board:" << endl;
        cpu.displayBoard();
        spaceConsole(1);
        player.displayBoard();
        cout << "Your Board:" << endl;
        player.displayWinScreen();
    }
    else if (player.getNumOfShips() == 0) { //if cpu wins
        spaceConsole(50);
        hashtagConsole(120);
        loseText();
        hashtagConsole(120);
        //spaceConsole(1);
        cout << "CPU Board:" << endl;
        cpu.displayBoard();
        spaceConsole(1);
        player.displayBoard();
        cout << "Your Board:" << endl;
        player.displayLoseScreen();
    }



}




