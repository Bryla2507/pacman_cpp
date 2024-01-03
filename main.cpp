#include <iostream>
#include <curses.h>
#include <windows.h>

// Constants for the game
const int BOARD_WIDTH = 29;
const int BOARD_HEIGHT = 31;
const char PACMAN = 'C';
const char WALL = '#';
const char COIN = '.';
const char EMPTY = ' ';

int SCORE = 0;
//Starter position for pacman on board
int pacmanX = 13, pacmanY = 23;



//game board
char board[BOARD_HEIGHT][BOARD_WIDTH] = {
    "############################",
    "#............##............#",
    "#.####.#####.##.####.#####.#",
    "#.#  #.#   #.##.#  #.#   #.#",
    "#.####.#####.##.####.#####.#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#......##....##....##......#",
    "######.##### ## #####.######",
    "     #.##### ## #####.#     ",
    "     #.##          ##.#     ",
    "     #.## ######## ##.#     ",
    "######.## #      # ##.######",
    "      .   #      #   .      ",
    "######.## #      # ##.######",
    "     #.## ######## ##.#     ",
    "     #.##          ##.#     ",
    "     #.## ######## ##.#     ",
    "######.## ######## ##.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#...##................##...#",
    "###.##.##.########.##.##.###",
    "###.##.##.########.##.##.###",
    "#......##....##....##......#",
    "#.##########.##.##########.#",
    "#.##########.##.##########.#",
    "#..........................#",
    "############################",
    
};

void drawBoard() {
    start_color();

    // Color pair for Pacman
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    // Color pair for board 
    init_pair(2, COLOR_BLUE, COLOR_BLACK); 

    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (y == pacmanY && x == pacmanX) {
                attron(COLOR_PAIR(1));
                mvaddch(y, x, PACMAN);
                attroff(COLOR_PAIR(1));
            } else if (board[y][x] == WALL) {
                attron(COLOR_PAIR(2));
                mvaddch(y, x, WALL);
                attroff(COLOR_PAIR(2));
            } else if (board[y][x] == COIN) {
                mvaddch(y, x, COIN);
            } else {
                mvaddch(y, x, EMPTY);
            }
        }
    }
    mvaddch(BOARD_HEIGHT+1, 0, SCORE);
}

int main() {
    //setting console window size
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, r.left, r.top, 400, 800, TRUE); // 400 width, 800 height (in pixels)
    
    //pdcurses settings
    initscr(); // Initialize PDCurses
    noecho(); // Don't echo user input
    curs_set(0); // Hide cursor

    while (true) {
        clear();
        drawBoard();
        std::cout<<SCORE;
        refresh();

        char userInput = getch();
        switch (userInput) {
            case ('w'):
                if (board[pacmanY - 1][pacmanX] != WALL) {
                    if (board[pacmanY - 1][pacmanX] == COIN)
                    {
                        ++SCORE;
                    }
                    
                    --pacmanY;
                }
                break;
            case ('s'):
                if (board[pacmanY + 1][pacmanX] != WALL) {
                    if (board[pacmanY + 1][pacmanX] == COIN)
                    {
                        ++SCORE;
                    }
                    ++pacmanY;
                }
                break;
            case ('a'):
                if (board[pacmanY][pacmanX - 1] != WALL) {
                    if (board[pacmanY][pacmanX - 1] == COIN)
                    {
                        ++SCORE;
                    }
                    --pacmanX;
                }
                break;
            case ('d'):
                if (board[pacmanY][pacmanX + 1] != WALL) {
                    if (board[pacmanY][pacmanX + 1] == COIN)
                    {
                        ++SCORE;
                    }
                    ++pacmanX;
                }
                break;
            case ('q'):
                endwin(); // End PDCurses
                return 0;
        }
    }

    return 0;
}