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
    moveNoRPS(10, 35);
    LCD.WriteLine("Turn 90");
    turn(-90, 25);
    faceNorth();
}
void startToDumbbellAlign(){
    LCD.WriteLine("Move 16");
    moveNoRPS(16, 25);
    Sleep(1000);
    LCD.WriteLine("Face 270");
    faceAngle(270);
    Sleep(1000);
    LCD.WriteLine("Move 5");
    moveNoRPS(5, 35);
    Sleep(2000);
    LCD.WriteLine("Turn 90");
    turn(-90, 25);
    faceNorth();
}

void approachDumbbell(){
    moveNoRPS(10, -25);
    faceNorth();
}
void grabDumbbell(){
    rotateMagnet(120);
    Sleep(1000);
    rotateMagnet(5);
    Sleep(1000);
}
void approachRamp(){
    //Move to the ramp
    moveNoRPS(16, 30);
    faceNorth();
    //Center robot and line up properly
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
}
void scrapeDumbbell(){
    //lower arm
    rotateMagnet(15);
    Sleep(1000);
    //move forward a bit
    moveNoRPS(6, 35);
}

void pushButtons(){
    //Move to buttons
    faceNorth();
    //push a button
    moveNoRPS(8, 25);
    faceNorth();
    //Change this so it is over light
    moveNoRPS(7.0, 25);

    //dirty button press
    timedMove(1000, 20);
    Sleep(5000);

    //True press
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
#endif
