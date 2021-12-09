// ECCS 1611 - Programming 1 - Fall Semester 2021
// Machine Problem 4 (MP4) - Rubber Ducks vs. Peeps!
// 
// MP4.cpp
// 
// Last Updated: December 9, 2021
// Hailey M. Wendt
// 
// Some code was provided by Dr. Estell
// 
// This assignment is a text-based adventure game with 3 rounds. In the odd number rounds (1 & 3), 
// the user will be playing the role of the Rubber Ducks. In round 2, the tables will be turned, 
// and the user will be playing the role of the Snow Stealer Peeps. The goal of the game is to track
// down and defeat the Snow Stealing Peeps, who are using magic to make Snow Beasts, in a cave that 
// contains 20 different rooms.

// List of Concepts Used in Code:
// 1. Function Definition with a Vector as a Parameter and Function Call (line 366, 117) (3 pts.)
// 2. File as Input (Reading) (line 385) (7 pts.)
// 3. Vector (line 73) (3 pts.)
// 4. 2D Array / Vector (line 44) (3 pts.)
// 5. Assignment Statement (line 69) (1 pt)
// 6. While Loop (line 92) (5 pts.)
// 7. If Statement (line 97) (3 pts.)
// Total Points: 25 pts.

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

// Function Prototypes
vector<int> getAdjacentRooms(vector<vector<int>> map, int currentRoom);
bool isValidMove(int to, vector<int> connections);
void printCurrentRoom(int room);
void printAdjacentRooms(vector<int> rooms);
void instructions();
void pressEnterToContinue(void);
bool twoSteps(vector<int> rooms, int randomPeeps, vector<vector<int>> map, int currentRoom);

int main() {
    // Vector for adjacent rooms
    vector<vector<int>> dodecahedron{ // Concept: 2D Array / Vector
        {-1, -1, -1},  // no node 0...
        { 2,  5,  8},  // node 1
        { 1,  3, 10},  // node 2
        { 2,  4, 12},  // node 3
        { 3,  5, 14},  // node 4
        { 1,  4,  6},  // node 5
        { 5,  7, 15},  // node 6
        { 6,  8, 17},  // node 7
        { 1,  7,  9},  // node 8
        { 8, 10, 18},  // node 9
        { 2,  9, 11},  // node 10
        {10, 12, 19},  // node 11
        { 3, 11, 13},  // node 12
        {12, 14, 20},  // node 13
        { 4, 13, 15},  // node 14
        { 6, 14, 16},  // node 15
        {15, 17, 20},  // node 16
        { 7, 16, 18},  // node 17
        { 9, 17, 19},  // node 18
        {11, 18, 20},  // node 19
        {13, 16, 19}   // node 20
    };

    // Initialize variables
    int startRoom = 1; // Concept: Assignment Statement
    int currentRoom;
    int enteredRoom;
    char userInput = ' ';
    vector<int> adjacentRooms; // Concept: Vector
    int round = 1;
    int scorePeeps = 0;
    int scoreDucks = 0;
    srand(time(NULL));
    bool twoStep = false;

    // Initial random locations for peeps, vultures, taffy pit, and ducks
    int randomPeeps = rand() % 20 + 1;
    int randomVultures = rand() % 20 + 1;
    int randomTaffy = rand() % 20 + 1;
    int randomDucks = rand() % 20 + 1;

    // Display instructions
    instructions();

    // Round 1
    cout << endl << "Round 1:" << endl;
    currentRoom = startRoom;
    while (round == 1) { // Concept: While Loop
        adjacentRooms = getAdjacentRooms(dodecahedron, currentRoom);
        twoStep = twoSteps(adjacentRooms, randomPeeps, dodecahedron, currentRoom);

        // Displays any location information
        if (randomPeeps == adjacentRooms[0] || randomPeeps == adjacentRooms[1] || randomPeeps == adjacentRooms[2]) { // Concept: If Statement
            cout << "I hear footsteps!" << endl;
        }
        if (twoStep == true) {
            cout << "I smell marshmallows!" << endl;
        }
        if (currentRoom == randomVultures) {
            enteredRoom = rand() % 20 + 1;
            cout << "Vultures transport you to " << enteredRoom << endl;
            currentRoom = enteredRoom;
        }
        if (currentRoom == randomTaffy) {
            cout << "lol you lost round 1." << endl;
            round = 2;
        }

        //Displays current location
        printCurrentRoom(currentRoom);

        // Displays adjacent rooms
        printAdjacentRooms(adjacentRooms); // Concept: Function Definition with a Vector as a Parameter and Function Call

        // Displays menu to choose move(M), exit(E), instructions(I), and candy cane arrow(C)
        cout << "Move, Exit, Instructions, or Candy Cane: ";
        cin >> userInput;
        if (userInput == 'M') {
            printCurrentRoom(currentRoom);
            printAdjacentRooms(adjacentRooms);
            cout << "Where to? ";
            cin >> enteredRoom;
            if (cin.fail()) {
                cout << "SORRY: Invalid input, please try again." << endl;
                break;
            }
            if (isValidMove(enteredRoom, getAdjacentRooms(dodecahedron, currentRoom))) {
                currentRoom = enteredRoom;
            }
            else {
                cout << "You can't get there from here." << endl;
                cout << endl;
            }
        }
        else if (userInput == 'E') {
            cout << "Thanks for playing!" << endl;
            break;
        }
        else if (userInput == 'I') {
            instructions();
        }
        else if (userInput == 'C') {
            cout << "Room to aim at? ";
            cin >> enteredRoom;
            if (enteredRoom == randomPeeps) {
                cout << "Great Job! You found the enemy!" << endl;
                cout << "You win this round:)" << endl;
                round = 2;
                scoreDucks = 1;
            }
            else {
                cout << "You suck. ROUND 1 OVER:)" << endl;
                round = 2;
                break;
            }
        }
    }

    // Re-randomize the locations for the taffy pit and vultures for Round 2
    randomTaffy = rand() % 20 + 1;
    randomVultures = rand() % 20 + 1;

    // Round 2
    cout << endl << "Round 2:" << endl;
    currentRoom = startRoom;
    while (round == 2) {
        adjacentRooms = getAdjacentRooms(dodecahedron, currentRoom);

        // Displays any location information
        if (randomDucks == adjacentRooms[0] || randomDucks == adjacentRooms[1] || randomDucks == adjacentRooms[2]) {
            cout << "I hear footsteps!" << endl;
        }
        if (currentRoom == randomVultures) {
            enteredRoom = rand() % 20 + 1;
            cout << "Vultures transport you to " << enteredRoom << endl;
            currentRoom = enteredRoom;
        }
        if (currentRoom == randomTaffy) {
            cout << "lol you lost round 2." << endl;
            round = 3;
        }

        //Displays current location
        printCurrentRoom(currentRoom);

        // Displays adjacent rooms
        printAdjacentRooms(adjacentRooms);

        // Displays menu to choose move(M), exit(E), instructions(I), and sword toothpick(S)
        cout << "Move, Exit, Instructions, or Sword Toothpick: ";
        cin >> userInput;
        if (userInput == 'M') {
            printCurrentRoom(currentRoom);
            printAdjacentRooms(adjacentRooms);
            cout << "Where to? ";
            cin >> enteredRoom;
            if (cin.fail()) {
                cout << "SORRY: Invalid input, please try again." << endl;
                break;
            }
            if (isValidMove(enteredRoom, getAdjacentRooms(dodecahedron, currentRoom))) {
                currentRoom = enteredRoom;
            }
            else {
                cout << "You can't get there from here." << endl;
                cout << endl;
            }
        }
        else if (userInput == 'E') {
            cout << "Thanks for playing!" << endl;
            break;
        }
        else if (userInput == 'I') {
            instructions();
        }
        else if (userInput == 'S' || randomDucks == adjacentRooms[0] || randomDucks == adjacentRooms[1] || randomDucks == adjacentRooms[2]) {
            cout << "Room to aim at? ";
            cin >> enteredRoom;
            if (enteredRoom == randomDucks || randomDucks == adjacentRooms[0] || randomDucks == adjacentRooms[1] || randomDucks == adjacentRooms[2]) {
                cout << "Great Job! You found the enemy!" << endl;
                cout << "You win this round:)" << endl;
                round = 3;
                scorePeeps = 1;
            }
            else {
                cout << "You suck. ROUND 2 OVER:)" << endl;
                round = 3;
                break;
            }
        }
    }

    // Re-randomize the locations for the taffy pit, vultures, and peeps for Round 3
    randomTaffy = rand() % 20 + 1;
    randomVultures = rand() % 20 + 1;
    randomPeeps = rand() % 20 + 1;

    // Round 3
    cout << endl << "Round 3:" << endl;
    currentRoom = startRoom;
    while (round == 3) {
        adjacentRooms = getAdjacentRooms(dodecahedron, currentRoom);
        twoStep = twoSteps(adjacentRooms, randomPeeps, dodecahedron, currentRoom);

        // Displays any location information
        if (randomPeeps == adjacentRooms[0] || randomPeeps == adjacentRooms[1] || randomPeeps == adjacentRooms[2]) {
            cout << "I hear footsteps!" << endl;
        }
        if (twoStep == true) {
            cout << "I smell marshmallows!" << endl;
        }
        if (currentRoom == randomVultures) {
            enteredRoom = rand() % 20 + 1;
            cout << "Vultures transport you to " << enteredRoom << endl;
            currentRoom = enteredRoom;
        }
        if (currentRoom == randomTaffy) {
            cout << "lol game over." << endl;
            break;
        }

        //Displays current location
        printCurrentRoom(currentRoom);

        // Displays adjacent rooms
        printAdjacentRooms(adjacentRooms);

        // Displays menu to choose move(M), exit(E), instructions(I), and pastry torch(F)
        cout << "Move, Exit, Instructions, or Pastry Torch: ";
        cin >> userInput;
        if (userInput == 'M') {
            printCurrentRoom(currentRoom);
            printAdjacentRooms(adjacentRooms);
            cout << "Where to? ";
            cin >> enteredRoom;
            if (cin.fail()) {
                cout << "SORRY: Invalid input, please try again." << endl;
                break;
            }
            if (isValidMove(enteredRoom, getAdjacentRooms(dodecahedron, currentRoom))) {
                currentRoom = enteredRoom;
            }
            else {
                cout << "You can't get there from here." << endl;
                cout << endl;
            }
        }
        else if (userInput == 'E') {
            cout << "Thanks for playing!" << endl;
            break;
        }
        else if (userInput == 'I') {
            instructions();
        }
        else if (userInput == 'F') {
            cout << "Room to aim at? ";
            cin >> enteredRoom;
            if (enteredRoom == randomPeeps || randomPeeps == adjacentRooms[0] || randomPeeps == adjacentRooms[1] || randomPeeps == adjacentRooms[2]) {
                cout << "Great Job! You found the enemy!" << endl;
                cout << "You win this round:)" << endl;
                break;
                scoreDucks += 1;
            }
            else {
                cout << "You suck. GAME OVER:)" << endl;
                break;
            }
        }
    }

    //Determining the winner of the game
    if (scorePeeps > scoreDucks) {
        cout << endl << "Peeps win:(" << endl;
    }
    else if (scoreDucks > scorePeeps) {
        cout << endl << "Ducks win:)" << endl;
    }
    else {
        cout << endl << "Draw. Neither win." << endl;
    }
    pressEnterToContinue();
    return 0;
}

/**
getAdjacentRooms - lets you know what rooms you can directly move to from the current room.
@param map - 2-D vector of integers containing the game's room map
@param currentRoom - integer value indicating one's current location
@return integer vector containing list of rooms that it's legal to move to
*/
vector<int> getAdjacentRooms(vector<vector<int>> map, int currentRoom) {
    return map[currentRoom];
}

/**
isValidMove - given a room number, can one directly move there from where they currently are?
@param to - proposed room to move to
@param connections - list of rooms adjacent to the current room
@return true if specific room is adjacent, false otherwise
*/
bool isValidMove(int to, vector<int> connections) {
    for (int i = 0; i < connections.size(); i++) {
        if (to == connections[i]) {
            return true;
        }
    }
    return false;
}

/**
printCurrentRoom - display message containing current room number.
@param room - current room number
*/
void printCurrentRoom(int room) {
    cout << "You are in room " << room << endl;
}

/**
printAdjacentRooms - display message listing those rooms adjacent to the current room.
@param rooms - list of rooms adjacent to the current room.
*/
void printAdjacentRooms(vector<int> rooms) { // Concept: Function Definition with a Vector as a Parameter and Function Call
    cout << "Tunnels lead to rooms ";
    for (int i = 0; i < rooms.size(); i++) {
        cout << rooms[i];
        if (i < rooms.size() - 1) {
            cout << ", ";
        }
        else {
            cout << endl;
        }
    }
}

/**
instructions - displays instructions
*/
void instructions() {
    char ch;
    fstream in_file;
    in_file.open("MP4-GameInstructions.txt"); // Concept: File as Input (Reading)
    while (in_file.eof() == 0) {
        in_file.get(ch);
        cout << ch;
    }
    in_file.close();
    cout << endl;
}

/**
pressEnterToContinue: used to keep the console window open long enough to see your program's output.
*/
void pressEnterToContinue(void) {
    char c;
    cout << "Press Enter to continue...";
    cin.ignore(1024, '\n');
    do { cin.get(c); } while (c != '\n' && c != EOF);
    return;
}

/**
twoSteps - identifies rooms that are "two steps" away from current room
@param rooms - list of rooms adjacent to the current room
@param randomPeeps - random room that peeps are in
@param map - 2-D vector of integers containing the game's room map
@param currentRoom - integer value indicating one's current location
@return false if room is not "two steps" away from current room
*/
bool twoSteps(vector<int> rooms, int randomPeeps, vector<vector<int>> map, int currentRoom) {
    rooms = getAdjacentRooms(map, currentRoom);
    for (int i = 0; i < rooms.size(); i++) {
        vector<int> temp = getAdjacentRooms(map, rooms[i]);
        if (temp[0] == randomPeeps) {
            return true;
        }
        if (temp[1] == randomPeeps) {
            return true;
        }
        if (temp[2] == randomPeeps) {
            return true;
        }
    }
    return false;
}
