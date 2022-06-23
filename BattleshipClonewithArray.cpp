#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <chrono>

using namespace std;

class Battleship
{
private:
    const static int rowsX = 10;
    const static int columnsY = 10;
    int co0rd;
    int maximumShips;
    int matrixBoard[rowsX][columnsY];

    struct coordPair {
        int xCoord;
        int yCoord;
    };
public:
    Battleships() {
        co0rd = 0;
        maximumShips = 10;
    }
    //method to clear the board of ships(sets everything to 0)
    void clearGrid() {
        for (int x = 0; x < rowsX; x++) {
            for (int y = 0; y < columnsY; y++) {
                matrixBoard[y][x] = 0;
            }
        }
    }
    //method to show the grid
    void showGrid() {
        cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
        cout << "-----------------------" << endl;
        for (int x = 0; x < rowsX; x++)
        {
            cout << co0rd << "| ";
            co0rd++;
            for (int y = 0; y < rowsX; y++)
            {
                cout << matrixBoard[x][y] << " ";
            }
            cout << endl;
        }
    }
    //method for finding number of ships
    int numberOfShips() {
        int c = 0;
        for (int x = 0; x < rowsX; x++)
        {
            for (int y = 0; y < columnsY; y++)
            {
                if (matrixBoard[x][y] == 1)
                {
                    c++;
                }
            }
        }
        return c;
    }
    //method to set ships onto the board
    void setShips() {
        int ships = 0
             while (ships < maximumShips) {
                int xPosition = rand() % 10;
                int yPosition = rand() % 10;

                if (matrixBoard[xPosition][Y[yPosition] != 1]) {
                    ships++
                        matrix[xPosition][yPosition] = 1;
                }
            }
    }
    //method to attack the target coordinates
    bool attack(int newX, int newY) {
        if (matrixBoard[newX][newY] == 1) {
            matrixBoard[newX][newY] == 2;
            return true;
        }
        else {
            return false;
        }
    }
    //method to scan for a ship
    void battleScan() {
        coordPair pair;
        for (int x = 0; x < rowsX; x++) {
            for (int y = 0; y < columnsY; y++) {
                if (matrixBoard[x][y] == 1) {
                    pair.xCoord = x;
                    pair.yCoord = y;
                    return pair;
                }
            }
        }
    }


    class Boards // makes another class called boards, will be used to initiate the game boards the user can see
    {
    private:
        const static int rows = 10; // makes constants called rows and columns set to 10; to make the game board matrix
        const static int columns = 10;
        char grid[rows][columns]; // makes an multidimensional array of data type 'char'
    public:
        void MakeBoards() // declares a function to make the game boards
        {
            for (int x = 0; x < rows; x++) // starts a for loop
            {
                for (int y = 0; y < columns; y++) // nested for loop
                {
                    grid[x][y] = '-'; // sets the element in the position to a '-'
                }
            }
        }

        void updateBoards(bool i, int x, int y) // makes a function to update the game boards, takes 3 paramaters. a boolean, and two integers
        {
            int xPos = x; // sets two variables equal to the int values passed in
            int yPos = y;

            if (i == true) // checks if i is equal to 'true'
            {
                grid[xPos][yPos] = 'Y'; // sets the element in the position to 'Y'
            }
            else
            {
                grid[xPos][yPos] = 'N'; // sets the element in the position to 'N'
            }
        }

        void PrintBoards() // makes a function to print the boards
        {
            int amt = 0; // sets an int called amt to 0

            cout << "  0 1 2 3 4 5 6 7 8 9" << endl; // prints the top line of coordinates
            for (int x = 0; x < rows; x++) { // for loop
                cout << amt << " "; // outputs the amount variable to the console + a space
                amt++; // increments amt
                for (int y = 0; y < columns; y++) { // nested for loop
                    cout << grid[x][y] << " "; // outputs the element of the grid to the console, plus a space
                }
                cout << endl; // outputs an endline character
            }
        }
    };

    int main() {
        char restart;

        do {
            srand((unsigned)time(NULL));
            setConsoleTitle(_T("Battleships"));
            Battleship human;
            Battleship cpu;

            Boards humanBoard;
            Boards cpuBoard;

            human.clearGrid();
            human.setShips();

            cpu.clearGrid();
            cpu.setShips();

            humanBoard.MakeBoards();
            cpuBoard.MakeBoards();

            cout << "Your board: " << endl;
            humanBoard.PrintBoards();
            cout << "the Computer's board" << endl;
            cpuBoard.PrintBoards();

            int position1, position2;
            char which;
            int found = 0;
            int toGo = 10;

            int cpuFound = 0;
            int cpuToGet = 10;

            bool isTrueHuman;
            bool isTrueCPU;

            int choice;
            coordPair enemyShipCoord;

            while (found < 10 || cpuFound < 10) {
                int cpuX = rand() % 10;
                int cpuY = rand() % 10;

                if (cpu.attack(cpuX, cpuY)) {
                    isTrueCPU = true;
                    cpuFound++;
                    cpuToGet--;
                    cout << "The computer has destroyed your battleship at: " << "(" << cpuX << ", " << cpuY << ")" << endl;
                }
                else {
                    isTrueCPU = false;
                    cout << "The computer did not find a battleship this time" << endl;
                }
            }

            while (position1 > 9 || position2 > 9)
            {
                if (cpuFound == 10 || found == 10) {
                    break;
                }
                cout << "Choose whether you want to (1)attack or (2)scan (input the integer):" << endl;
                cin >> choice;
                switch (choice) {
                case 1:
                    cout << "Please input where you want to attack on the grid: ";

                    cin >> position1 >> position2;

                    while (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "not int, try again: "; cin >> position1 >> position2;
                    }

                    if (human.attack(position1, position2))
                    {
                        isTrueHuman = true;
                        found++;
                        toGo--;
                        cout << "You have found: " << found << " battleships, you have: " << toGo << " to go" << endl;
                    }
                    else
                    {
                        isTrueHuman = false;
                        cout << "there is no ship at that position, keep trying" << endl;
                    }

                    break;
                case 2:
                    enemyShipCoord = battleScan();

                    cout << "There is an enemy ship at ()" << enemyShipCoord.xCoord << ", " << enemyShipCoord.yCoord << ")" << endl;
                    break;
                default:
                    cout << "not an option, please input an integer";
                    break;
                }

                cout << "There are: " << human.numberOfShips() << " left" << endl;
                cout << "would you like to surrender (y/n)?: "; cin >> which;

                system("CLS");

                humanBoard.updateBoards(isTrueHuman, position1, position2);
                cpuBoard.updateBoards(isTrueCPU, cpuX, cpuY);

                cout << "Your board: " << endl;
                humanBoard.PrintBoards();
                cout << "the Computer's board" << endl;
                cpuBoard.PrintBoards();

                if (which == "y") {
                    break;
                }
                else if (found == 10 || cpuFound == 10) {
                    break;
                }
            }

            cout << "game over" << endl;
            cout << "your grid: " << endl;
            cout << "The number 2 represents struck ships" << endl;
            human.showGrid();
            cout << "-------------------------------------" << endl;
            cout << "Computer's Grid" << endl;
            cpu.showGrid();

                ; cout << "Would you like to continue or exit (r/e);";
            cin >> restart;
        } while (restart == "r" || rerun == "R");

        return 0;
    }
};
