#ifndef UTIL_H
#define UTIL_H

#endif // UTIL_H

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
    leftMotor.SetPercent(-1*percent);

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


    //Set left and right motor percentages
    rightMotor.SetPercent(percent);
    leftMotor.SetPercent(-1*percent);

    LCD.WriteLine("set percentages");
    //Convert the inches to a value for shaft encoding
    int counts = inches * COUNTS_PER_INCH;
    //Drive the specified number of cycles and or distance
    while((leftEnc.Counts() + rightEnc.Counts()) / 2. < counts){
    }

    //Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}

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
        leftMotor.SetPercent(-1*-percent);
    }else{
        //Set both motors to desired percent
        rightMotor.SetPercent(-percent);
        leftMotor.SetPercent(-1*percent);
    }

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((leftEnc.Counts() + rightEnc.Counts()) / 2. < counts);

    //Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
}


void pushArm(float inches){

}

void rotateMagnet(int angle){

}
