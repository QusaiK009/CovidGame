#ifndef INTRO_H
#define INTRO_H

const int Agent [22][17] = {
    
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},  
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},  
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},  
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},  
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},  
    {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},  
    {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},  
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},  
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},  
    
};

const int Doc [20][17] = {
    
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  
    {1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1},  
    {1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},  
    {1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},  
    {1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1},  
    {1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1},  
    {1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1},  
    {1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1},  
    {1,1,1,0,0,0,0,0,0,1,1,0,0,1,1,1,1},  
    {1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1},  
    {1,1,1,1,0,0,0,0,0,1,1,0,0,0,1,1,1},  
    {1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},  
    {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},  
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},  
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},   
    
};

const int Cure [29][12] = {
    
    {1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,0,1,0,0,0,0,0,0,1,0,0},
    {0,0,1,0,0,0,0,0,0,1,0,0},
    {0,0,0,1,1,1,1,1,1,0,0,0},
    
};



#endif