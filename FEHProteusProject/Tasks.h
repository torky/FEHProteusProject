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
    rotateMagnet(115);
    Sleep(1000);
    move(3, 25);
    Sleep(1000);
    rotateMagnet(0);
    Sleep(1000);
}

void scrapeDumbbell(){
    rotateMagnet(100);
    Sleep(1000);
    move(5, 35);
    Sleep(1000);
    rotateMagnet(30);
    Sleep(1000);
    timedMove(1000, -35);
    move(5, 35);

}

void approachRamp(){
    //Move to the ramp
    moveNoRPS(12, 30);
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

void scanForLight(){

    int left = 0;
    float color = 0;
    while(color == 0){

        if(color!=0){
            break;
            break;
        }

        //turn right once
        turn(2, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            break;
            break;
        }

        //turn right twice
        turn(2, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            break;
            break;
        }

        //turn left once
        turn(-1, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            break;
            break;
        }

        //turn left twice
        turn(-1, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            break;
            break;
        }

        //turn left thrice
        turn(-1, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            break;
            break;
        }

        //turn left a fourth time
        turn(-1, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            break;
            break;
        }


        //move jaggedly back and forth
        if(left<=2){
            //go left
            turn(1,25);
            left++;
            color = determineColor();
            Sleep(1000);
        }else if(left<=6){
            turn(-1,25);
            left++;
            color = determineColor();
            Sleep(1000);

        }else{
            left = -2;
        }
        if(color!=0){
            break;
            break;
        }
    }

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

void pushButtons2(){
    //Read light
    float color = determineColor();
    //Move based on color
    //blue bottom
    if(color == BLUE_LIGHT_COLOR){
        LCD.WriteLine("BLUE");
        timedMove(500, 25);
        timedMove(5000, 10);
    }else if(color == RED_LIGHT_COLOR){
        LCD.WriteLine("RED");
        move(4,-25);
        cardArm.SetDegree(10);
        faceAngle2(0);
        Sleep(1000);
        timedMove(500, 25);
        Sleep(5000);

    }else if(color == 0){
        LCD.WriteLine("We failed");
    }

    cardArm.SetDegree(120);

    //reverse to get on line

}
#endif
