#ifndef ENGINE_H
#define ENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Player.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Intro.h"
#include "melody.h"
#include <vector>
#include "math.h"


/**Game engine class
  *@brief contains all the functions that help run the game
  *@author Qusay Khshman
  *@date May, 2020
*/

class Engine
{
public:
    
    /**Constructor */
    Engine();
    
    /**Destructor */
    ~Engine();
    
    /**Initialize percentages
    *@details sets percentages for levels 1,2 and 3 to 0
    */
    void percentages_init();
    
    /**Initialize game engine
    *@details initializes variables required for every game cycle
    *@param fps - set fps (refresh rate of game(float))
    */
    void init(float fps);
    
    /**Add Obstacles into vector
    *@details randomises obstacle heights and widths, and whether it is a jump obstacle or duck. Pushes new obstacle back into obstacle vector.
    */
    void AddObstacle();
    
    /**Add Viruses into vector
    *@details randomises jump or duck virus, and pushes new virus back into virus vector
    */
    void AddVirus();
    
    /**Add Bullets into vector
    *@details pushes new bullets into vector
    */
    void AddBullet();
    
    /**Print Obstacles in vector
    *@details iterate through obstacle vector and print members
    *@param lcd - object of class N5110
    */
    void PrintObstacles(N5110 &lcd);
    
    /**Print Viruses in vector
    *@details iterate through virus vector and print members
    *@param lcd - object of class N5110
    */
    void PrintVirus(N5110 &lcd);
    
    /**Print Bullets in vector
    *@details iterate through Bullet vector and print members
    *@param lcd - object of class N5110
    */
    void PrintBullets(N5110 &lcd);
    
    /**accessors*/ 
    
    /**Get value of T
    *@return period of refresh rate - T
    */
    float get_T();
    
    /**Get won state
    *@return either won or lost @details 1 means lost, 2 means won, 0 is neither
    */
    int get_won();
    
    /**Get level number
    *@return level selected
    */
    int get_level();
    
    /**mutator*/
    
    /**Set level number
    *@param n - level number
    *
    *   0 - none
    *   1 - lvl 1
    *   2 - lvl 2
    *   3 - lvl 3
    *
    */
    void set_level(int n);
    
    /**Print percentage of level 1
    *@details create char array to store value of percentage and print
    *@param x - x value to print percentage at (int)
    *@param l - line to print at (int)
    *@param lcd - object of class N5110
    */
    void print_percentage1(int x, int l, N5110 &lcd);
    
    /**Print percentage of level 2
    *@details create char array to store value of percentage and print
    *@param x - x value to print percentage at (int)
    *@param l - line to print at (int)
    *@param lcd - object of class N5110
    */
    void print_percentage2(int x, int l, N5110 &lcd);
    
    /**Print percentage of level 3
    *@details create char array to store value of percentage and print
    *@param x - x value to print percentage at (int)
    *@param l - line to print at (int)
    *@param lcd - object of class N5110
    */
    void print_percentage3(int x, int l, N5110 &lcd);
    
    /**Initiate Start-Game Animation
    *@details run to x = 20 and start level
    *@param lcd - object of class N5110
    *@param pad - object of class Gamepad
    */
    void StartGame(N5110 &lcd,Gamepad &pad);
    
    /**Read Input
    *@details Obtain analog's direction
    *@param pad - object of class Gamepad
    */
    void ReadUserInput(Gamepad &pad);
    
    /**Game AI
    *@details Contains all the conditions for the game's main engine
    *@param pad - object of class Gamepad
    *@param lcd - object of class N5110
    */
    void UpdateGame(N5110 &lcd, Gamepad &pad);
    
    /**Initiate introduction cut-scene
    *@param pad - object of class Gamepad
    *@param lcd - object of class N5110
    */
    void IntroScene(N5110 &lcd,Gamepad &pad);
    
    /**Initiate end cut-scene
    *@param pad - object of class Gamepad
    *@param lcd - object of class N5110
    */
    void EndScene(N5110 &lcd,Gamepad &pad);
    
    /**Initiate game over screen
    *@details prints game over screen depending on type of death and displays percentage completed
    *@param pad - object of class Gamepad
    *@param lcd - object of class N5110
    */
    void GameOver(N5110 &lcd, Gamepad &pad);
    
    /**Initiate level completed screen
    *@param pad - object of class Gamepad
    *@param lcd - object of class N5110
    */
    void LevelCompleted(N5110 &lcd,Gamepad &pad);

private:

    Direction _d;
    float _t;
    float _T;
    float _t1;
    float _fps;
    Vector2D _pos;
    int _won;
    int _bullet_number;
    int _death;
    int _percentage1;
    int _percentage2;
    int _percentage3;
    
    int _level;
    int _bullets_left;
    
    int _MAX_WIDTH;
    int _MIN_WIDTH;
    int _MAX_HEIGHT;
    int _MIN_HEIGHT;
    
    int _MIN_VIRUS_Y1;
    int _MAX_VIRUS_Y1;
    int _MIN_VIRUS_Y2;
    int _MAX_VIRUS_Y2;
    
    vector<Obstacle> myObstacles;
    vector<Enemy> myVirus;
    vector<Bullet> myBullet;
    
    Player _p; //object of player class
    
    void Bullet_Virus_Detect();
    bool check_collision(float x, float y);
    int _collision;
    
};
#endif