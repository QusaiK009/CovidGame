#include "Bullet.h"

// contrustor and destructor
Bullet::Bullet()
{

}

Bullet::Bullet(int x, int y) {
    
    _x = x;
    _y = y;
    
}

Bullet::~Bullet()
{

}

void Bullet::Spawn(N5110 &lcd) {
    
    lcd.drawRect(_x,_y,1,1,FILL_BLACK);   
    
}

void Bullet::set_x(int x) {
   
    _x = x;
    
}

int Bullet::get_x() {
    
    return _x;
    
}

int Bullet::get_y() {

    return _y;   
    
}