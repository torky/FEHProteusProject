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
    rotateMagnet(GRAB_DUMBBELL);
    Sleep(1000);
    move(3, 25);
    Sleep(1000);
    rotateMagnet(0);
    Sleep(1000);
}

void scrapeDumbbell(){
    Sleep(500);
    rotateMagnet(100);
    Sleep(200);
    move(5, 35);
    Sleep(200);
    rotateMagnet(30);
    Sleep(200);
    timedMove(500, -50);

    rotateMagnet(100);
    Sleep(200);
    rotateMagnet(30);
    Sleep(200);
    move(5, 35);

}
void doLever(bool direction){
    if(!direction){
        LCD.WriteLine("Forward");
        cardArm.SetDegree(15.0);
        Sleep(300);
        moveNoRPS(2, 35);
        //Return to back
        moveNoRPS(7, -35);
        cardArm.SetDegree(100.0);
    }else{
        LCD.WriteLine("Backward");
        moveNoRPS(2, 35);
        cardArm.SetDegree(15.0);
        LCD.WriteLine("Position to Pull Backward");
        Sleep(1000);
        moveNoRPS(1.5, -25);
        cardArm.SetDegree(100.0);
        moveNoRPS(1.5, 25);
        LCD.WriteLine("Pulled and lfted");
        Sleep(1000);
        //Return to back
        moveNoRPS(7, -35);
    }
}

void doLevers(){
    //Get data
    float pos[3];
    getRPSData(pos);
    //Align behind 1
    turn(5, 35);
    Sleep(1000);
    moveNoRPS(5.5, 35);
    Sleep(1000);
    if(pos[2] > 0){
        faceAngle2(180);
    }else{
        turn(-2, 35);
    }
    //Now is aligned behind lever one
    bool data[3];
    getLeverData(data);
    Sleep(2000);

    //Do one
    doLever(data[0]);

    //Go to two
    Sleep(1000);
    turn(-90, 25);
    Sleep(500);
    moveNoRPS(3, 35);
    Sleep(500);
    turn(90, 25);
    Sleep(1000);
    //approach distance
    moveNoRPS(5, 35);

    //Do two
    doLever(data[1]);

    //Go to three
    Sleep(1000);
    turn(-90, 25);
    Sleep(500);
    moveNoRPS(3, 35);
    Sleep(500);
    turn(90, 25);
    faceAngle2(180);
    Sleep(1000);
    //approach
    moveNoRPS(4.5, 35);

    //do three
    doLever(data[2]);
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

//////////////////////////////////Calibrate with RPS (needs work)
void scanForLight(){

    Sleep(150);
    int left = 0;
    float color = 0;
    float timeStart = TimeNow();

    leftMotor.SetPercent(25);
    rightMotor.SetPercent(25);
    float a = fuelLight[0]-RPS.X();
    float b = fuelLight[1]-RPS.Y();
    float inches = sqrt(a*a+b*b);
    float angle = acos(a/inches);
    float angleDegrees = angle/PI*180;
    //normalize angle for our robot
    angleDegrees+=270;
    //fix angle if it's not between 0 and 360
    if(angleDegrees>360){
        angleDegrees-=360;
    }else if(angleDegrees <0){
        angleDegrees+=360;
    }

    Sleep(200);
    //faceAngle(angleDegrees);

    int counts = inches * COUNTS_PER_INCH;
    rightMotor.SetPercent(20);
    leftMotor.SetPercent(20);
    while((leftEnc.Counts() + rightEnc.Counts()) / 2. < counts){
        LCD.WriteLine(CdSButtonSensor.Value());
        if(CdSButtonSensor.Value()<MAX_RED_COLOR+.2){
            rightMotor.Stop();
            leftMotor.Stop();
            return;
        }
    }



    //while(color == 0&&TimeNow()-timeStart<10){
    /*
        if(color!=0){
            return;
        }

        //turn right once
        turn(2, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            return;
        }

        //turn right twice
        turn(2, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            return;
        }

        //turn left once
        turn(-1, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            return;
        }

        //turn left twice
        turn(-1, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            return;
        }

        //turn left thrice
        turn(-1, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            return;
        }

        //turn left a fourth time
        turn(-1, 25);
        Sleep(1000);
        color = determineColor();
        if(color!=0){
            return;
        }
        moveNoRPS(.1,-25);
    /*
        //Check RPS if this fails
        Sleep(500);

        float fuelLightMaxX = fuelLight[0]+.4;
        float fuelLightMinX = fuelLight[0]-.4;
        float fuelLightMaxY = fuelLight[1]+.4;;
        float fuelLightMinY = fuelLight[1]-.4;;
        color = determineColor();
        if(color!=0){
            return;
        }

        /*
        if(RPS.X()<fuelLightMaxX&&RPS.X()>fuelLightMinX){
            Sleep(500);
            color = determineColor();

            if(color!=0){
                return;
            }
            if(RPS.X()>fuelLight[0]){
                turn(-1,20);
            }else{
                turn(1, 20);
            }
        }
        */
        /*
        if(RPS.Y()<fuelLightMaxY&&RPS.Y()>fuelLightMinY){
            Sleep(500);
            color = determineColor();

            if(color!=0){
                return;
            }

            if(RPS.Y()>fuelLight[1]){
                move(.125, -20);
            }else{
                move(.125, 20);
            }
        }

    //*/

        /*
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
            return;
        }*/
    /*}

    if(TimeNow()-timeStart>10){
        timedMove(500,25);
        timedMove(5500,10);
    }*/

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

char colorString;

void pushButtons2(){
    //bool retry = true;
    //int count = 0;
    //do{
        //Read light
    Sleep(200);
        float color = determineColor();
        //Move based on color
        //blue bottom
        if(color == BLUE_LIGHT_COLOR){
            LCD.WriteLine("BLUE");
            colorString = 'b';
            timedMove(500, 25);
            timedMove(5500, 10);
            moveNoRPS(5,-25);
            //retry = false;
        }else if(color == RED_LIGHT_COLOR){
            LCD.WriteLine("RED");
            move(4,-25);
            cardArm.SetDegree(7);
            faceAngle2(0);
            Sleep(500);
            timedMove(300, 25);
            timedMove(700, 10);
            Sleep(5500);
            colorString = 'r';
            //retry = false;
        }else {
            LCD.WriteLine("We failed: DEFAULT BLUE");
            colorString = 'b';
            timedMove(500, 25);
            timedMove(5500, 10);
            moveNoRPS(5,-25);
            //retry = false;
        }
    //}while(retry && count < 5);

    //If the light was never found, default to blue
    //if(retry){
        //LCD.WriteLine("Default guess");
        //timedMove(500, 25);
        //timedMove(6000, 10);
    //}
    cardArm.SetDegree(120);

    //reverse to get on line

}
#endif
