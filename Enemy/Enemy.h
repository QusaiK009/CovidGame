#ifndef ENEMY_H
#define ENEMY_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/**Enemy class
  *@brief Virus
  *@author Qusay Khshman
  *@date May, 2020
*/   


class Enemy
{
public:
    
    /**Constructor*/
    Enemy();
    
    /**Overload Constructor*/
    Enemy(int, int);
    
    /**Destructor*/
    ~Enemy();
    
    /**Print virus
    *@param lcd - object for class N5110
    */
    void Spawn(N5110 &lcd);
    
    /**Accessors*/
    
    /**Get x coordinate of virus
    *@return x coordinate (int)
    */
    int get_x();
    
    /**Get y coordinate of virus
    *@return y coordinate (int)
    */
    int get_y();
    
    /**Get width of virus
    *@return width (int)
    */
    int get_width();
    
    /**Get height of virus
    *@return height (int)
    */
    int get_height();
    
    /**Mutuator*/
    
    /**Set x coordinate of virus
    *@param x - coordinate to be set
    */
    void set_x(int x);
    
    
private:

    int _x;
    int _y;
    int _height;
    int _width;

};
#endif