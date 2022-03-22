#include <iostream>
#include <string>
#include <sstream>
#include <charconv>
#include <codecvt>
#include <locale>
#include <io.h>
#include <Windows.h>
#include <fcntl.h>

#include "renderer.h"

using namespace std;

Color::Color(int r, int g, int b) : R(r), G(g), B(b) {}

using convert_t = codecvt_utf8<wchar_t>;
wstring_convert<convert_t, wchar_t> strconverter;
wstring Renderer::to_wstring(string str)
{
    return strconverter.from_bytes(str);
}

Renderer::Renderer()
    : width(0), height(0)    
{
    
}

void Renderer::Init() {
    //Enable VT100
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    //Set Echo Input False
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    mode &= ~ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode);    

    //Enable Unicode
    _setmode(_fileno(stdout), _O_U16TEXT);    

    //Hide Cursor
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 100;
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

    //Get Command Prompt Size
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    cout << width << endl;
    cout << height << endl;

    //Draw Frame
    stringstream sOut;
    sOut << "\e[38;2;0;0;255m\e[48;2;255;255;255m";
    for (int i = 0; i < height; i++) {
        for (int q = 0; q < width - 1; q++) {
            sOut << ".";

        }
        if (i != height - 1) {
            sOut << "\n";
        }
    } 

    //Move Caret to Home Position
    sOut << "\e[0m\e[H";

    //Output
    wcout << to_wstring(sOut.str());
}

void Renderer::Draw(int x, int y, string ch, int style_mode, Color foreground, Color background) { // X and Y is counted from Top Right             
    drawStack.push_back(CharPixel(x, y, 
    "\e[" + to_string(style_mode) + "m"
     + "\e[38;2;" + to_string(foreground.R) + ";" + to_string(foreground.G) + ";" + to_string(foreground.B) + "m"
     + "\e[48;2;" + to_string(background.R) + ";" + to_string(background.G) + ";" + to_string(background.B) + "m" + ch));    
}

void Renderer::Display() {
    string out;        
    for (CharPixel e : drawStack) {        
        out += "\e[" + to_string(e.posX - 1) + "C"  // Move Right
             + "\e[" + to_string(e.posY - 1) + "B"  // Move Down
             + e.ch
             + "\e[H"; // Move back Home                                 
    }

    out += "\e[0m";

    //Start Drawing
    wcout << to_wstring(out);

    //Clear array
    drawStack.clear();
}

CharPixel::CharPixel(int x, int y, string s) : posX(x), posY(y), ch(s) {}