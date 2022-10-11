#include "Player.h"

// contrustor and destructor
Player::Player()
{

}

Player::~Player()
{

}

const int run_anim1[12][7] =   {     // run animations 1 & 2 sprites
    { 0,0,1,1,1,0,0 },
    { 0,0,1,1,0,0,0 },
    { 0,0,1,1,1,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,1,1,1 },
    { 1,1,1,1,1,1,0 },
    { 0,0,0,1,0,1,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 1,0,0,1,0,0,0 },
    { 0,1,1,0,1,1,0 },
    { 0,0,0,0,0,0,1 },

    };

const int run_anim2[12][7] =   {
    { 0,0,1,1,1,0,0 },
    { 0,0,1,1,0,0,0 },
    { 0,0,1,1,1,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,1,1,1 },
    { 0,0,1,1,1,1,0 },
    { 0,0,1,1,0,1,0 },
    { 0,0,1,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,1,0,1,0,0 },
    { 0,0,1,0,1,0,0 },

    };

const int jump_anim[9][6] =   {          // jump animation sprite
    { 0,1,1,1,0,0 },
    { 0,1,1,0,0,0 },
    { 0,1,1,1,0,0 },
    { 0,0,1,0,0,0 },
    { 0,0,1,0,1,1 },
    { 1,1,1,1,1,0 },
    { 0,0,1,0,0,0 },
    { 1,1,0,1,1,0 },
    { 1,0,0,0,1,0 },
    

    };

const int duck_anim1[9][6] =   {         // duck animations 1 & 2 sprites
    { 1,1,1,0,0,0 },
    { 1,1,0,0,0,0 },
    { 1,1,1,0,0,0 },
    { 0,1,0,0,0,0 },
    { 1,0,0,1,1,1 },
    { 1,0,1,1,1,0 },
    { 0,1,0,0,1,0 },
    { 0,1,1,1,0,0 },
    { 1,1,0,1,0,0 },
    

    };
const int duck_anim2[9][6] =   {
    { 1,1,1,0,0,0 },
    { 1,1,0,0,0,0 },
    { 1,1,1,0,0,0 },
    { 0,1,0,0,0,0 },
    { 1,0,0,1,1,1 },
    { 1,0,1,1,1,0 },
    { 0,1,0,0,1,0 },
    { 1,0,1,0,0,0 },
    { 1,0,1,0,0,0 },
    

    };

void Player::init() {
    
    _x = 0;
    _y = 33; //initial positions
    _G = 0; // Gravitational field strength for jumping animation (initial 0, jump function alters it)
    _vy = 0; // y-velocity
    _u_y = 0; // displacement
    _progress = 0;
    
}

void Player::Run(float t,N5110 &lcd,Gamepad &pad) {
        
    _y -= _u_y; // subtract y from displacement due to inverted screen
    int T2 = t*100; // Change t to an integer and multiply by 10 to make it a whole number
    
    if (_y > 33 && pad.get_direction() == CENTRE) { //once landed on floor set gravity and velocity back to zero to prevent displacement formula being used. 
                                                    // Restrict y going above 33. In case of duck, if analog release set y back to 33
        _y = 33;
        _vy = 0;
        _G = 0;
    }  
    
#ifdef CHECK_RUN

        printf("t = %.2f, T2 = %d, y displacement = %d\n",t,T2,_u_y); // Check if t and T are correct values, check y-displacement for jump

#endif

    if(_y < 33) { //check if the player is off ground
        
        lcd.drawSprite(_x,_y,9,6,(int *)jump_anim);
    
    } else {
         
        if (T2%2==0) { // alternate run animation. if t is even, display anim 1 otherwise anim 2

            lcd.drawSprite(_x,_y,12,7,(int *)run_anim1);

        } else {

            lcd.drawSprite(_x,_y,12,7,(int *)run_anim2);
        }
    }                
}
        
void Player::Jump(float &t1, float T) {
        
    _G = -9;   
    _vy = 3;
    t1 = T; //set t1
    
}

void Player::Duck(float t,N5110 &lcd) {
        
    _y = 36;
    int T2 = t*100; // change t to an integer and multiply by 10 to make it a whole number
    
#ifdef CHECK_DUCK

        printf("T(duck) = %d\n", T2); // Check if T is correct value

#endif

    if (T2%2==0) { // alternate duck animation. if t is even display anim 1 otherwise anim 2
        
        lcd.drawSprite(_x,_y,9,6,(int *)duck_anim1);

    } else {

        lcd.drawSprite(_x,_y,9,6,(int *)duck_anim2);
    }    
}

void Player::ground_anim(float t,N5110 &lcd) {
        
    int T2 = t*10; // change t to an integer and multiply by 10 to make it a whole number

    if (T2%2==0) { // alternate ground animation. if t is even display anim 1 otherwise anim 2
        
        lcd.drawLine(1,45,84,45,2);

    } else {

        lcd.drawLine(0,45,84,45,2);
    }
}

Vector2D Player::get_pos() {
        
    Vector2D p = {_x,_y};
    return p;
        
}

int Player::get_grav() {
    
    return _G;
    
}

int Player::get_y_vel() {
    
    return _vy;   
    
}
int Player::get_progress() {

    return _progress;
    
}

void Player::set_grav(int G) {
    
    _G = G;   
    
}

void Player::set_y_vel(int vy) {
    
    _vy = vy;   
    
}

void Player::set_x_pos(int x) {
    
    _x = x;   
    
}

void Player::set_y_pos(int y) {
    
    _y = y;   
    
}

void Player::set_y_displacement (int uy) {
    
    _u_y = uy;
    
}

void Player::draw_a_sprite(int x, int y, int SpriteNumber, N5110 &lcd) {
    
    switch (SpriteNumber) {

        case 1:
            lcd.drawSprite(x,y,12,7,(int *)run_anim1);
            break;
        case 2:
            lcd.drawSprite(x,y,12,7,(int *)run_anim2);
            break;
        case 3:
            lcd.drawSprite(x,y,9,6,(int *)jump_anim);
            break;
        case 4:
            lcd.drawSprite(x,y,9,6,(int *)duck_anim1);
            break;
        case 5:
            lcd.drawSprite(x,y,9,6,(int *)duck_anim2);
            break;
            
    }

}

void Player::progress(N5110 &lcd) {
        
    _progress += 1; //increment progress each frame
    //progress bar
    lcd.drawRect(11,2,62,3,FILL_TRANSPARENT);
    int X = _progress/20; //change max (which is 1200) to fit 60 length bar
    lcd.drawRect(12,3,X,1,FILL_BLACK);
}