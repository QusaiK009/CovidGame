#ifndef PLAYER_H
#define PLAYER_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"


/**Player class
  *@brief contains all player parameters
  *@author Qusay Khshman
  *@date May, 2020
*/    
    
class Player
{
public:
    
    /**Constructor*/
    Player();
    
    /**Destructor*/
    ~Player();
    
    /**initialize player parameters
    *@details initial positions, gravity, y-velocity, y-displacement and progress
    */
    void init();
    
    /**Running Animation
    *@details alternate between running animations 1 and 2. If above ground, print jump animation
    *@param t - time level ran for (float)
    *@param lcd - object for class N5110
    *@param pad - object for class Gamepad
    */
    void Run(float t,N5110 &lcd,Gamepad &pad);
    
    /**Alter Jump parameters
    *@details set time of jump, gravity and y-velocity
    *@param t1 - pass by reference to alter t1(float)
    *@param T - period of refresh (float)
    */
    void Jump(float &t1, float T);
    
    /**Duck Animation
    *@details alternate ducking animations
    *@param t - time game has ran for
    *@param lcd - object of class N5110
    */
    void Duck(float t,N5110 &lcd);
    
    /**Ground Animation
    *@details alternate ground animations
    *@param t - time game has ran for
    *@param lcd - object of class N5110
    */
    void ground_anim(float t,N5110 &lcd);
    
    /**Alter progress and print bar
    *@param lcd - object of class N5110
    */
    void progress(N5110 &lcd);
    
    /**Draw designated sprite from list
    *@param x - x coordinate to print at
    *@param y - y coordinate to print at
    *@param SpriteNumber - choose which sprite to print
    *       
    *       0 - Run animation 1
    *       1 - Run animation 2
    *       2 - Jump animation 
    *       3 - Duck animation 1
    *       4 - Duck animation 2
    *
    *@param lcd - object of class N5110
    */
    void draw_a_sprite(int x, int y, int SpriteNumber, N5110 &lcd); //function to print a specific sprite out of sprites given
    
    /**Accessors*/
    
    /**Get position of player
    *@return x and y positions as a vector
    */
    Vector2D get_pos();
    
    /**Get gravity of player
    *@return gravity (int)
    */
    int get_grav();
    
    /**Get y-velocity of player
    *@return y velocity (int)
    */
    int get_y_vel();
    
    
    /**Get progress value
    *@return progress (int)
    */
    int get_progress();
    
    /**Mutators*/
    
    /**Set gravity of player
    *@param G - gravity value to set (int)
    */
    void set_grav(int G);
    
    /**Set y-velocity of player
    *@param vy - y-velocity to be set (int)
    */
    void set_y_vel(int vy);
    
    /**Set x coordinate of player
    *@param x - x value to set (int)
    */
    void set_x_pos(int x);
    
    /**Set y coordinate of player
    *@param y - y value to set (int)
    */
    void set_y_pos(int y);
    
    /**Set y displacement of player
    *@param uy - y-displacement value to be set (int)
    */
    void set_y_displacement (int uy);

private:

    int _x;
    int _y;
    int _G;
    int _vy;
    int _u_y;
    int _progress;

};
#endif