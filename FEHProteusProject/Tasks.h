#ifndef TASKS_H
#define TASKS_H

 // TASKS_H

//Precondition: Robot is above light
void startWait(){
    while(readLight(CdS) != 'r');
}
//Precondition:  Robot is at start
//Postcondition: Robot is between the ramp and dumbbell, facing north
void startToRampAlign(){
    LCD.WriteLine("Move 16");
    moveNoRPS(16, 25);
    LCD.WriteLine("Turn 44 right");
    turn(44, 25);
    LCD.WriteLine("Move 10");
    moveNoRPS(10, 25);
    LCD.WriteLine("Turn 90");
    turn(-90, 25);
    faceNorth();
}
//Precondition:  Robot nubs are at ramp base
//Postconsition: Robot is at the top of the ramp
void ascendRamp(){
    faceNorth();

    //Go up ramp
    LCD.WriteLine("Move 10");
    moveNoRPS(10, 35);
    //Nubs over the lip
    Sleep(2000);
    LCD.WriteLine("TEST 1: Go over hump");
    //9 inches to power over
    moveNoRPS(9, 55);
    //Scooch forward
    moveNoRPS(1, 25);
    faceNorth();
    Sleep(500);
    faceNorth();
    Sleep(500);
    faceNorth();
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
#endif
