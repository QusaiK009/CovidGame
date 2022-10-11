#include "Obstacle.h"

// contrustor and destructor
Obstacle::Obstacle()
{

}

Obstacle::Obstacle(int x, int y, int height, int width) {
    
    _x = x;
    _y = y;
    _height = height;
    _width = width;
    
}

Obstacle::~Obstacle()
{

}

void Obstacle::Spawn(N5110 &lcd) {
    
    lcd.drawRect(_x,_y,_width,_height,FILL_BLACK);   
    
}

void Obstacle::set_x(int x) {
   
    _x = x;
    
}

int Obstacle::get_x() {
    
    return _x;
    
}

int Obstacle::get_width() {
    
    return _width;
    
}

int Obstacle::get_height() {
    
    return _height;   
    
}

int Obstacle::get_y() {

    return _y;   
    
}