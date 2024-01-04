#include <iostream>
#include <curses.h>
#include <windows.h>

// Constants and variables for the game
const int BOARD_WIDTH = 29;
const int BOARD_HEIGHT = 31;
const char PACMAN = 'C';
const char WALL = '#';
const char COIN = '.';
const char EMPTY = ' ';
const char POWER_UP = 'o';
const char GHOST_GATE = '-';
const char ghost[4] = {'Y','Y','Y','Y'};
const int defaultGhostPositionX = 13, defaultGhostPositionY = 14;

int SCORE = 0;
int LIFES = 3;
int powerUpped = false;

//Starter position for pacman and ghosts on board
int pacmanX = 13, pacmanY = 23;
int ghost1X = 11, ghost1Y = 14;
int ghost2X = 13, ghost2Y = 14;
int ghost3X = 14, ghost3Y = 14;
int ghost4X = 16, ghost4Y = 14;




//game board
char board[BOARD_HEIGHT][BOARD_WIDTH] = {
    "############################",
    "#............##............#",
    "#.####.#####.##.####.#####.#",
    "#o#  #.#   #.##.#  #.#   #o#",
    "#.####.#####.##.####.#####.#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#......##....##....##......#",
    "######.##### ## #####.######",
    "     #.##### ## #####.#     ",
    "     #.##          ##.#     ",
    "     #.## ###--### ##.#     ",
    "######.## #      # ##.######",
    "      .   #Y YY Y#   .      ",
    "######.## #      # ##.######",
    "     #.## ######## ##.#     ",
    "     #.##          ##.#     ",
    "     #.## ######## ##.#     ",
    "######.## ######## ##.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#o..##.......C........##..o#",
    "###.##.##.########.##.##.###",
    "###.##.##.########.##.##.###",
    "#......##....##....##......#",
    "#.##########.##.##########.#",
    "#.##########.##.##########.#",
    "#..........................#",
    "############################",
    
};

void powerUpping() {
    SCORE = SCORE + 20;
    powerUpped = true;
}

void collision(int ghostNumber) {
    if (powerUpped == false)
    {
        --LIFES;
        if (LIFES == 0)
        {
            //todo you lost
        }
        else {
            int pacmanX = 13, pacmanY = 23;
            int ghost1X = 11, ghost1Y = 14;
            int ghost2X = 13, ghost2Y = 14;
            int ghost3X = 14, ghost3Y = 14;
            int ghost4X = 16, ghost4Y = 14;
        }
        
    }
    else {
        SCORE = SCORE + 50;
        ghostX[ghostNumber] = defaultGhostPositionX;
        ghostY[ghostNumber] = defaultGhostPositionY;
    }
    
}

void moveGhosts() {
    //todo
}

void drawBoard() {
    start_color();

    // Color pair for Pacman
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    // Color pair for board 
    init_pair(2, COLOR_BLUE, COLOR_BLACK); 
    //Color pair for ghosts
    init_pair(3, COLOR_RED, COLOR_BLACK);

    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {

            //drawing pacman
            if (y == pacmanY && x == pacmanX) {
                attron(COLOR_PAIR(1));
                mvaddch(y, x, PACMAN);
                attroff(COLOR_PAIR(1));
            }

            //drawing everything else
            else {
                switch (board[y][x])
                {
                case WALL:
                    attron(COLOR_PAIR(2));
                    mvaddch(y, x, WALL);
                    attroff(COLOR_PAIR(2));
                    break;
                case GHOST_GATE:
                    attron(COLOR_PAIR(2));
                    mvaddch(y, x, GHOST_GATE);
                    attroff(COLOR_PAIR(2));
                    break;
                case GHOST_1:
                    attron(COLOR_PAIR(3));
                    mvaddch(y, x, GHOST_1);
                    attroff(COLOR_PAIR(3));
                    break;
                case COIN:
                    mvaddch(y, x, COIN);
                    break;
                case POWER_UP:
                    mvaddch(y, x, POWER_UP);
                    break;
                default:
                    mvaddch(y, x, EMPTY);
                    break;
                }
            }
            
        }
    }
    
    // print score and lifes remaining below board
    mvprintw(BOARD_HEIGHT+1, 0, "Score: %d", SCORE);

    for (size_t i = 0; i < LIFES; i++)
    {
        attron(COLOR_PAIR(1));
        mvaddch(BOARD_HEIGHT+1, 15+i, PACMAN);
        attroff(COLOR_PAIR(1));
    }
    
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

        //drawing current game state
        clear();
        drawBoard();
        refresh();

        //moving pacman
        char userInput = getch();

        switch (userInput) {
            case ('w'):
                if (board[pacmanY - 1][pacmanX] != WALL && board[pacmanY - 1][pacmanX] != GHOST_GATE) {
                    if (board[pacmanY - 1][pacmanX] == COIN)
                    {
                        ++SCORE;
                        board[pacmanY - 1][pacmanX] = EMPTY;
                    }
                    else if (board[pacmanY - 1][pacmanX] == POWER_UP)
                    {
                        powerUpping();
                        board[pacmanY - 1][pacmanX] = EMPTY;
                    }
                    --pacmanY;
                }
                break;


            case ('s'):
                if (board[pacmanY + 1][pacmanX] != WALL && board[pacmanY + 1][pacmanX] != GHOST_GATE) {
                    if (board[pacmanY + 1][pacmanX] == COIN)
                    {
                        ++SCORE;
                        board[pacmanY + 1][pacmanX] = EMPTY;
                    }
                    else if (board[pacmanY + 1][pacmanX] == POWER_UP)
                    {
                        powerUpping();
                        board[pacmanY + 1][pacmanX] = EMPTY;
                    }
                    ++pacmanY;
                }
                break;


            case ('a'):
                if (board[pacmanY][pacmanX - 1] != WALL && board[pacmanY][pacmanX - 1] != GHOST_GATE) {
                    if (board[pacmanY][pacmanX - 1] == COIN)
                    {
                        ++SCORE;
                        board[pacmanY][pacmanX - 1] = EMPTY;
                    }
                    else if (board[pacmanY][pacmanX - 1] == POWER_UP)
                    {
                        powerUpping();
                        board[pacmanY][pacmanX - 1] = EMPTY;
                    }
                    --pacmanX;
                }
                break;


            case ('d'):
                if (board[pacmanY][pacmanX + 1] != WALL && board[pacmanY][pacmanX + 1] != GHOST_GATE) {
                    if (board[pacmanY][pacmanX + 1] == COIN)
                    {
                        ++SCORE;
                        board[pacmanY][pacmanX + 1] = EMPTY;
                    }
                    else if (board[pacmanY][pacmanX + 1] == POWER_UP)
                    {
                        powerUpping();
                        board[pacmanY][pacmanX + 1] = EMPTY;
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