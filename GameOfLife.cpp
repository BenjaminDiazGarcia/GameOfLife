#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

// The "real" size is (N-2)*(N-2)
const int N = 27;

using namespace std;

bool** initialize();
void printBoard(bool**);
void deleteAll(bool**);
void copyBoard(bool**, bool**);
void determineCurrentState(bool**);
bool** readFile();

int main() {
	unsigned cells = 0;
    char ans;
    bool** board = nullptr;
    int n = 0;
    cout << "Do you wanna read a file? (y/n): ";
    cin >> ans;
    
    if (ans == 'y'){
        board = readFile();
        printBoard(board);
    } else {
        board = initialize();
        cout << "Enter the number of cells: ";
        cin >> cells;

        for (int i = 0; i < cells; ++i) {
            int x = 0;
            int y = 0;
            cout << "Enter coordinates of cell (x, y): ";

            cin >> x; cin >> y;
            board[y+1][x+1] = true;
            printBoard(board);
        }
    }
    
    char check;
    do {
        cout << "This is the initial state. Do you wanna start? (y/n)" << endl;
        cin >> check;
    } while (check != 'y' && check != 'n');
    
    if (check == 'y'){
        
        while (true) {
            determineCurrentState(board);
            printBoard(board);
            cout << "\033[2J";
            usleep(200000);
        }
        
    } else {
        cout << "Bye :)" << endl;
    }
    
    deleteAll(board);
	return 0;
}

bool** initialize() {
    bool** array2D = nullptr;
    array2D = new bool*[N];
    for (int h = 0; h < N; ++h) {
        array2D[h] = new bool[N];
        for (int w = 0; w < N; ++w) {
            array2D[h][w] = false;
        }
    }

    return array2D;
}

void printBoard(bool** currentBoard) {
	for (int i = 1; i < N-1; ++i) {
		for (int j = 1; j < N-1; ++j) {
			cout << setw(3) << currentBoard[i][j] << " ";
		}
		cout << endl;
	}
}

void deleteAll(bool** currentBoard) {
    for (int h = 0; h < N; ++h) {
      delete [] currentBoard[h];
    }
    delete [] currentBoard;
}

void copyBoard(bool** currentBoard, bool** copyBoard) {
    for (int h = 0; h < N; ++h) {
        for (int w = 0; w < N; ++w) {
            copyBoard[h][w] = currentBoard[h][w];
        }
    }
}

void determineCurrentState(bool** currentBoard) {
    auto board2 = initialize();
    // Analyze the current state (board2) and edit the actual board (currentBoard)
    copyBoard(currentBoard, board2);
    
    //Mario Talevski's code (1)
    for (int i = 1; i < N-1; ++i) {
        for (int j = 1; j < N-1; ++j) {
            int alive = 0;
            for(int c = -1; c < 2; c++) {
                for(int d = -1; d < 2; d++) {
                    if(!(c == 0 && d == 0)) {
                        if(board2[i+c][j+d]) {
                           ++alive;
                       }
                    }
                }
            }
            if(alive < 2) {
                currentBoard[i][j] = false;
            } else if(alive == 3) {
                currentBoard[i][j] = true;
            } else if(alive > 3) {
                currentBoard[i][j] = false;
            }
            
        }
    }
    
    
    deleteAll(board2);
}

bool** readFile(){
    auto board = initialize();
    string fileName;
    char separador = ' ';
    Start:
    cout << "Enter a valid file name: ";
    cin >> fileName;
    ifstream check(fileName);
    if (check.fail())
        goto Start;
    
    string line;
    string sline;
    
    getline(check, line);
    sline = line;
    
    int cells = stoi(sline);
    
    for (int i = 0; i < cells; ++i) {
        getline(check, line);
        int x = 0;
        int y = 0;
        string value;
        int value_;
        vector<int> coordinates;
        
        for (size_t p = 0, q = 0, j = 0; j < 2; p = q, j++) {
            value = line.substr(p + (p != 0), (q = line.find(separador, p + 1)) - p - (p != 0));
            value_ = stoi(value);
            coordinates.push_back(value_);
        }
        
        x = coordinates[0];
        y = coordinates[1];
        
        board[y+1][x+1] = true;
    }
    
    return board;
}




/*
 (1) https://github.com/MarioTalevski/game-of-life
 */
