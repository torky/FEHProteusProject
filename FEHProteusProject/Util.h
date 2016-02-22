#ifndef UTIL_H
#define UTIL_H

#endif // UTIL_H

//In order x, y, heading
//Heading is in degrees, 0 is "North", 90 is "East"
float* getRPSData(){
    float data[3];
    data[0] = RPS.X();
    data[1] = RPS.Y();
    data[3] = RPS.Heading();

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
    return data;
}

//False is forward, true is backwards
//In order red, white, blue
bool* getLeverData(){
    bool data[3];
    data[0] = RPS.RedSwitchDirection()-1;
    data[1] = RPS.WhiteSwitchDirection()-1;
    data[2] = RPS.BlueSwitchDirection()-1;
    return data;
}

void move(float inches, int percent){
    //Get robot location and bearing
    float start[] = getRPSData();
    //Reset encoder counts
    rightEnc.ResetCounts();
    leftEnc.ResetCounts();

    //Set left and right motor percentages
    rightMotor.SetPercent(percent);
    leftMotor.SetPercent(percent);

    //Convert the inches to a value for shaft encoding
    int counts = inches * COUNTS_PER_INCH;
    //Drive the specified number of cycles and or distance
    float delta = 0;
    while((leftEnc.Counts() + rightEnc.Counts()) / 2. < counts && (delta < inches)){
        float loc[] = getRPSData;
        double x = pow(loc[0] - start[0], 2);
        double y = pow(loc[1] - start[1], 2);
        delta = sqrt(x + y);
    }

    //Turn off motors
    rightMotor.Stop();
    leftMotor.Stop();
    //Check RPS to see if the distance was correct
    float end[] = getRPSData();
    //If the distance and bearing are not within error margins, adjust accordingly

}

void turn(int angle, int percent){

}
void turn_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void pushArm(float inches){

}

void rotateMagnet(int angle){

}
