#include <string>

#include "paint.h"
#include "renderer.h"

using namespace std;

Paint::Paint(Renderer* r)
    : renderer(r), palette(this), color(C_BLACK)
{

}

void Paint::Frame() {
    w = renderer->width;
    h = renderer->height;    

    string out;

    //Draw Top
    for (int i = 1; i <= w; i++) {
        out += "█";
    }

    //Draw Right
    for (int i = 1; i < h; i++) {
        out += "\e[1B█";
    }

    //Draw Bottom
    out += "\e[1D▄";
    for (int i = 1; i < w; i++) {        
        out += "\e[2D▄";
    }

    //Draw Left
    for (int i = 1; i < h; i++) {
        out += "\e[1A\e[1D█";
    }

    renderer->Draw(0, 0, out, 0, C_BLUE, C_BLUE);

    //Draw Title
    char title[] = "Paint";
    renderer->Draw(1, 0, title, 1, C_WHITE, C_BLUE);

    //Get Font Info
    //Get Font Info        
    font_info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    if (GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &font_info)) {
        renderer->Draw(1, 1, "Font X :" + to_string(font_info.dwFontSize.X) + " Font Y :" + to_string(font_info.dwFontSize.Y));                     
    }    
}

void Paint::PaintUpdate() {
    //Get Cursor Position        
    if (GetCursorPos(&cursor_pos)) {
        if (ScreenToClient(GetConsoleWindow(), &cursor_pos)) {                
            renderer->Draw(1, 3, "X :" + to_string(cursor_pos.x) + " Y :" + to_string(cursor_pos.y));                                    
       }
    }            
    int cX = cursor_pos.x / font_info.dwFontSize.X + 1;
    int cY = cursor_pos.y / font_info.dwFontSize.Y + 1;
    renderer->Draw(1, 4, "cX :" + to_string(cX) + " cY :" + to_string(cY));        

    //Alt : Paint Key
    if (GetKeyState(VK_RBUTTON) & 0x8000) {       
        //Paint
        if (cY > palette.palette_height && cY < h && cX > 0 && cX < w) {
            //Draw Line between previous draw position to current position                        
            if (previously_drew) {
                int dX = cX - prev_cursor_pos.x;
                int dY = cY - prev_cursor_pos.y;
                int d = 2 * dX - dY;
                int incr_east = 2 * dX;
                int incr_northeast = 2 * (dY - dX);
                int x = prev_cursor_pos.x;
                int y = prev_cursor_pos.y;

                //Draw first pixel
                if (y > palette.palette_height && y < h && x > 0 && x < w)
                renderer->Draw(x, y, "#", 0, color, C_WHITE);                

                while (x < cX) {
                    if (d <= 0) {
                        d += incr_east;
                        x++;
                    } else {
                        d += incr_northeast;
                        x++;
                        y++;
                    }

                    if (y > palette.palette_height && y < h && x > 0 && x < w)
                        renderer->Draw(x, y, "#", 0, color);                    
                }
            } else {
                renderer->Draw(cX, cY, "#", 0, color);
            }
        }    

        prev_cursor_pos.x = cX;
        prev_cursor_pos.y = cY;
        previously_drew = true;
    } else {
        previously_drew = false;
    }

    //Shift : Click Button Key
    if (GetKeyState(VK_RBUTTON) & 0x8000) {
        for (ColorButton e : color_buttons) {            
            if (cX == e.xPos && cY == e.yPos) {                
                ChangeColor(e.color);
            }
        }
    }
}

Paint::ColorButton::ColorButton(int p_x, int p_y, Color p_color) : xPos(p_x), yPos(p_y), color(p_color) {}

void Paint::AddColorButton(int p_x, int p_y, Color p_color) {
    color_buttons.push_back(ColorButton(p_x, p_y, p_color));
}

void Paint::ChangeColor(Color p_color) {
    color = p_color;
}