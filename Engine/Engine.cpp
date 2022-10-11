#include "Engine.h"

// contrustor and destructor
Engine::Engine()
{

}

Engine::~Engine()
{

}



void Engine::percentages_init() {
    
    // initialize all percentages to 0
    _percentage1 = 0;
    _percentage2 = 0;
    _percentage3 = 0;
    
}

void Engine::init(float fps) {
    
    _fps = fps;
    _T = 1/fps;
    _t = 0;       // time game has run for
    _won = 0;
    _collision = 0;
    _level = 0;
    _death = 0; // 0 - alive, 1 - died from obstacle, 2 - died from virus
    _bullets_left = 50; // for level 3
    
    _p.init();
    
    // clear all elements in vectors
    myObstacles.clear();
    myVirus.clear();
    myBullet.clear();
    
    srand(time(NULL)); //for random number gens
    
    _MAX_WIDTH = 11; //max and min widths and heights of obstacle
    _MIN_WIDTH = 7;
    _MAX_HEIGHT = 12;
    _MIN_HEIGHT = 9;
    
    _MIN_VIRUS_Y1 = 20; // max and min jump virus y-spawns
    _MAX_VIRUS_Y1 = 25;
    _MIN_VIRUS_Y2 = 36; // max and min duck virus y-spawns
    _MAX_VIRUS_Y2 = 38;
    
}

void Engine::AddObstacle() {
    
    int obstacle_height = rand() % _MAX_HEIGHT; // randomise a value between 0 and 19
    if ( obstacle_height < _MIN_HEIGHT ) {
        obstacle_height = _MIN_HEIGHT; //make sure height doesnt go below minimum
    }
    int obstacle_width = rand() % _MAX_WIDTH;
    if ( obstacle_width < _MIN_WIDTH) {
        obstacle_width = _MIN_WIDTH; //make sure width does not go below minimum
    }
    int obstacle_x = 83; // initialize x-coordinate of obstacle at x = 83 i.e end of screen
    int obstacle_y1 = 45 - obstacle_height; //jump obstacle
    int obstacle_y2 = 34 - obstacle_height; //duck obstacle
            
    int j_or_d = rand() % 3; //randomise between 0 or 2 - 0/1 is a jump obstacle and 2 is an obstacle to duck - 1/3 chance for duck and 2/3 chance for jump obstacle
#ifdef CHECK_J_OR_D

    printf("J_OR_D = %d\n",j_or_d); //check randomised value

#endif
    if(j_or_d < 2) {
        Obstacle newObstacle1(obstacle_x,obstacle_y1,obstacle_height,obstacle_width);
        myObstacles.push_back(newObstacle1); //jump obstacle
    } else {  
        Obstacle newObstacle2(obstacle_x,obstacle_y2,obstacle_height,obstacle_width);
        myObstacles.push_back(newObstacle2); //duck obstacle
    }
    
}

void Engine::AddVirus() {
    
    int virus_x = 83; // initialize x-coordinate at beginning of screen
            
    int virus_y1 = rand() % _MAX_VIRUS_Y1; //randmise value between 0 and maxY1
    if (virus_y1 < _MIN_VIRUS_Y1) { // make sure y doesnt go below minimum
        virus_y1 = _MIN_VIRUS_Y1;
    }
                
    int virus_y2 = rand() % _MAX_VIRUS_Y2; //randmose value between 0 and maxY2
    if (virus_y2 < _MIN_VIRUS_Y2) { // make sure y doesnt go below minimum
        virus_y2 = _MIN_VIRUS_Y2;
    }
    
    int j_or_d = rand() % 2; //randomise between 0 or 1 - 0 is a jump virus and 1 is a duck
        
    if(j_or_d == 0) {  
        Enemy newVirus(virus_x,virus_y1);
        myVirus.push_back(newVirus);
    } else {
        Enemy newVirus(virus_x,virus_y2);
        myVirus.push_back(newVirus);
    }
}

void Engine::AddBullet() {
    
    // shoot at the end of gun
    int bullet_x = _pos.x + 6;
    int bullet_y = _pos.y + 4;
    // add new bullet to vector
    Bullet newBullet(bullet_x,bullet_y);
    myBullet.push_back(newBullet);
    
}

void Engine::PrintObstacles(N5110 &lcd) {
    
    for (int i = 0; i < myObstacles.size(); i++) {      // iterate through members and print
        myObstacles[i].Spawn(lcd);
        int new_obstacle_x = myObstacles[i].get_x();
        if (new_obstacle_x <= 0) {                       // check if x has surpassed screen width - delete obstacle from vector
            myObstacles.erase(myObstacles.begin() + i);
        } else {
            myObstacles[i].set_x(new_obstacle_x -= 1);    // otherwise move obstacle at a speed of 1 to the left
        }
    }
    
}

void Engine::PrintVirus(N5110 &lcd) {
    
    for (int i = 0; i < myVirus.size(); i++) {         // iterate through members and print 
        myVirus[i].Spawn(lcd);
        int new_virus_x = myVirus[i].get_x();
        if (new_virus_x <= 0) {                        // check if x has surpassed screen width - delete obstacle from vector
            myVirus.erase(myVirus.begin() + i);
        } else {
            myVirus[i].set_x(new_virus_x -= 1);       // otherwise move obstacle at a speed of 1 to the left
        }
    }
    
    
}

void Engine::PrintBullets(N5110 &lcd) {
    
    for (int i = 0; i < myBullet.size(); i++) {      // iterate through members and print   
        myBullet[i].Spawn(lcd);
        int new_bullet_x = myBullet[i].get_x();
        if (new_bullet_x >= 83) {                    // check if x has surpassed screen width - delete obstacle from vector
            myBullet.erase(myBullet.begin() + i);
        } else {
            myBullet[i].set_x(new_bullet_x += 2);    // otherwise move obstacle at a speed of 2 to the right
        }
    }
    
}

bool Engine::check_collision(float x, float y) {    // returns true if collided and sets value of death variable
    
    for (int i = 0; i < myObstacles.size(); i++) { //iterate through obstacles
       
        if (
            //                                 compare back of player against obstacle                                                                      compare face of player with obstacle
            (((x >= myObstacles[i].get_x()) && (x <= (myObstacles[i].get_x()+ myObstacles[i].get_width()))) || (((x + 2) >= myObstacles[i].get_x()) && ((x + 2) <= (myObstacles[i].get_x()+ myObstacles[i].get_width())))) && 
            //                                     compare head with face of obstacle                                                                        compare legs of player against obstacle
            (((y >= myObstacles[i].get_y()) && (y <= (myObstacles[i].get_y() + myObstacles[i].get_height()))) || (((y + 9) >= myObstacles[i].get_y()) && ((y + 9) <= (myObstacles[i].get_y() + myObstacles[i].get_height()))))
            
        ) { 
            _collision = 1;
            _death = 1;
            break; //exit for loop
            
        }
    }
    
    for (int i = 0; i < myVirus.size(); i++) { //iterate through virus
       
        if (
            //                                 compare back of player against virus                                                                      compare face of player with virus
            (((x >= myVirus[i].get_x()) && (x <= (myVirus[i].get_x()+ myVirus[i].get_width()))) || (((x + 2) >= myVirus[i].get_x()) && ((x + 2) <= (myVirus[i].get_x()+ myVirus[i].get_width())))) && 
            //                                     compare head with face of virus                                                                        compare legs of player against virus
            (((y >= myVirus[i].get_y()) && (y <= (myVirus[i].get_y() + myVirus[i].get_height()))) || (((y + 9) >= myVirus[i].get_y()) && ((y + 9) <= (myVirus[i].get_y() + myVirus[i].get_height()))))
            
        ) { 
            _collision = 1;
            _death = 2;
            break; //exit for loop
            
        }
        
    }
    
        
    if (_collision == 1) {
        return true;
    } else {
        return false;
    }
}

void Engine::Bullet_Virus_Detect() {  // detects virus-bullet collision
       
    for ( int i = 0; i < myBullet.size(); i++) {  
    
        if (
            //      check x of bullet with x of virus           check y of bullet is within range of virus face     
            (myBullet[i].get_x() - myVirus[i].get_x() > -1) && ((myBullet[i].get_y() <= (myVirus[i].get_y() + myVirus[i].get_height())) && (myBullet[i].get_y() >= myVirus[i].get_y()))
            
            ) {
                
                myBullet.erase(myBullet.begin() + i); // if collided, delete both bullet and virus
                myVirus.erase(myVirus.begin() + i);
            }
    }
    
}

float Engine::get_T() {
    
    return _T;
    
}

int Engine::get_won() {
    
    return _won;
    
}

void Engine::set_level(int n) {
    
    _level = n;
    
}

int Engine::get_level() {
 
    return _level;   
    
}

void Engine::print_percentage1(int x, int l, N5110 &lcd) {
    
    char buffer[14];
        
    sprintf(buffer,"%d",_percentage1);
        
    lcd.printString(buffer,x,l);
    lcd.printString("%",x+18,l);
    
}
    
void Engine::print_percentage2(int x, int l, N5110 &lcd) {
    
    char buffer[14];
        
    sprintf(buffer,"%d",_percentage2);
        
    lcd.printString(buffer,x,l);
    lcd.printString("%",x+18,l);
    
}

void Engine::print_percentage3(int x, int l, N5110 &lcd) {
    
    char buffer[14];
        
    sprintf(buffer,"%d",_percentage3);
        
    lcd.printString(buffer,x,l);
    lcd.printString("%",x+18,l);
    
}

void Engine::ReadUserInput(Gamepad &pad) {
    
    _d = pad.get_direction();
    
}

void Engine::StartGame(N5110 &lcd,Gamepad &pad) {
        
#ifdef CHECK_STARTGAME

    printf("Start game initiated\n"); //check to see if the function has initiated

#endif

    if(_level == 1 && _percentage1 == 0) {  // play cut scene at level 1. Check if played already
        IntroScene(lcd,pad);  
    }
    
    do { 
    
        _pos = _p.get_pos();
        lcd.clear();
        
        lcd.drawLine(0,45,84,45,2);
        lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);
        _p.Run(_t,lcd,pad);
        
        // display different texts at different levels
        
        if(_level == 1) {
            
            lcd.printString("Avoid",2,1);
            lcd.printString("Obstacles!",2,2);
            
        } else if (_level == 2) {
            
            lcd.printString("Virus is",17,1);
            lcd.printString("appearing now",2,2);
            
        } else if (_level == 3) {
        
            lcd.printString("Running low",2,1);
            lcd.printString("on Dettol...",2,2);
            
        }
        
        _p.set_x_pos(_pos.x+=1); //run to x = 20 to start game
        
        if(_pos.x == 20) {
            pad.led(1,1);
            pad.led(4,1);
            pad.tone(750.0,0.5);
            wait(1);
            pad.led(2,1);
            pad.led(5,1);
            pad.tone(750.0,0.5);
            wait(1);
            pad.led(3,1);
            pad.led(6,1);
            pad.tone(2000.0,0.5); // ready, set, go
        }
        
        lcd.refresh();
        _t = _t + _T;
        wait(_T);
        pad.leds_off();
        
    } while(_pos.x <= 20);   
}

void Engine::GameOver(N5110 &lcd, Gamepad &pad) {
    
    lcd.clear();
    
    if (_death == 1) {
        
        lcd.printString("Ouch!",30,1);
        lcd.printString("Bones",29,2);
        lcd.printString("Broken...",25,3);
        
    } else if (_death == 2) {
        
        lcd.printString("Infected!",16,1);
        lcd.printString("Go Quarantine",4,2);
        lcd.printString("Yourself!",16,3);
        
    }
    
    // display percentage completed
    
    lcd.printString("Percent = ",0,5);
    
    if(_level == 1) {
        print_percentage1(60,5,lcd);
    } else if(_level == 2) {
        print_percentage2(60,5,lcd);
    } else {
        print_percentage3(60,5,lcd);
    }
    
    lcd.refresh();  
    
    //sad tone
    
    pad.tone(200.0,0.5);
    wait(0.5);
    pad.tone(100.0,0.5);
    wait(0.5);
    pad.tone(50.0,0.5);
    wait(0.5);
    
    while(1) {
        pad.led(1,1);
        wait(0.3);
        pad.leds_off();
        pad.led(4,1);
        wait(0.3);
        pad.leds_off();
        if(pad.Y_pressed()) {
            break;
        }
    }   
    
}
void Engine::IntroScene(N5110 &lcd,Gamepad &pad) {

        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.refresh();
        wait(0.5);
        lcd.printString("I'm wanted?",19,1);
        lcd.refresh();
        wait(2.0);
        lcd.printString("Hello,",6,4);
        lcd.printString("Agent 00-C.",0,5);
        lcd.refresh();
        wait(3.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("I am Dr.",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("Zhirkov",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("with the",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("WHO.",8,5);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("A cure",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("has said",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("to have",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("been found.",0,5);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("I see.",19,1);
        lcd.refresh();
        wait(1.0);
        lcd.printString("What",58,1);
        lcd.refresh();
        wait(0.5);
        lcd.printString("brings me?",19,2);
        lcd.refresh();
        wait(2.0);
        lcd.printString("Deliver it",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("to Helsak",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("Hospital",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("ASAP!",0,5);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("There are",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("2 doctors",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("over there",0,4);
        lcd.refresh();
        wait(0.8);
        lcd.printString("who go by",0,5);
        lcd.refresh();
        wait(0.8);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("the names",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("of",0,5);
        lcd.refresh();
        wait(0.8);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("Richtofen",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("and",0,5);
        lcd.refresh();
        wait(0.8);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("Ittihad.",0,4);
        lcd.refresh();
        wait(2.0);
        lcd.printString("They will",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("be",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("expecting",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("you.",0,4);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("Got it.",19,1);
        lcd.refresh();
        wait(1.0);
        lcd.printString("No worries.",19,2);
        lcd.refresh();
        wait(1.0);
        lcd.printString("You will",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("face",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("some",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("challenges.",0,5);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("It's best",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("you go",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("prepared.",0,4);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.drawRect(43,14,41,10,FILL_BLACK);
        lcd.drawSprite(33,2,29,12,(int *)Cure);
        lcd.refresh();
        wait(0.5);
        lcd.printString("Here.",0,4);
        lcd.refresh();
        wait(0.8);
        lcd.printString("Take this.",0,5);
        lcd.refresh();
        wait(0.8);
        lcd.drawRect(0,14,18,10,FILL_BLACK);
        lcd.refresh();
        wait(1.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("Got your",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("dettol?",0,5);
        lcd.refresh();
        wait(1.0);
        lcd.printString("I am",19,1);
        lcd.printString("Ready.",19,2);
        lcd.refresh();
        wait(1.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("I am",19,1);
        lcd.printString("Ready.",19,2);
        lcd.printString("Good luck",0,4);
        lcd.printString("Agent",0,5);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.printString("Operation",15,1);
        lcd.printString("COVID",27,2);
        lcd.printString("has",33,3);
        lcd.printString("Commenced..",10,4);
        lcd.refresh();
        wait(3.0);
    
}

void Engine::EndScene(N5110 &lcd,Gamepad &pad) {
    
    lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(57,25,20,17,(int *)Doc);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.refresh();
        wait(0.5);
        lcd.printString("I have",19,1);
        lcd.printString("arrived..",19,2);
        lcd.refresh();
        wait(2.0);
        lcd.printString("Hello,",6,4);
        lcd.printString("Agt 00-C.",0,5);
        lcd.refresh();
        wait(3.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(57,25,20,17,(int *)Doc);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("We were",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("expecting",0,5);
        lcd.refresh();
        wait(0.5);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(57,25,20,17,(int *)Doc);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("you.",0,4);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(57,25,20,17,(int *)Doc);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("Got the",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("cure?",0,5);
        lcd.refresh();
        wait(2.0);
        lcd.clear();
        lcd.drawRect(0,14,18,10,FILL_BLACK);
        lcd.drawSprite(9,2,29,12,(int *)Cure);
        lcd.refresh();
        wait(0.5);
        lcd.printString("There you",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("go..",0,5);
        lcd.refresh();
        wait(0.8);
        lcd.drawRect(43,10,41,10,FILL_BLACK);
        lcd.drawRect(43,23,41,10,FILL_BLACK);
        lcd.refresh();
        wait(3.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(57,25,20,17,(int *)Doc);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("Well done",0,4);
        lcd.refresh();
        wait(0.5);
        lcd.printString("brave one",0,5);
        lcd.refresh();
        wait(3.0);
        lcd.printString("Exactly",19,1);
        lcd.printString("you..",19,2);
        lcd.refresh();
        wait(3.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(57,25,20,17,(int *)Doc);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("Who is",19,1);
        lcd.printString("reading ",19,2);
        lcd.printString("on the",0,4);
        lcd.printString("screen.",0,5);
        lcd.refresh();
        wait(3.0);
        lcd.clear();
        lcd.drawSprite(0,3,22,17,(int *)Agent);
        lcd.drawSprite(57,25,20,17,(int *)Doc);
        lcd.drawSprite(65,28,20,17,(int *)Doc);
        lcd.printString("WELL ",19,1);
        lcd.printString("DONE!",19,2);
        lcd.refresh();
        wait(1.0);
        lcd.printString("You can ",0,4);
        lcd.printString("rest..",0,5);
        lcd.refresh();
        wait(1.0);
        
        
}
void Engine::LevelCompleted(N5110 &lcd,Gamepad &pad) {
    
    lcd.clear();
    if(_percentage1 == 100 && _percentage2 == 100 && _percentage3 == 100) {  // end scene if all completed
        EndScene(lcd,pad);
    } else {
        lcd.printString("LEVEL",27,2);
        lcd.printString("COMPLETED!",14,3);
    }
    
    // happy tone
    
    lcd.refresh(); 
    pad.tone(500.0,0.5);
    wait(0.5);
    pad.tone(1000.0,0.5);
    wait(0.5);
    pad.tone(1500.0,0.5);
    wait(0.5);
    
    while(1) {
        pad.leds_on();
        wait(0.3);
        pad.leds_off();
        wait(0.3);
        if(pad.Y_pressed()) {
            break;
        }
    }   
}

void Engine::UpdateGame(N5110 &lcd, Gamepad &pad) {
    
    lcd.clear();   
    _pos = _p.get_pos();
    lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);
    _p.ground_anim(_t,lcd);
    
    
    int T2 = _t*20; // change to a whole number
#ifdef CHECK_T2
    
    printf("T2 = %d\n",T2); //print to check correct value is calculated
    
#endif 

    if (T2%40 == 0 && _p.get_progress() < 1100) { //every 1 second add an obstacle, but not until end of game
    
        AddObstacle();
#ifdef CHECK_OBSTACLE
    
        printf("Obstacle Spawned\n"); //print to check how often obstacles are spawned
    
#endif 
    }
    
    if(_level > 1) { //Virus and bullets used only in level 2 and 3
    
        if ((rand() % 100) < 2 && _p.get_progress() < 1100) { //  2% spawn rate
        
            AddVirus();
        
        }
        if (_bullets_left > 0) { //only shoot if there are bullets 
            if (pad.B_pressed()) {
                pad.tone(1000.0,0.1);
                AddBullet();
                if(_level == 3) { //reduce bullets in level 3
                    _bullets_left -= 1;
                }
            }
        }
    }
    
    if (_level == 3) {  // print how mant bullets left
        
        char buffer[14];
        sprintf(buffer,"%d",_bullets_left);
        lcd.printString("Bullets = ",2,1);
        lcd.printString(buffer,64,1);
    }
    
    if (pad.A_pressed() && _pos.y == 33) { //only jump if button pressed and player is on ground
            
        _p.Jump(_t1,_T); // alter values of G and vy, initiate t1
        
    }
#ifdef CHECK_JUMP

    printf("t1 = %.2f, G = %d, vy = %d\n",_t1,_p.get_grav(),_p.get_y_vel()); // check t if initiated

#endif
        
    if (_d == S) { // duck when analog is south
                
        _p.Duck(_t,lcd);
                
    } else {
            
        int uy = ceil(0.5*(_p.get_grav())*pow(_t1,2) + _p.get_y_vel()*_t1); // y-displacement rounded up by ceil() function to the nearest integer due to pixels.
        _p.set_y_displacement(uy);
        _p.Run(_t,lcd,pad);
            
    }
        
    Bullet_Virus_Detect();
    
    // print 
    
    PrintObstacles(lcd);
    PrintVirus(lcd);
    PrintBullets(lcd);
        
#ifdef CHECK_Y

    printf("Y = %.2f\n",_pos.y); // check y in case of jump or duck

#endif

    if (check_collision(_pos.x,_pos.y)) {
        _won = 1;                                // lost
    }
    
    _p.progress(lcd);
        
    if (_p.get_progress() == 1200) { //once progress bar is full, level finished
        _won = 2;
    }
    
    if(_level == 1) {
        _percentage1 = (_p.get_progress()*100)/1200;
    } else if(_level == 2) {
        _percentage2 = (_p.get_progress()*100)/1200;
    } else {
        _percentage3 = (_p.get_progress()*100)/1200;
    }
        
    if (_pos.y < 33) {
        _t1 = _t1 + _T; //increment time for jump
    }
    
    _t += _T; //increment time
    lcd.refresh(); // refresh the LCD so all the pixels appear
        
}
