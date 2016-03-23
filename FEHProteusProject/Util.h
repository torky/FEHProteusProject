#ifndef UTIL_H
#define UTIL_H

 // UTIL_H

bool checkColor(float colorValue){

    float upperColorValue = colorValue+.05;
    float lowerColorValue = colorValue-.05;

    if(CdSButtonSensor.Value()<upperColorValue&&CdSButtonSensor.Value()>lowerColorValue){
        return true;
    }else{
        return false;
    }
}

float determineColor(){
    if(checkColor(BLUE_LIGHT_COLOR)){
        LCD.WriteLine("It's blue.");
        return BLUE_LIGHT_COLOR;
    }else if(checkColor(RED_LIGHT_COLOR)){
        LCD.WriteLine("It's red.");
        return RED_LIGHT_COLOR;
    }else {
        LCD.WriteLine("It's not blue or red.");
        return 0;
    }
}

void calibrateServos(){
    cardArm.SetMin(CARD_MIN);
    cardArm.SetMax(CARD_MAX);

    magnetArm.SetMin(MAGNET_MIN);
    magnetArm.SetMax(MAGNET_MAX);
}

//In order x, y, heading
//Heading is in degrees, 0 is "North", 90 is "East"
//Returns -2 in the dead zone
void getRPSData(float data[]){
    data[0] = RPS.X();
    data[1] = RPS.Y();
    data[2] = RPS.Heading();

    //Test the RPS 5 times if there is an error
    if(data[0] == -1){
        for(int c = 0; c < 5 || data[0] == -1; c++){
            data[0] = RPS.X();
        }
    }
    if(data[1] == -1){
        for(int c = 0; c < 5 || data[1] == -1; c++){
            data[1] = RPS.Y();
        }
    }
    if(data[2] == -1){
        for(int c = 0; c < 5 || data[2] == -1; c++){
            data[2] = RPS.Heading();
        }
    }
}

//False is forward, true is backwards
//In order red, white, blue
void getLeverData(bool data[]){
    data[0] = RPS.RedSwitchDirection()-1;
    data[1] = RPS.WhiteSwitchDirection()-1;
    data[2] = RPS.BlueSwitchDirection()-1;
}

//subtracts from total value
static const int rightOffsetForward = 0;
static const int leftOffsetForward = 0;
static const int rightOffsetBack = 2;
static const int leftOffsetBack = 0;

void move(float inches, int percent){
    //Get robot location and bearing
    float start[3];
    getRPSData(start);
    LCD.WriteLine("Got move rps data");
    //Reset encoder counts
    rightEnc.ResetCounts();
    leftEnc.ResetCounts();


    //Set left and right motor percentages


    if(percent < 0){
        rightMotor.SetPercent(percent+rightOffsetBack);
        leftMotor.SetPercent(percent+leftOffsetBack);
    }else{
        //Set left and right motor percentages
        rightMotor.SetPercent(percent-rightOffsetForward);
        leftMotor.SetPercent(percent-leftOffsetForward);
    }

    LCD.WriteLine("set percentages");
    //Convert the inches to a value for shaft encoding
    int counts = inches * COUNTS_PER_INCH;
    //Drive the specified number of cycles and or distance
    float delta = 0;
    float loc[3];
    while((leftEnc.Counts() + rightEnc.Counts()) / 2. < counts && (delta < inches)){
        getRPSData(loc);
        double x = pow(loc[0] - start[0], 2);
        double y = pow(loc[1] - start[1], 2);
        delta = sqrt(x + y);
    }

    //Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();

    //Check RPS to see if the distance was correct
    float end[3];
    getRPSData(end);
    //If the distance and bearing are not within error margins, adjust accordingly

}

void moveNoRPS(float inches, int percent){
    //Reset encoder counts
    rightEnc.ResetCounts();
    leftEnc.ResetCounts();


    if(percent < 0){
        rightMotor.SetPercent(percent+rightOffsetBack);
        leftMotor.SetPercent(percent+leftOffsetBack);
    }else{
        //Set left and right motor percentages
        rightMotor.SetPercent(percent-rightOffsetForward);
        leftMotor.SetPercent(percent-leftOffsetForward);
    }

    //LCD.WriteLine("set percentages");
    //Convert the inches to a value for shaft encoding
    int counts = inches * COUNTS_PER_INCH;
    //LCD.WriteLine(counts);
    //Drive the specified number of cycles and or distance
    while((leftEnc.Counts() + rightEnc.Counts()) / 2. < counts);

    //LCD.WriteLine(leftEnc.Counts());
    //LCD.WriteLine(rightEnc.Counts());
    //Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}
void timedMove(int millis, int percent){
    //Set left and right motor percentages
    if(percent < 0){
        rightMotor.SetPercent(percent+rightOffsetBack);
        leftMotor.SetPercent(percent+leftOffsetBack);
    }else{
        //Set left and right motor percentages
        rightMotor.SetPercent(percent-rightOffsetForward);
        leftMotor.SetPercent(percent-leftOffsetForward);
    }

    Sleep(millis);
    rightMotor.Stop();
    leftMotor.Stop();
}

//Fix turning delta
//Turning right is positive, left is negative
void turn(int angle, int percent){
    //Reset encoder counts
    //LCD.WriteLine("reseting counts");
    rightEnc.ResetCounts();
    leftEnc.ResetCounts();

    //LCD.WriteLine("converting");
    //Convert angle to counts
    int counts = angle * COUNTS_PER_DEGREE;
    if(counts < 0){
        counts = -counts;
    }

    //LCD.WriteLine("deciding");
    if(angle < 0){
        //Set both motors to desired percent
        rightMotor.SetPercent(percent);
        leftMotor.SetPercent(-percent);
    }else{
        //Set both motors to desired percent
        rightMotor.SetPercent(-percent);
        leftMotor.SetPercent(percent);
    }

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((leftEnc.Counts() + rightEnc.Counts()) / 2. < counts);

    //Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}

void turn2(int angle, int percent){
    //Reset encoder counts
    //LCD.WriteLine("reseting counts");
    rightEnc.ResetCounts();
    leftEnc.ResetCounts();

    //LCD.WriteLine("converting");
    //Convert angle to counts
    int counts = angle * COUNTS_PER_DEGREE;
    if(counts < 0){
        counts = -counts;
    }

    //LCD.WriteLine("deciding");
    if(angle < 0){
        //Set both motors to desired percent
        rightMotor.SetPercent(percent);
        leftMotor.SetPercent(0);
    }else{
        //Set both motors to desired percent
        rightMotor.SetPercent(0);
        leftMotor.SetPercent(percent);
    }

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((leftEnc.Counts() + rightEnc.Counts())  < counts);

    //Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}

void pushArm(float inches){
    cardArm.SetDegree(inches * ARM_DEGREE_PER_INCH);
}

void rotateMagnet(int angle){
    magnetArm.SetDegree(angle);
}

//Get this working
void faceNorth(){
    float data[3];
    LCD.WriteLine("FACE NORTH");
    for(int c = 0; c < 3; c++){
        LCD.Write("Angle is ");
        getRPSData(data);
        LCD.WriteLine(data[2]);
        //Convert from the RPS cycle to the turning cycle
        if(data[2] > 180){
            if(data[2]-360 < -2){
                turn((data[2]-360), 25);
                LCD.WriteLine((data[2]-360));
            }
        }else{
            if(data[2] > 2){
                turn(data[2], 25);
                LCD.WriteLine(data[2]);
            }
        }
        LCD.WriteLine("Wait for 200ms");
        Sleep(200);
    }
}

//Needs to be tested thoroughly
void faceAngle(int angle){
    float data[3];
    for(int c = 0; c < 3; c++){
        LCD.Write("Angle is:");
        getRPSData(data);
        LCD.WriteLine(data[2]);
        //Convert from the RPS cycle to the turning cycle
        //If it is in the right side
        if(data[2] > 180){
            //if the angle to turn to is also in the right
            if(angle > (data[2] - 180)){
                //turn right by a bit
                turn(data[2] - angle, 20);
            }else if(angle > data[2]){
                turn(data[2] - angle, 20);
            }else{
                turn(data[2] - 360 - angle, 20);
            }
        }else{
            if(angle < data[2]){
                //turn right a bit
                turn(angle, 20);
            }else if(angle > (data[2] + 180)){
                //turn right a lot
                turn(data[2] + angle - 180, 20);
            }else{
                //turn left a bit
                turn(data[2]-angle, 20);
            }
        }
        Sleep(500);
    }
}

/*

float passNoZero = RPS.Heading()-angle;
float passThroughZero = RPS.Heading()-angle + 360;
if(RPS.Heading()<=180){
    passNoZero = RPS.Heading()-angle;
    passThroughZero = RPS.Heading()-angle + 360;

}else{
    passNoZero = RPS.Heading()-angle;
    passThroughZero = 360-angle +RPS.Heading();

}


if(passNoZero<0){
    passNoZero = passNoZero*-1;
}

if(passThroughZero<0){
    passThroughZero = passThroughZero*-1;
}

float initialTurnDegrees = 0;
if(passNoZero<=passThroughZero){
    initialTurnDegrees = RPS.Heading()-angle;

}else{
    if(RPS.Heading()<=180){
        initialTurnDegrees = RPS.Heading()-angle + 360;

    }else{
        initialTurnDegrees = -1*(360-angle +RPS.Heading());

    }

}

float absoluteValueOfTurn = initialTurnDegrees;
if(initialTurnDegrees<0){
    absoluteValueOfTurn *= -1;
}
if(absoluteValueOfTurn>=2){
    turn(initialTurnDegrees, 20);
}
*/

//Take two
void faceAngle2(float angle){
    //inch adjust
    Sleep(200);
    LCD.Write("Heading b4 turn: ");
    LCD.WriteLine(RPS.Heading());

    LCD.Write("Goal: ");
    LCD.WriteLine(angle);

    float turnDegrees = RPS.Heading()-angle;

    while(turnDegrees<0){
        turnDegrees=turnDegrees+360;
    }

    if(turnDegrees>180){
        //turn positive
        //changed from negative one
        turn(turnDegrees-360, 20);
    }else{
        //turn negative
        turn(turnDegrees, 20);

    }

    bool notAtAngle = true;
    while(notAtAngle){
        Sleep(300);
        turnDegrees = RPS.Heading()-angle;


        while(turnDegrees<0){
            turnDegrees=turnDegrees+360;
        }

       /* if(turnDegrees<-180){
            turnDegrees = -1*(turnDegrees+360);
        }else if(turnDegrees>180){
            turnDegrees = turnDegrees-360;
        }*/

        if((turnDegrees>359)||(turnDegrees<1)){
            notAtAngle = false;
        }else{
            if(turnDegrees>180){
                //turn positive
                //changed from negative one
                turn(-1, 20);
            }else{
                //turn negative
                turn(1, 20);

            }
            LCD.Write("Heading: ");
            LCD.WriteLine(RPS.Heading());
            LCD.Write("turnDegrees: ");
            LCD.WriteLine(turnDegrees);


        }
    }
    Sleep(200);
    LCD.Write("Heading after turn: ");
    LCD.WriteLine(RPS.Heading());
}

//turn right 2 inches of change
//turn left 8 inches of change

//New idea bitches
//x = the rps x value
//backwards = negative power value
void moveX(float x, int power){
    //turn right 2 inches of change
    //turn left 8 inches of change
    if(x-RPS.X()>0){
        LCD.WriteLine(RPS.X());
        faceAngle2(270);
    }else{
        LCD.WriteLine(RPS.Y());

        faceAngle2(90);
    }
    float distance = x-RPS.X();
    if(distance<0){
        distance = distance*-1;
    }
    move(distance , power);

}

//y = the rps y value
//backwards = negative power value
void moveY(float y, int power){
    //turn right 2 inches of change
    //turn left 8 inches of change
    if((y-RPS.Y())*power>0){
        faceAngle2(0);
    }else{
        faceAngle2(180);
    }
    float distance = y-RPS.Y();
    if(distance<0){
        distance = distance*-1;
    }
    move(distance , power);


}

void moveRPS(float x, float y, int power){
    float currentX = RPS.X();
    float currentY = RPS.Y();

    float a = x-currentX;
    float b = y-currentY;

    float distance = sqrt((a)*(a)+(b)*(b));

    float headingRadians = acos(a/distance);
    float headingDegrees = headingRadians*360/2/PI;

    //consider the other 180 degrees;
    if(b<0){
        headingDegrees = -1*headingDegrees;
    }

    //adjusting for the 0 degree
    headingDegrees = 270+headingDegrees;
    if(headingDegrees>360){
        headingDegrees= headingDegrees - 360;
    }

    if(headingDegrees<0){
        headingDegrees = headingDegrees + 360;
    }


    LCD.Write("Heading degrees: ");
    LCD.WriteLine(headingDegrees);
    LCD.Write("Actual heading: ");
    LCD.WriteLine(RPS.Heading());

    LCD.Write(a);
    LCD.WriteLine(" inches X");
    LCD.Write(b);
    LCD.WriteLine(" inches Y");

    Sleep(1000);

    //if backwards
    if(power<0){
        headingDegrees = headingDegrees+180;
        if(headingDegrees>360){
            headingDegrees= headingDegrees - 360;
        }
        LCD.WriteLine("negative heading");
        LCD.Write("Heading degrees: ");
        LCD.WriteLine(headingDegrees);
        LCD.Write("Actual heading: ");
        LCD.WriteLine(RPS.Heading());
        Sleep(1000);
    }

    //check if heading is over 360 and adjust
    if(headingDegrees>360){
        headingDegrees= headingDegrees - 360;
    }

    if(headingDegrees>180){
        headingDegrees= headingDegrees - 360;
    }

    faceAngle2(headingDegrees);
    LCD.Write("Actual heading------: ");
    LCD.WriteLine(RPS.Heading());
    Sleep(1000);
    move(distance, power);


}


#endif
