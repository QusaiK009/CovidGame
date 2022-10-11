/*
ELEC2645 Embedded Systems Project
School of Electronic & Electrical Engineering
University of Leeds
2019/20

Name: Qusay Khshman
Username: el18qk
Student ID Number: 201236370
Date: 31/03/2020
*/

// includes
#include "mbed.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "melody.h"
#include "Gamepad.h"
#include "N5110.h"

//objects
Gamepad pad;
N5110 lcd;
Engine OperationCovid;
Player p;

//function prototypes
void StartGame();
void MainMenu();
void DrawGameBoard();
void Arrowfront(int x,int y);
void Arrowback(int x, int y);
void Tutorial();
void Selection_Menu();
void GameLoop();


const int VIRUS[14][29] = {
    
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0},
    {0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0},
    {1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,1,1,0},
    {1,1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0},
    {0,1,1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0},
    {0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,1,1},
    {0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,1,1},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
    {0,1,1,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0},
    {0,1,1,1,1,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0},
    
};

int main() {
    
    OperationCovid.percentages_init(); // initialize percentages
    
    while(1) {
        
        OperationCovid.init(20.0); //initialize with 20 fps
        lcd.init();
        pad.init();
        lcd.setContrast(0.55);
        MainMenu();
        
        OperationCovid.StartGame(lcd,pad);
        GameLoop();
        
        if (OperationCovid.get_won() == 2) {
            OperationCovid.LevelCompleted(lcd,pad);
        } else if (OperationCovid.get_won() == 1) {
            OperationCovid.GameOver(lcd,pad);
        }
        wait(0.1);
    }
}

void GameLoop() {
    
    float T = OperationCovid.get_T();
    int t = 0;
    bool playMusic = true;
    // play background music
    int n = sizeof(note_array)/sizeof(int);
    
    while(1) {
        
        OperationCovid.ReadUserInput(pad);
        OperationCovid.UpdateGame(lcd,pad);
        
        if(pad.X_pressed()) {
            playMusic = !playMusic;  // mute or unmute music
        }
        
        if(playMusic) {
            if(t%80 == 0) {  // every 4 seconds since melody lasts 4 seconds
                pad.play_melody(n,note_array,duration_array,120.0,false);
            }
        }
    
        if(OperationCovid.get_won() > 0) { //break loop when won has 1 or 2
            break;
        }
        t += (T*20);
        wait(T);
    }

}

void DrawGameBoard() {
    
     // board outline
    lcd.drawRect(20,2,44,44,FILL_TRANSPARENT);
    // leds
    lcd.drawCircle(28,6,1,FILL_TRANSPARENT);
    lcd.drawCircle(28,10,1,FILL_TRANSPARENT);
    lcd.drawCircle(28,14,1,FILL_TRANSPARENT);
    lcd.drawCircle(55,6,1,FILL_TRANSPARENT);
    lcd.drawCircle(55,10,1,FILL_TRANSPARENT);
    lcd.drawCircle(55,14,1,FILL_TRANSPARENT);
    //screen
    lcd.drawRect(34,4,16,16,FILL_TRANSPARENT);
    lcd.drawRect(36,6,12,4,FILL_BLACK);
    lcd.drawRect(36,10,12,7,FILL_TRANSPARENT);
    //Speaker + potentiometer
    lcd.drawCircle(59,19,3,FILL_TRANSPARENT);
    lcd.setPixel(59,17,true);
    lcd.setPixel(58,19,true);
    lcd.setPixel(60,19,true);
    lcd.setPixel(59,21,true);
    lcd.drawRect(52,21,4,4,FILL_TRANSPARENT);
    //buttons
    lcd.drawCircle(54,28,1,FILL_BLACK);
    lcd.drawCircle(54,36,1,FILL_BLACK);
    lcd.drawCircle(58,32,1,FILL_BLACK);
    lcd.drawCircle(50,32,1,FILL_BLACK);
    //lower pots
    lcd.drawRect(37,38,5,5,FILL_TRANSPARENT);
    lcd.drawRect(42,38,5,5,FILL_TRANSPARENT);
    lcd.setPixel(39,40,true);
    lcd.setPixel(44,40,true);
    //start and reset
    lcd.setPixel(34,41,true);
    lcd.setPixel(49,41,true);
    //analog
    lcd.drawRect(29,29,7,7,FILL_TRANSPARENT);
    lcd.drawCircle(32,32,1,FILL_BLACK);
    //extra peripherals connector
    lcd.drawLine(22,21,22,34,1);
    // screws for aesthetics
    lcd.setPixel(22,4,true);
    lcd.setPixel(22,43,true);
    lcd.setPixel(61,43,true);
    lcd.setPixel(61,4,true);
    
}

void Selection_Menu() {
    
    int x = 4; // initialize x at 4
    
    while (1) { 
    
        Direction joystick = pad.get_direction();
        lcd.clear();
        
        if (joystick == E) { // if joystick is to the right, scroll right
            x += 14;
            if(x > 60) {
                x = 60; //stop at third box
            } 
        } else if (joystick == W) {   // if joystick is to the right, scroll right
            x -= 14;
            if(x < 4) {
                x = 4; //stop at first box
            } 
        }
        
        if (x < 28) {
            // zoom lvl 1
            lcd.drawRect(2,0,24,39,FILL_TRANSPARENT);
            lcd.drawRect(32,2,20,35,FILL_TRANSPARENT);
            lcd.drawRect(60,2,20,35,FILL_TRANSPARENT);
        } else if (x > 28 && x < 56) {
            // zoom lvl 2
            lcd.drawRect(4,2,20,35,FILL_TRANSPARENT);
            lcd.drawRect(30,0,24,39,FILL_TRANSPARENT);
            lcd.drawRect(60,2,20,35,FILL_TRANSPARENT);
        } else if (x > 56) {
            // zoom lvl 3
            lcd.drawRect(4,2,20,35,FILL_TRANSPARENT);
            lcd.drawRect(32,2,20,35,FILL_TRANSPARENT);
            lcd.drawRect(58,0,24,39,FILL_TRANSPARENT);
        }
        
        // draw graphics for selection menu
        
        lcd.drawRect(17,22,7,12,FILL_BLACK);
        p.draw_a_sprite(6,23,1,lcd);
        lcd.drawLine(4,34,23,34,2);
        
        lcd.drawRect(44,5,8,15,FILL_BLACK);
        p.draw_a_sprite(34,25,4,lcd);
        Enemy Virus1(43,26);
        Virus1.Spawn(lcd);
        lcd.drawLine(32,34,51,34,2);
        
        lcd.drawRect(72,24,8,10,FILL_BLACK);
        p.draw_a_sprite(61,13,3,lcd);
        Enemy Virus2(72,13);
        Virus2.Spawn(lcd);
        lcd.drawRect(69,17,1,1,FILL_BLACK);
        lcd.drawLine(60,34,79,34,2);
        
        // print percentages:
        OperationCovid.print_percentage1(0,5,lcd);
        OperationCovid.print_percentage2(28,5,lcd);
        OperationCovid.print_percentage3(56,5,lcd);
        
        lcd.refresh();
        
        if(pad.start_pressed()) {  // go back to main menu
            break;
        }
        if (x < 28 && pad.X_pressed()) { //check which level is selected
            OperationCovid.set_level(1);
            break;
        } else if (x > 28 && x < 56 && pad.X_pressed()) {
            OperationCovid.set_level(2);
            break;
        } else if (x > 56 && pad.X_pressed()) {
            OperationCovid.set_level(3);
            break;
        } 
        
        wait(0.1);
    } 
    
}
void Arrowfront(int x,int y) {
    
    //  draw an arrow pointing forward
    lcd.drawLine(x,y,x+4,y,1);
    lcd.setPixel(x+2,y-2,true);
    lcd.setPixel(x+3,y-1,true);
    lcd.setPixel(x+3,y+1,true);
    lcd.setPixel(x+2,y+2,true);
    
}

void Arrowback(int x, int y) {
    
    //  draw an arrow pointing backward
    lcd.drawLine(x,y,x+4,y,1);
    lcd.setPixel(x+2,y-2,true);
    lcd.setPixel(x+1,y-1,true);
    lcd.setPixel(x+1,y+1,true);
    lcd.setPixel(x+2,y+2,true);
    
    
}
void MainMenu() {
    
    int y = 35;
    int t = 0;
    while(1){
        Direction joystick = pad.get_direction();
        lcd.clear();
        lcd.drawSprite(28,0,14,29,(int *)VIRUS);
        lcd.drawRect(2,14,80,11,FILL_TRANSPARENT);
        lcd.printString("OPRTN COVID",10,2);
        
        if (joystick == S) {
            y += 8;
            if(y > 43) {
                y = 43; //stop arrow at buttom option
            } 
        } else if (joystick == N) {
            y -= 8;
            if(y < 35) {
                y = 35; //stop at top option
            } 
        }
        
        if (t%2 == 0) {     //flash text
            if(y == 35) {
                lcd.printString("START GAME",15,4);
            } else {
                lcd.printString("TUTORIAL",15,5);
            }
        }
        
        if(y == 35) {
            lcd.printString("TUTORIAL",15,5); // keep text still
        } else {
            lcd.printString("START GAME",15,4);
        }
        
        Arrowfront(2,y);
        lcd.refresh();
        
        if (y == 35 && pad.Y_pressed()) {
            Selection_Menu();
            if(OperationCovid.get_level() > 0) {   // if an option has been selected start game
                break;
            }
        } else if (y == 43 && pad.Y_pressed()) {
            Tutorial();
        }
        
        t += 1;
        wait(0.1);
        
    }
    
}

void Tutorial() {
    
    int screen = 0; // variable for choosing screen
    
    while(1) {
     
        lcd.clear();
        if(pad.A_pressed()) {   // go forward
            screen += 1;
            if(screen > 2) {
                screen = 2;
            }
        } else if (pad.Y_pressed()) {   // go backward
            screen -= 1;
            if(screen < 0) {
                screen = 0;
            }
        }
        
        if (screen == 0) {
        
            DrawGameBoard();
            Arrowfront(72,24);
           
        } else if (screen == 1) {
            
            Arrowfront(72,6);
            lcd.drawRect(34,0,15,15,FILL_TRANSPARENT);
            lcd.drawCircle(41,3,1,FILL_BLACK);
            lcd.drawCircle(37,7,1,FILL_BLACK);
            lcd.drawCircle(45,7,1,FILL_BLACK);
            lcd.drawCircle(41,11,1,FILL_BLACK);
            Arrowback(9,6);
            
            lcd.printString("A(right):",0,2);
            lcd.printString("JUMP-all lvls",0,3);
            lcd.printString("B(bottom):",0,4);
            lcd.printString("SPRAY DETTOL",0,5);
            
        } else if (screen == 2) {
            
            lcd.drawRect(34,0,15,15,FILL_TRANSPARENT);
            lcd.drawCircle(41,7,4,FILL_BLACK);
            lcd.printString("Analog: ",0,3);
            lcd.printString("down to DUCK",0,5);
            Arrowback(9,6);
            
        }
        
        lcd.refresh();
        if(pad.start_pressed()) {
            break;
        }
        wait(0.1);
    }
    
}