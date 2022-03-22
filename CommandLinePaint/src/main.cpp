#include <iostream>
#include <string>
#include <cstdlib>
#include <csignal>

#include <stdarg.h>
#include <signal.h>
#include <Windows.h>
#include <WinUser.h>

#include "renderer.h"
#include "paint.h"

using namespace std;

//Converts string to int ; in order for switch case to work with it
constexpr unsigned int to_hash(const char *s, int off = 0) {                        
    return !s[off] ? 5381 : (to_hash(s, off+1)*33) ^ s[off];                           
}  

Renderer renderer;

int main() {  
    cout << "Active" << endl;              

    //Init
    renderer.Init();   
    Paint painter(&renderer);  

    //On Exit  
    int exit_signals[] {SIGINT, SIGABRT, SIGTERM};    
    for (int sg : exit_signals) {signal(sg, [] (int i) { wcout << renderer.to_wstring("\e[" + to_string(renderer.height) + "B\e[0m\n"); exit(i); }); };        

    //Draw init
    painter.Frame();
    painter.palette.DrawPalette(5);
    painter.palette.DrawLineSep(22);

    //Main While Loop
    bool close = false;
    while(!close) {                                    
        //Reload
        if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState('R') & 0x8000)) {                     
            renderer.Init();
            painter.Frame();
            painter.palette.DrawPalette(5);            
        }

        //Update
        painter.PaintUpdate();
        renderer.Display();
    }

    return 0;
}