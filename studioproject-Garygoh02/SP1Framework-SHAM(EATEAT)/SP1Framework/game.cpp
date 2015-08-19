// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using std::vector;
using std::string;
double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD players[2];
COORD consoleSize;

size_t playfieldX = 15, playfieldY = 8;

vector<vector<unsigned int>> playfield(playfieldY);

unsigned int TEST;
void boardGen();
void printBoard();
void move(int X, int Y, unsigned int P);
bool check(string key);
char wall = 130;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"Splayers[0] Framework");
    srand(time(0)); rand();

    elapsedTime = 0.0;

    boardGen();
    // Sets the console size, this is the biggest so far.
    setConsoleSize(50, 30);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = playfield.size();
    consoleSize.Y = playfield.size();

    players[0].X = rand()%playfieldX;
    players[0].Y = rand()%playfieldY;
}

void shutdown()
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_UPLEFT] = isKeyPressed(VK_NUMPAD7);
    keyPressed[K_UPRIGHT] = isKeyPressed(VK_NUMPAD9);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_DOWNLEFT] = isKeyPressed(VK_NUMPAD1);
    keyPressed[K_DOWNRIGHT] = isKeyPressed(VK_NUMPAD3);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
    int X = players[0].X;
    int Y = players[0].Y;
    // Updating the location of the character based on the key press
	if (keyPressed[K_UP])		move(0, -1, 0);
	if (keyPressed[K_DOWN])		move(0, 1, 0);
	if (keyPressed[K_LEFT])		move(-1, 0, 0);
	if (keyPressed[K_RIGHT])	move(1, 0, 0);
	if (keyPressed[K_UPLEFT])	move(-1, -1, 0);
	if (keyPressed[K_UPRIGHT])	move(1, -1, 0);
	if (keyPressed[K_DOWNLEFT])	move(-1, 1, 0);
	if (keyPressed[K_DOWNRIGHT])move(1, 1, 0);

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;
}
void printBoard(){
    for (unsigned int Y = 0; Y < playfieldY; Y++)
    {
        for (unsigned int X = 0; X < playfieldX; X++)
        {
            gotoXY(X, Y );
            colour(0x0F);
            std::cout << static_cast<char>((playfield[Y][X]) + 48);
        }
    }
}
void render()
{
    // clear previous screen
    cls();

    //render the game
    printBoard();


    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;

    gotoXY(0, 0);
    colour(0x59);
    //std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(players[0]);
    colour(0x0C);
    std::cout << (char)1;

    colour(0x0F);
}

void boardGen(){
    for (unsigned int Y = 0; Y < playfieldY; Y++)
    {
        vector<unsigned int> V(playfieldX);

        for (unsigned int X = 0; X < playfieldX; X++) V[X] = rand() % 5 + 1;

        playfield[Y] = V;
    }
}

void move(int X, int Y, unsigned int P) //X and Y can be -1, 0, or 1 for unit directions; P represents player number (zero-based index)
{
	int TX = (int)players[P].X + X;
	int TY = (int)players[P].Y + Y;

	if (TX < 0) return;
	if (TX >= (int)playfieldX) return;
	if (TY < 0) return;
	if (TY >= (int)playfieldY) return;

	int N = playfield[TY][TX];

	if (TX + (N-1)*X < 0) return;
	if (TX + (N-1)*X >= (int)playfieldX) return;
	if (TY + (N-1)*Y < 0) return;
	if (TY + (N-1)*Y >= (int)playfieldY) return;

	for (int i = 1; i < N; i++)
	{
		TX += X; TY += Y;

		if (playfield[TY][TX] == wall) return;
	}

	for (unsigned int i = 0; i < N; i++) playfield[players[P].Y + Y*i][players[P].X + X*i] = wall;

	players[P].X += N*X;
	players[P].Y += N*Y;

	return;
}