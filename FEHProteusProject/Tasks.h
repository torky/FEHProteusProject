#ifndef TASKS_H
#define TASKS_H

 // TASKS_H

static const int TOP = 1;
static const int BOTTOM = 0;
static const int TOP_TO_BOTTOM = 5;
static const int BOTTOM_TO_TOP = 4;
static const int SAME = 3;

void startWait(){
    while(readLight(midOpt) != 'r');
}

void ascendRamp(){
    //Move forward
    move(10, 75);
    //Straighten out robot
    float data[3];
    getRPSData(data);
    if(data[2] > 4 && data[2] < 361){
        turn(-data[2], 10);
    }
}

void pushButtons(){
    //Move to buttons
    //Read light
    char color = readLight(midOpt);
    //Move based on color
    if(color == 'r'){

    }else if(color == 'b'){

    }else if(color == 'n'){

    }else{

    }
    //reverse to get on line

}

void approachRamp(){
    //Move to the ramp
    //Center robot and line up properly
}

void faceNorth(){
    float data[3];
    LCD.WriteLine("Angle is:");
    getRPSData(data);
    LCD.WriteLine(data[2]);
    //Convert from the RPS cycle to the turning cycle
    if(data[2] > 180){
        LCD.WriteLine((data[2]-360));
        turn((data[2]-360), 10);
    }else{
        turn(data[2], 10);
        LCD.WriteLine(data[2]);
    }
}

//Determine if you are on the top or bottom
int determineLocation(int xLocation, int yLocation){

}

void moveToPoint(int x, int y, int xLocation, int yLocation){

    int startingLocation = determineLocation(xLocation, yLocation);
    int destination = determineLocation(x, y);
    int traversingRamp;

    //determine movement pattern
    if(startingLocation>destination){
        traversingRamp = TOP_TO_BOTTOM;
    }else if(startingLocation>destination){
        traversingRamp = BOTTOM_TO_TOP;
    }

    //move
    switch (traversingRamp){
        case TOP_TO_BOTTOM:

        case BOTTOM_TO_TOP:

        case SAME:

    }
}

#endif
