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
constexpr char ghost[4] = {'Y','G','R','U'};
const int defaultGhostPositionX = 13, defaultGhostPositionY = 14;

int SCORE = 0;
int LIFES = 3;
int turnsRemaining = 0;

//Starter position for pacman and ghosts on board
int pacmanX = 13, pacmanY = 23;
int ghostX[4] = {11, 13, 14, 16};
int ghostY[4] = {14, 14, 14, 14};



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
    turnsRemaining = 30;
}

void collision(int ghostNumber) {
    if (turnsRemaining <= 0)
    {
        --LIFES;
        if (LIFES == 0)
        {
            //todo you lost
        }
        else {
            pacmanX = 13, pacmanY = 23;
            ghostX[0] = 11;
            ghostX[1] = 13;
            ghostX[2] = 14;
            ghostX[3] = 16;
            ghostY[0] = 14;
            ghostY[1] = 14;
            ghostY[2] = 14;
            ghostY[3] = 14;
        }
        
    }
    else {
        SCORE = SCORE + 50;
        ghostX[ghostNumber] = defaultGhostPositionX;
        ghostY[ghostNumber] = defaultGhostPositionY;
    }
    
}

void moveGhosts(int ghostNumber) {

    int direction = rand() % 4;
            switch (direction) {
            case 0:
                if (board[ghostY[ghostNumber] - 1][ghostX[ghostNumber]] != WALL) {
                    --ghostY[ghostNumber];
                }
                break;
            case 1:
                if (board[ghostY[ghostNumber] + 1][ghostX[ghostNumber]] != WALL) {
                    ++ghostY[ghostNumber];
                }
                break;
            case 2:
                if (board[ghostY[ghostNumber]][ghostX[ghostNumber] - 1] != WALL) {
                    --ghostX[ghostNumber];
                }
                break;


            case 3:
                if (board[ghostY[ghostNumber]][ghostX[ghostNumber] + 1] != WALL) {
                    ++ghostX[ghostNumber];
                }
                break;
            }
}


void drawBoard() {
    start_color();

    // Color pair for Pacman
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    // Color pair for board 
    init_pair(2, COLOR_BLUE, COLOR_BLACK); 
    //Color pair for ghosts
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);

    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            
            //drawing pacman
            if (y == pacmanY && x == pacmanX) {
                attron(COLOR_PAIR(1));
                mvaddch(y, x, PACMAN);
                attroff(COLOR_PAIR(1));
            } 

            else if (turnsRemaining <= 0)
            {
                if (y == ghostY[0] && x == ghostX[0]) {
                attron(COLOR_PAIR(3));
                mvaddch(y, x, ghost[0]);
                attroff(COLOR_PAIR(3));
            } else if (y == ghostY[1] && x == ghostX[1]) {
                attron(COLOR_PAIR(3));
                mvaddch(y, x, ghost[1]);
                attroff(COLOR_PAIR(3));
            } else if (y == ghostY[2] && x == ghostX[2]) {
                attron(COLOR_PAIR(3));
                mvaddch(y, x, ghost[2]);
                attroff(COLOR_PAIR(3));
            } else if (y == ghostY[3] && x == ghostX[3]) {
                attron(COLOR_PAIR(3));
                mvaddch(y, x, ghost[3]);
                attroff(COLOR_PAIR(3));
            }
            
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
            else if (turnsRemaining > 0)
            {
                if (y == ghostY[0] && x == ghostX[0]) {
                attron(COLOR_PAIR(4));
                mvaddch(y, x, ghost[0]);
                attroff(COLOR_PAIR(4));
            } else if (y == ghostY[1] && x == ghostX[1]) {
                attron(COLOR_PAIR(4));
                mvaddch(y, x, ghost[1]);
                attroff(COLOR_PAIR(4));
            } else if (y == ghostY[2] && x == ghostX[2]) {
                attron(COLOR_PAIR(4));
                mvaddch(y, x, ghost[2]);
                attroff(COLOR_PAIR(4));
            } else if (y == ghostY[3] && x == ghostX[3]) {
                attron(COLOR_PAIR(4));
                mvaddch(y, x, ghost[3]);
                attroff(COLOR_PAIR(4));
            }

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

    srand(time(0));
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
                    moveGhosts(0);
                    moveGhosts(1);
                    moveGhosts(2);
                    moveGhosts(3);
                    --pacmanY;
                    --turnsRemaining;
                    if (ghostX[0] == pacmanX && ghostY[0] == pacmanY)
                    {
                        collision(0);
                    }
                    else if (ghostX[1] == pacmanX && ghostY[1] == pacmanY)
                    {
                        collision(1);
                    } 
                    else if (ghostX[2] == pacmanX && ghostY[2] == pacmanY)
                    {
                        collision(2);
                    }
                    else if (ghostX[3] == pacmanX && ghostY[3] == pacmanY)
                    {
                        collision(3);
                    }
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
                    moveGhosts(0);
                    moveGhosts(1);
                    moveGhosts(2);
                    moveGhosts(3);
                    ++pacmanY;
                        switch (board[pacmanY][pacmanX])
                        {
                        case ghost[0]:
                            collision(0);
                            break;
                        case ghost[1]:
                            collision(1);
                            break;
                        case ghost[2]:
                            collision(2);
                            break;
                        case ghost[3]:
                            collision(3);
                            break;
                        }
                    --turnsRemaining;
                    if (ghostX[0] == pacmanX && ghostY[0] == pacmanY)
                    {
                        collision(0);
                    }
                    else if (ghostX[1] == pacmanX && ghostY[1] == pacmanY)
                    {
                        collision(1);
                    } 
                    else if (ghostX[2] == pacmanX && ghostY[2] == pacmanY)
                    {
                        collision(2);
                    }
                    else if (ghostX[3] == pacmanX && ghostY[3] == pacmanY)
                    {
                        collision(3);
                    }

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
                    moveGhosts(0);
                    moveGhosts(1);
                    moveGhosts(2);
                    moveGhosts(3);
                    --pacmanX;
                    --turnsRemaining;
                    if (ghostX[0] == pacmanX && ghostY[0] == pacmanY)
                    {
                        collision(0);
                    }
                    else if (ghostX[1] == pacmanX && ghostY[1] == pacmanY)
                    {
                        collision(1);
                    } 
                    else if (ghostX[2] == pacmanX && ghostY[2] == pacmanY)
                    {
                        collision(2);
                    }
                    else if (ghostX[3] == pacmanX && ghostY[3] == pacmanY)
                    {
                        collision(3);
                    }
                    
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
                    moveGhosts(0);
                    moveGhosts(1);
                    moveGhosts(2);
                    moveGhosts(3);
                    ++pacmanX;
                    --turnsRemaining;
                    if (ghostX[0] == pacmanX && ghostY[0] == pacmanY)
                    {
                        collision(0);
                    }
                    else if (ghostX[1] == pacmanX && ghostY[1] == pacmanY)
                    {
                        collision(1);
                    } 
                    else if (ghostX[2] == pacmanX && ghostY[2] == pacmanY)
                    {
                        collision(2);
                    }
                    else if (ghostX[3] == pacmanX && ghostY[3] == pacmanY)
                    {
                        collision(3);
                    }
                }
                break;


            case ('q'):
                endwin(); // End PDCurses
                return 0;
        }
    }

    return 0;
}