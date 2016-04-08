#ifndef TASKS_H
#define TASKS_H

 // TASKS_H

//Precondition: Robot is above light
void startWait(){
    float timeStart = TimeNow();
    while(readLight(CdS) != 'r'&&TimeNow()-timeStart<30){
        LCD.Write(CdS.Value());
        LCD.Write(", H:--");
        LCD.WriteLine(RPS.Heading());
    }
    LCD.Clear();
    LCD.Write("Light value is ");
    LCD.WriteLine(CdS.Value());

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
    Sleep(500);
    move(3, 25);
    Sleep(200);
    float timeStart = TimeNow();
    rotateMagnet(10);
}

void scrapeDumbbell(){
    rotateMagnet(50);
    Sleep(200);
    rotateMagnet(122);
    Sleep(200);
    move(5, 35);
    Sleep(200);
    rotateMagnet(30);

    ////////
    //Return to the box
    move(5, -35);
    ////////

    ///*/Chop
    Sleep(200);
    timedMove(500, -50);
    rotateMagnet(135);
    Sleep(500);
    rotateMagnet(10);
    Sleep(200);//*/
}
void doLever(bool direction){
    if(!direction){
        //towards bottom
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
        faceAngle2(180);
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

void doLever2(bool direction){
    if(!direction){
        //towards bottom
        LCD.WriteLine("Forward");
        cardArm.SetDegree(15.0);
        //This sleep needs to be 200
        Sleep(200);
        if(RPS.X()!=-1){
            if(RPS.Y()>=redLever[1]+.125){
                moveY(redLever[1],25);
            }
        }else{
            moveNoRPS(2, 35);
        }
        //Return to back
        moveNoRPS(5, -35);
        cardArm.SetDegree(100.0);
    }else{
        LCD.WriteLine("Backward");
        moveUntilBump(35);
        moveStraight(.12, -25);
        faceAngle2(180);
        cardArm.SetDegree(15.0);
        LCD.WriteLine("Position to Pull Backward");
        //This sleep needs to be 200 at least
        Sleep(500);

        moveNoRPS(1.5, -25);

        cardArm.SetDegree(100.0);
        moveNoRPS(1.5, 25);
        LCD.WriteLine("Pulled and lifted");
        //Sleep(1000);
        //Return to back
        moveNoRPS(5, -35);
    }
}

void doLevers(){
    //Get data
    float pos[3];
    //Align behind 1
    turn(25, 35);
    Sleep(200);
    //Changed from 750
    timedMove(850, 25);
    //moveNoRPSCalibrated(4, 25);
    //moveNoRPS(5.5, 35);
    Sleep(200);
    moveNoRPSCalibrated(.125, -25);
    getRPSData(pos);
    if(pos[2] > 0){
        faceAngle2(180);
    }else{
        turn(-2, 35);
    }
    //Now is aligned behind lever one
    bool data[3];
    getLeverData(data);
    Sleep(200);

    //Do one
    doLever2(data[0]);

    //Go to two
    Sleep(200);
    //////////////////////
    turn(-90, 25);
    //Changed from move No RPS 3.5
    moveStraight(4.0, 35);

    Sleep(200);
    turn(85, 25);
    //approach distance
    //moveNoRPS(2, 35);

    faceAngle(180);

    //Do two
    doLever2(data[1]);

    //Go to three
    //Sleep(200);
    turn(-90, 25);
    //Sleep(200);

    //changed from 3.75
    moveNoRPS(3.25, 35);
    //Sleep(200);
    turn(60, 25);
    //This sleep makes it not over turn
    Sleep(100);
    faceAngle2(180);
    //Sleep(200);
    //approach
    //moveNoRPS(2.5, 35);
    //moveStraight(1, 25);

    //do three
    doLever2(data[2]);
    moveNoRPSCalibrated(2, 25);
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

char colorString;

void pushButtons(){
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
        }else if(color == RED_LIGHT_COLOR){
            LCD.WriteLine("RED");
            move(4,-25);
            cardArm.SetDegree(CARD_ARM_DEGREE);
            faceAngle2(0);
            //Sleep(500);
            timedMove(300, 25);
            timedMove(600, 20);
            Sleep(5500);
            colorString = 'r';
        }else {
            LCD.WriteLine("We failed: DEFAULT BLUE");
            colorString = 'b';
            timedMove(500, 25);
            timedMove(5500, 10);
            moveNoRPS(5,-25);
        }
    cardArm.SetDegree(120);

    //reverse to get on line

}

//////////////////////////////////Calibrate with RPS (needs work)
void scanForLight(){

//    int left = 0;
//    float color = 0;
//    float timeStart = TimeNow();

//    leftMotor.SetPercent(25*leftOffsetForward);
//    rightMotor.SetPercent(25*rightOffsetForward);
    float a = fuelLight[0]-RPS.X();
    float b = fuelLight[1]-RPS.Y();
    float inches = sqrt(a*a+b*b);
//    float angle = acos(a/inches);
//    float angleDegrees = angle/PI*180;
//    //normalize angle for our robot
//    angleDegrees+=270;
//    //fix angle if it's not between 0 and 360
//    if(angleDegrees>360){
//        angleDegrees-=360;
//    }else if(angleDegrees <0){
//        angleDegrees+=360;
//    }
    //faceAngle(angleDegrees);

    int counts = inches * COUNTS_PER_INCH+10;
    rightMotor.SetPercent(20*rightOffsetForward);
    leftMotor.SetPercent(20);
    while((leftEnc.Counts() + rightEnc.Counts()) / 2. < counts){
        LCD.Write("CdS:");
        LCD.WriteLine(CdSButtonSensor.Value());

        leftMotor.SetPercent(20);
        float difference = leftEnc.Counts()-rightEnc.Counts();
        rightMotor.SetPercent(20+difference*k);

        if((CdSButtonSensor.Value()<MAX_RED_COLOR+.2)||(CdSRight.Value()<MAX_RED_COLOR+.4)){
            rightMotor.Stop();
            leftMotor.Stop();

            LCD.WriteLine("RED");
            move(4,-25);
            cardArm.SetDegree(CARD_ARM_DEGREE);
            faceAngle2(0);
            //Sleep(500);
            timedMove(300, 25);
            timedMove(500, 20);
            timedMove(5500, 5);
            colorString = 'r';
            moveStraight(1,-25);
            cardArm.SetDegree(120);

            return;
        }else if(CdSLeft.Value()<MAX_RED_COLOR+.2){
            rightMotor.Stop();
            leftMotor.Stop();

            LCD.WriteLine("RED");
            move(4,-25);
            cardArm.SetDegree(CARD_ARM_DEGREE);
            faceAngle2(2);
            //Sleep(500);
            timedMove(300, 25);
            timedMove(600, 20);
            Sleep(5500);
            colorString = 'r';
            moveStraight(1,-25);

            cardArm.SetDegree(120);
            return;
        }
    }
    if(colorString!='r'){
        pushButtons();
    }
}



#endif
