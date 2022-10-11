#include "Enemy.h"

// contrustor and destructor
Enemy::Enemy()
{

}

Enemy::Enemy(int x, int y) {
    
    _x = x;
    _y = y;
    
}

Enemy::~Enemy()
{

}

const int virus[7][7] =   {     // run animations 1 & 2

    { 0,1,1,0,1,1,0 },
    { 1,1,0,1,0,1,1 },
    { 1,0,1,1,1,0,1 },
    { 0,1,1,0,1,1,0 },
    { 1,0,1,1,1,0,1 },
    { 1,1,0,1,0,1,1 },
    { 0,1,1,0,1,1,0 },
    

    };

void Enemy::Spawn(N5110 &lcd) {
    
    lcd.drawSprite(_x,_y,7,7,(int *)virus);
    
}

void Enemy::set_x(int x) {
   
    _x = x;
    
}

int Enemy::get_x() {
    
    return _x;
    
}

int Enemy::get_width() {
    
    return 7;
    
}

int Enemy::get_height() {
    
    return 7;
    
}

int Enemy::get_y() {

    return _y;   
    
}