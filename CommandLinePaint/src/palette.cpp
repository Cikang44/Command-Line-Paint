#include "paint.h"
#include "renderer.h"

Paint::Palette::Palette(Paint* p)
    :parent(p), renderer(p->renderer)
{    
    w = renderer->width;
    h = renderer->height;
}

void Paint::Palette::SetColor(Color p_color) {
    renderer->Draw(1, 6, "Clicked!");
}

void test(int i) {

}

void Paint::Palette::DrawPalette(int p_pHeight) {         
    //Update Width and Height
    w = renderer->width;
    h = renderer->height;

    //Draw Bottom Line of Palette    
    string lineOut;
    for (int i = 1; i < w - 1; i++) {
        lineOut += "═";    
    }        
    renderer->Draw(1, p_pHeight, lineOut, 1, C_BLUE, C_WHITE);

    palette_height = p_pHeight;

    //Draw Color
    int start = 22;
    int end = 42;
    DrawLineSep(start);    
    DrawLineSep(end);
    //Colors : Black, Red, Orange, Yellow, Green, Cyan, Blue, Purple
    Color colors[3][9] = {    
        {C_BLACK, C_GREY, C_RED, C_ORANGE, C_YELLOW, C_GREEN, C_CYAN, C_BLUE, C_PURPLE}, 
        {C_WHITE, C_LIGHTGREY, C_PINK, C_LIGHTORANGE, C_LIGHTYELLOW, C_LIGHTGREEN, C_LIGHTCYAN, C_LIGHTBLUE, C_LIGHTPURPLE},
        {C_DARKERGREY, C_DARKGREY, C_DARKRED, C_DARKYELLOW, C_DARKORANGE, C_DARKGREEN, C_DARKCYAN, C_DARKBLUE, C_DARKPURPLE}
    };    
    Color pal_background = Color(225, 225, 225);

    for (int i = 0; i < sizeof(colors)/sizeof(Color[9]); i++) {
        for (int q = 0; q < sizeof(colors[i])/sizeof(Color); q++) {
            renderer->Draw(q * 2 + start + 3, i + 2, "│", 0, C_WHITE, pal_background);
            renderer->Draw(q * 2 + start + 2, i + 2, "■", 0, colors[i][q], pal_background);
            parent->AddColorButton(q * 2 + start + 2, i + 2, colors[i][q]);
        }
        renderer->Draw(start + 1, i + 2, "│", 0, C_WHITE, pal_background);
    }    
}

void Paint::Palette::DrawLineSep(int x) {    
    renderer->Draw(x, palette_height, "╧", 1, C_BLUE, C_WHITE);
    for (int i = 1; i < palette_height; i++) {
        renderer->Draw(x, i, "│", 1, C_BLUE, C_WHITE);
    }
}
