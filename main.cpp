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
int leftToPick = 245;

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

void drawBoard() {
    start_color();

    // Color pair for Pacman
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    // Color pair for board 
    init_pair(2, COLOR_BLUE, COLOR_BLACK); 
    //Color pairs for ghosts
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

void powerUpping() {
    SCORE = SCORE + 20;
    turnsRemaining = 30;
    --leftToPick;
}

void collision(int ghostNumber) {
    if (turnsRemaining <= 0)
    {
        --LIFES;
        if (LIFES != 0)
        {
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

void checkCollision() {
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
            if (ghostX[ghostNumber] == 27)
            {
                ghostX[ghostNumber] = 1;
            } else if (ghostX[ghostNumber] == 0)
            {
                ghostX[ghostNumber] = 26;
            }
            
            
}




int main() {

    srand(time(0));


    //pdcurses settings
    initscr(); // Initialize PDCurses
    noecho(); // Don't echo user input
    curs_set(0); // Hide cursor
    resize_term(35, 28);

    char userInput;

    while (LIFES != 0 && leftToPick != 0) {
        
        //drawing current game state
        clear();
        drawBoard();
        refresh();

        //moving pacman
        userInput = getch();

        switch (userInput) {
            case ('w'):
                if (board[pacmanY - 1][pacmanX] != WALL && board[pacmanY - 1][pacmanX] != GHOST_GATE) {
                    if (board[pacmanY - 1][pacmanX] == COIN)
                    {
                        ++SCORE;
                        --leftToPick;
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
                    checkCollision();
                }
                break;


            case ('s'):
                if (board[pacmanY + 1][pacmanX] != WALL && board[pacmanY + 1][pacmanX] != GHOST_GATE) {
                    if (board[pacmanY + 1][pacmanX] == COIN)
                    {
                        ++SCORE;
                        --leftToPick;
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
                    --turnsRemaining;
                    checkCollision();

                }
                break;


            case ('a'):
                if (board[pacmanY][pacmanX - 1] != WALL && board[pacmanY][pacmanX - 1] != GHOST_GATE) {
                    if (board[pacmanY][pacmanX - 1] == COIN)
                    {
                        ++SCORE;
                        --leftToPick;
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
                    if (pacmanX == 0 && pacmanY ==  14)
                    {
                        pacmanX = 27;
                    }
                    --turnsRemaining;
                    checkCollision();
                    
                }
                break;


            case ('d'):
                if (board[pacmanY][pacmanX + 1] != WALL && board[pacmanY][pacmanX + 1] != GHOST_GATE) {
                    if (board[pacmanY][pacmanX + 1] == COIN)
                    {
                        ++SCORE;
                        --leftToPick;
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
                    if (pacmanX == 27 && pacmanY ==  14)
                    {
                        pacmanX = 0;
                    }
                    
                    --turnsRemaining;
                    checkCollision();
                }
                break;


            case ('q'):
                endwin(); // End PDCurses
                return 0;
        }
 
    }
    if (leftToPick == 0)
    {
        clear();
        mvprintw(15, 10, "You won!");
        mvprintw(17, 7, "Final score: %d", SCORE);
        mvprintw(21, 7, "Press q to exit");
        while (userInput != 'q')
        {
            userInput = getch();
        }
    } else
    {
        clear();
        mvprintw(15, 10, "You lost!");
        mvprintw(17, 7, "Final score: %d", SCORE);
        mvprintw(21, 7, "Press q to exit");
        while (userInput != 'q')
        {
            userInput = getch();
        }
    }
    
    

    return 0;
}