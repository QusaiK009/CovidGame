#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

class Obstacle
{
public:
    
    /**Constructor*/
    Obstacle();
    
    /**Overload Constructor*/
    Obstacle(int, int, int, int);
    
    /**Destructor*/
    ~Obstacle();
    
    /**Print obstacle
    *@param lcd - object for class N5110
    */
    void Spawn(N5110 &lcd);
    
    /**Accessors*/
    
    /**Get x coordinate of obstacle
    *@return x coordinate (int)
    */
    int get_x();
    
    /**Get y coordinate of obstacle
    *@return y coordinate (int)
    */
    int get_y();
    
    /**Get width of obstacle
    *@return width (int)
    */
    int get_width();
    
    /**Get height of obstacle
    *@return height (int)
    */
    int get_height();
    
    /**Mutuator*/
    
    /**Set x coordinate of obstacle
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