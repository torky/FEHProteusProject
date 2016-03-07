#ifndef UTIL_H
#define UTIL_H

 // UTIL_H

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



void move(float inches, int percent){
    //Get robot location and bearing
    float start[3];
    getRPSData(start);
    LCD.WriteLine("Got move rps data");
    //Reset encoder counts
    rightEnc.ResetCounts();
    leftEnc.ResetCounts();


    //Set left and right motor percentages
    rightMotor.SetPercent(percent);
    leftMotor.SetPercent(percent);

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
        rightMotor.SetPercent(percent);
        leftMotor.SetPercent(percent+2);
    }else{
        //Set left and right motor percentages
        rightMotor.SetPercent(percent);
        leftMotor.SetPercent(percent-2);
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
        rightMotor.SetPercent(percent);
        leftMotor.SetPercent(percent+2);
    }else{
        rightMotor.SetPercent(percent);
        leftMotor.SetPercent(percent-2);
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


void pushArm(float inches){
    cardArm.SetDegree(inches * ARM_DEGREE_PER_INCH);
}

void rotateMagnet(int angle){
    magnetArm.SetDegree(angle);
}

//Get this working
void faceNorth(){
    float data[3];
    for(int c = 0; c < 3; c++){
        LCD.Write("Angle is ");
        getRPSData(data);
        LCD.WriteLine(data[2]);
        //Convert from the RPS cycle to the turning cycle
        if(data[2] > 180){
            LCD.WriteLine((data[2]-360));
            turn((data[2]-360), 20);
        }else{
            turn(data[2], 20);
            LCD.WriteLine(data[2]);
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

void moveRPS(float x, float y, int power){
    float currentX = RPS.X();
    float currentY = RPS.Y();

    float a = x-currentX;
    float b = y-currentY;

    float distance = sqrt((a)*(a)+(b)*(b));

    float headingRadians = acos(a/distance);
    float headingDegrees = headingRadians*360/2/PI;


    if(b<0){
        headingDegrees = -headingDegrees;
    }

    if(power<0){
        faceAngle(-headingDegrees);
        move(distance, -power);
    }else{
        faceAngle(headingDegrees);
        move(distance, power);

    }
}


#endif
