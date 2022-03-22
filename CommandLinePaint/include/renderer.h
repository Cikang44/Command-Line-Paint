#pragma once

#include <string>
#include <vector>
#include <codecvt>

#include <Windows.h>

using namespace std;

class Color {
public:
    Color(int r, int g, int b);

    int R = 0;
    int G = 0;
    int B = 0;
};

//Color Constants
const Color C_BLACK     = Color(0, 0, 0);
const Color C_GREY      = Color(200, 200, 200);
const Color C_RED       = Color(255, 0, 0);
const Color C_ORANGE    = Color(255, 100, 100);
const Color C_YELLOW    = Color(255, 255, 0);
const Color C_GREEN     = Color(0, 255, 0);
const Color C_CYAN      = Color(0, 255, 255);
const Color C_BLUE      = Color(0, 0, 255);
const Color C_PURPLE    = Color(255, 0, 255);

const Color C_WHITE         = Color(255, 255, 255);
const Color C_LIGHTGREY     = Color(225, 225, 225);
const Color C_PINK          = Color(255, 200, 200);
const Color C_LIGHTORANGE   = Color(255, 150, 150);
const Color C_LIGHTYELLOW   = Color(255, 255, 150);
const Color C_LIGHTGREEN    = Color(150, 255, 150);
const Color C_LIGHTCYAN     = Color(150, 255, 255);
const Color C_LIGHTBLUE     = Color(150, 150, 255);
const Color C_LIGHTPURPLE   = Color(255, 150, 255);

const Color C_DARKERGREY    = Color(50, 50, 50);
const Color C_DARKGREY      = Color(100, 100, 100);
const Color C_DARKRED       = Color(150, 0, 0);
const Color C_DARKORANGE    = Color(150, 50, 0);
const Color C_DARKYELLOW    = Color(150, 150, 0);
const Color C_DARKGREEN     = Color(0, 150, 0);
const Color C_DARKCYAN      = Color(0, 150, 150);
const Color C_DARKBLUE      = Color(0, 0, 150);
const Color C_DARKPURPLE    = Color(150, 0, 150);

class CharPixel {    
public:
    const int posX;
    const int posY;
    const string ch;
    CharPixel(int posX, int posY, string ch);    
};

class Renderer {
private:
    bool p_firstdraw = false;  
    vector<CharPixel> drawStack;
public:
    Renderer();
    void Init();    
    void Draw(int x, int y, const string ch, int style_mode = 0, Color foreground = C_BLACK, Color background = C_WHITE);
    void Display();
    int width;
    int height;     

    wstring to_wstring(string str);   
};