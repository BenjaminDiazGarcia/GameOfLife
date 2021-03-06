//
//  GameOfLife.h
//  
//
//  Created by Benjamin Diaz on 12/30/19.
//

#ifndef GameOfLife_h
#define GameOfLife_h

#include <iostream>

using namespace std;

class GameOfLife {
    // The "real" size is (N-2)*(N-2)
    const int N = 42;

    // Time in microseconds (1 second = 1000000 microseconds)
    const int Time = 250000;
    
public:
    
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
                if (currentBoard[i][j]){
                    cout << setw(1) << "\x1b[47m   \x1b[0m";
                } else {
                    cout << setw(1) << "\x1b[40m   \x1b[0m";
                }
            }
            cout << endl;
        }
        cout << "\n\nPress Ctrl + C to exit" << endl;
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
    
    void startGame(){
        unsigned cells = 0;
        char ans;
        char c;
        bool** board = nullptr;
        int n = 0;
        cout << "Do you wanna read a file? (y/n): ";
        cin >> ans;
        
        c = static_cast<char>(tolower(static_cast<unsigned char>(ans)));
        
        if (c == 'y'){
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
            c = static_cast<char>(tolower(static_cast<unsigned char>(check)));
        } while (c != 'y' && c != 'n');
        
        if (c == 'y'){
            
            while (true) {
                determineCurrentState(board);
                printBoard(board);
                cout << "\033[2J";
                usleep(Time);
            }
            
        } else {
            cout << "Bye :)" << endl;
        }
        
        deleteAll(board);
        
    }
    
    
    
};

/*
(1) https://github.com/MarioTalevski/game-of-life
*/

#endif /* GameOfLife_h */
