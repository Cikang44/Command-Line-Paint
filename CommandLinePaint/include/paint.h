#pragma once

#include <tuple>
#include <stdarg.h>
#include <functional>
#include <any>

#include "renderer.h"

class Paint {
public:
    Paint(Renderer* r);

    class Palette {        
    public:        
        Palette(Paint* p);

        Paint* parent;
        Renderer* renderer;        
        void DrawPalette(int p_pHeight);            
        void DrawLineSep(int x);        
        void SetColor(Color p_color);
        int palette_height;
    private:
        int w;
        int h;   
    }; 
    
    class ColorButton {
    public:                     
        ColorButton(int p_x, int p_y, Color p_color);

        Color color;
        int xPos, yPos;
    };    

    Renderer* renderer; 
    Palette palette;
    Color color;
    vector<ColorButton> color_buttons;    

    //Methods
    void Frame();    
    void PaintUpdate();           
    void AddColorButton(int p_x, int p_y, Color p_color);
    void ChangeColor(Color p_color);
private:
    bool previously_drew = false;
    //this variable is calculated in char size instead of actual pixel
    //Also note it is only set when the user has drew
    POINT prev_cursor_pos; 
    POINT cursor_pos;    
    CONSOLE_FONT_INFOEX font_info;
    int w;
    int h;
};