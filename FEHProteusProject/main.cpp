#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <math.h>
#include <FEHRPS.h>
#include <FEHSD.h>

//Sensor declarations
AnalogInputPin leftOpt(FEHIO::P0_0);
AnalogInputPin midOpt(FEHIO::P0_2);
AnalogInputPin rightOpt(FEHIO::P0_4);

AnalogInputPin CdS(FEHIO::P1_7);
AnalogInputPin CdSButtonSensor(FEHIO::P3_2);

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank2);
DigitalEncoder rightEnc(FEHIO::P3_0);
DigitalEncoder leftEnc(FEHIO::P1_0);

FEHMotor leftMotor(FEHMotor::Motor3, 12.0);
FEHMotor rightMotor(FEHMotor::Motor0, 12.0);

FEHServo cardArm(FEHServo::Servo7);
FEHServo magnetArm(FEHServo::Servo0);

//Need optosensor height and filter color
static const float YELLOW_COLOR = 2.50;
static const float RED_COLOR = 0.65;
static const float BLUE_COLOR = 0.96;
static const float BLACK_COLOR = 3.0;

//Need CdS value for reading the right color
static const float RED_LIGHT_COLOR = .40;
float BLUE_LIGHT_COLOR = 1.0;
static const float YELLOW_LINE_COLOR = .9;//lowest possible
static const float BLACK_BACKGROUND_COLOR = 2.27;

//If below, then red
static const float MAX_RED_COLOR = .5;
//If below then blue
static const float MAX_BLUE_COLOR = 1.0;

static const float LINE_SURFACE = 2.00;
//Motor and wheel constants
static const float COUNTS_PER_REV = 318;
static const float WHEEL_DIAMETER = 3;
static const float PI = 3.14159265358979323846;
static const float COUNTS_PER_INCH = COUNTS_PER_REV/(PI*WHEEL_DIAMETER);
static const float CALIBRATE = 27.125/915;
static const float COUNTS_PER_DEGREE = 190.0/90.0;
static const float ARM_DEGREE_PER_INCH = 0;

//Servo Constants
static const float CARD_MIN = 510;
static const float CARD_MAX = 2389;
static const float MAGNET_MIN = 508;
static const float MAGNET_MAX = 2430;
static const float GRAB_DUMBBELL = 110;

//Motor Constants
static const float rightOffsetForward = 1-20.0/915;
static const float leftOffsetForward = 1;
static const float rightOffsetBack = 1-(929-896)/896;
static const float leftOffsetBack = 0;

static const float k = .6;
static const int XValue = 0;
static const int YValue = 1;
//Brain
float startPoint[2] = {8.3, 13.2};
float finishPoint[2] = {86.4, 7.4};
float dumbbellStart[2] = {27.7, 16};
float belowRamp[2] = {27.7, 26};
float aboveRamp[2] = {31, 42.5};
float fuelLight[2] = {26.5, 65.5};
float dumbbellEnd[2] = {5.3, 47.3};
float redLever[2] = {4, 40.4};
float whiteLever[2] = {9, 40.4};
float blueLever[2] = {14, 40.4};

#include "Optosensor.h"
#include "Util.h"
#include "Tasks.h"
#include "Brain.h"

int main(void){
    //Necessary initialization code
    //moveNoRPS(72, 30);
    //moveNoRPS(72, -30);

//    moveForwardStraight(10, 20);
//    LCD.Write("Right Encoder: ");
//    LCD.WriteLine(rightEnc.Counts());
//    LCD.Write("Left Encoder: ");
//    LCD.WriteLine(leftEnc.Counts());

//    Sleep(100000);
    RPS.InitializeTouchMenu();

    calibrateServos();

    calibrateMapPerformanceTest4();

    LCD.Clear();

    /////PERFORMANCE TEST 4 first half/////

    LCD.WriteLine("Start wait");
    startWait();
    //first diagonal line up
    LCD.WriteLine("Move to first point");
    move(15, 35);

    LCD.WriteLine("Move to right x with 6.5 inch adjust");
    moveX(dumbbellStart[XValue]+6.5, 25);

    LCD.WriteLine("Move to back perfectly???");
    moveY(dumbbellStart[YValue], -25);
    inchY(dumbbellStart[YValue]);

    LCD.WriteLine("grab that bell");
    faceAngle2(0);

//    if(RPS.X()+.25<dumbbellStart[XValue]){
//        turn(-3, 25);
//    }else if(RPS.X()-.25>dumbbellStart[XValue]){
//        turn(3, 25);
//    }
    grabDumbbell();

    faceAngle(0);
    LCD.WriteLine("Go to that ramp");

//    if(RPS.X()+.25<dumbbellStart[XValue]){
//        turn(2, 25);
//        moveNoRPSCalibrated(12, 30);
//    }else if(RPS.X()-.25>dumbbellStart[XValue]){
//        turn(-2, 25);
//        moveNoRPSCalibrated(12, 30);
//    }else {
        moveY(30, 25);

//    }

    LCD.WriteLine("Charge");
    move(20, 30);

    //D move to 55.3, H move to 56.3
    LCD.WriteLine("Face north and align Y 57.3");
    faceAngle2(0);
    moveY(fuelLight[YValue]-10, 25);
    faceAngle(0);

    //moveRPS(fuelLight[XValue],fuelLight[YValue],25);

    LCD.WriteLine("Search for light");

    //OFF TO THE RIGHT WTF WHY CAN'T THE ROBOT JUST WORK!!!!!!!!
    scanForLight();
    LCD.WriteLine(colorString);

    ////////////////////////////////second half of perf 3
    ///
    //D move to 55.3, H move to 56.3
    LCD.WriteLine("Face north and align Y 57.3");
    faceAngle2(0);
    moveY(55.3, -25);

    LCD.WriteLine("Align x with 2 inch adjust");
    faceAngle2(90);
    /////////////////////FIX
    Sleep(200);

    LCD.WriteLine("Go across the field");
    moveStraight(RPS.X()-dumbbellEnd[XValue]+5.5, 25);

    LCD.WriteLine("Face south and move back");
    //Sleep(200);
    turn(-85,25);
    moveNoRPS(3, 25);
    faceAngle2(180);
    moveNoRPS(4, -25);
    if(RPS.X()+.25<dumbbellEnd[XValue]){
        turn(-3, 25);
    }else if(RPS.X()-.25>dumbbellEnd[XValue]){
        turn(3, 25);
    }
    moveNoRPS(2.5, -25);

    LCD.WriteLine("Scrape dumbbell");
    //Sleep(200);
    scrapeDumbbell();

    ///Levers
    //Expects robot to be at container
    doLevers();
    moveNoRPSCalibrated(3,25);

    ////////////////////////////////go to the front of the ramp

    LCD.WriteLine("Go to front of ramp");
    moveX(fuelLight[XValue]+6, 30);

    ////////////////////////////////last half of 4

    LCD.WriteLine("Go down the ramp");
    moveY(25.7, -35);
    faceAngle2(0);

    Sleep(200);
    if(RPS.Y()<23){
        moveY(26, 25);
    }
    faceAngle2(0);

    /*LCD.WriteLine("Lower the magnetic arm");
    magnetArm.SetDegree(50);
    Sleep(1000);
    LCD.WriteLine("Lower the magnetic arm");
    magnetArm.SetDegree(90);
    */

    LCD.WriteLine("Head straight for the launch button");

    faceAngle2(300);

    //moveRPS(0, 17, -50);
    //timedMove(5000, 30);

    leftMotor.SetPercent(-55);
    rightMotor.SetPercent(-50);
    float timeStart = TimeNow();
    while(TimeNow()-timeStart<3);
    move(3,25);
    LCD.WriteLine("Lower the magnetic arm");
    magnetArm.SetDegree(90);
    Sleep(100);
    timedMove(10000, -50);

    return 0;
}

