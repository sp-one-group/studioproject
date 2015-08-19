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
COORD charLocation;
COORD consoleSize;

size_t playfieldX = 15, playfieldY = 15;

vector<vector<unsigned int>> playfield(playfieldY);

unsigned int TEST;
void boardGen();
void printBoard();
bool check(string key);
char wall = 130;
void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"SP1 Framework");
    srand(time(0)); rand();

    elapsedTime = 0.0;

    boardGen();
    // Sets the console size, this is the biggest so far.
    setConsoleSize(playfield.size() *2, playfield.size() *2);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = playfield.size();
    consoleSize.Y = playfield.size();

    charLocation.X = rand()%playfieldX;
    charLocation.Y = rand()%playfieldY + 1;
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
    int X = charLocation.X;
    int Y = charLocation.Y;
    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        string key = "up";
        X = charLocation.X;
        Y = charLocation.Y;
        if(check(key) == true){
            Beep(1500,100);
            int number = playfield[Y-1][X];
            std::cout<<number;
            for(int i = 0; i<number; i++){
                X = charLocation.X;
                Y = charLocation.Y;
                playfield[Y][X] = wall;
                charLocation.Y--;
            }
        }
    }
    if (keyPressed[K_UPLEFT] && charLocation.Y > 0 && charLocation.X > 0)
    {
        string key = "upleft";
        X = charLocation.X;
        Y = charLocation.Y;
        if(check(key) == true){
            Beep(1500,100);
            int number = playfield[Y-1][X-1];
            std::cout<<number;
            for(int i = 0; i<number; i++){
                X = charLocation.X;
                Y = charLocation.Y;
                playfield[Y][X] = wall;
                charLocation.Y--;
                charLocation.X--;
            }
        }

    }
    if (keyPressed[K_UPRIGHT] && charLocation.X < consoleSize.X - 1 && charLocation.Y > 0 )
    {
        string key = "upright";
        X = charLocation.X;
        Y = charLocation.Y;
        if(check(key) == true){
            Beep(1500,100);
            int number = playfield[Y-1][X+1];
            std::cout<<number;
            for(int i = 0; i<number; i++){
                X = charLocation.X;
                Y = charLocation.Y;
                playfield[Y][X] = wall;
                charLocation.Y--;
                charLocation.X++;
            }
        }
        
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
         string key = "down";
        X = charLocation.X;
        Y = charLocation.Y;
        if(check(key) == true){
            Beep(1500,100);
            int number = playfield[Y + 1][X];
            std::cout<<number;
            for(int i = 0; i<number; i++){
                X = charLocation.X;
                Y = charLocation.Y;
                playfield[Y][X] = wall;
                charLocation.Y++;
            }
        }
        
    }
    if (keyPressed[K_DOWNLEFT] && charLocation.Y < consoleSize.Y - 1 && charLocation.X > 0)
    {
         string key = "downleft";
        X = charLocation.X;
        Y = charLocation.Y;
        if(check(key) == true){
            Beep(1500,100);
            int number = playfield[Y+1][X-1];
            std::cout<<number;
            for(int i = 0; i<number; i++){
                X = charLocation.X;
                Y = charLocation.Y;
                playfield[Y][X] = wall;
                charLocation.Y++;
                charLocation.X--;
            }
        }
        
    }
    if (keyPressed[K_DOWNRIGHT] && charLocation.Y < consoleSize.Y - 1 && charLocation.X < consoleSize.X - 1)
    {
         string key = "downright";
        X = charLocation.X;
        Y = charLocation.Y;
        if(check(key) == true){
            Beep(1500,100);
            int number = playfield[Y+1][X+1];
            std::cout<<number;
            for(int i = 0; i<number; i++){
                X = charLocation.X;
                Y = charLocation.Y;
                playfield[Y][X] = wall;
                charLocation.Y++;
                charLocation.X++;
            }
        }
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
         string key = "left";
        X = charLocation.X;
        Y = charLocation.Y;
        if(check(key) == true){
            Beep(1500,100);
            int number = playfield[Y][X-1];
            std::cout<<number;
            for(int i = 0; i<number; i++){
                X = charLocation.X;
                Y = charLocation.Y;
                playfield[Y][X] = wall;
                charLocation.X--;
            }
        }
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
         string key = "right";
        X = charLocation.X;
        Y = charLocation.Y;
        if(check(key) == true){
            Beep(1500,100);
            int number = playfield[Y][X+1];
            std::cout<<number;
            for(int i = 0; i<number; i++){
                X = charLocation.X;
                Y = charLocation.Y;
                playfield[Y][X] = wall;
                charLocation.X++;
            }
        }
    }


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
    gotoXY(charLocation);
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
bool check(string key){
    if(key == "up"){
        int number = playfield[charLocation.X][charLocation.Y - 1];
        if(((charLocation.Y - number) < 0 )){
            return false;
        }
        else if(playfield[charLocation.Y - number][charLocation.X] == 130){
            return false;
        }
        else{return true;}
    }
    if(key == "down"){
        int number = playfield[charLocation.X][charLocation.Y + 1];
        if(((charLocation.Y + number) > playfield.size() )){
            return false;
        }
        else if(playfield[charLocation.Y + number][charLocation.X] == 130){
            return false;
        }
        else{return true;}
    }
    if(key == "left"){
        int number = playfield[charLocation.X - 1][charLocation.Y];
        if(((charLocation.X) < 0 )){
            return false;
        }
        else if(playfield[charLocation.Y][charLocation.X - number] == 130){
            return false;
        }
        else{return true;}
    }
    if(key == "right"){
        int number = playfield[charLocation.X + 1][charLocation.Y];
        
        if(((charLocation.X + number) > playfield.size() )){
            return false;
        }
        else if(playfield[charLocation.Y][charLocation.X + number] == 130){
            return false;
        }
        else{return true;}
    }
}