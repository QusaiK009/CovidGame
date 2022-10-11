#ifndef BULLET_H
#define BULLET_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"


/**Bullet class
  *@author Qusay Khshman
  *@date May, 2020
*/   

class Bullet
{
public:

    /**Constructor*/
    Bullet();
    
    /**Overload Constructor*/
    Bullet(int, int);
    
    /**Destructor*/
    ~Bullet();
    
    /**Print bullet
    *@param lcd - object for class N5110
    */
    void Spawn(N5110 &lcd);
    
    /**Accessors*/
    
    /**Get x coordinate of bullet
    *@return x coordinate (int)
    */
    int get_x();
    
    /**Get y coordinate of bullet
    *@return y coordinate (int)
    */
    int get_y();
    
    /**Mutator*/
    
    /**Set x coordinate of bullet
    *@param x - coordinate to be set (int)
    */
    void set_x(int x);
    
    
private:

    int _x;
    int _y;

};
#endif