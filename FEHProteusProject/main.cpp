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

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank2);
DigitalEncoder rightEnc(FEHIO::P3_0);
DigitalEncoder leftEnc(FEHIO::P1_0);

FEHMotor leftMotor(FEHMotor::Motor3, 12.0);
FEHMotor rightMotor(FEHMotor::Motor0, 12.0);

FEHServo cardArm(FEHServo::Servo7);
FEHServo magnetArm(FEHServo::Servo1);

//Need optosensor height and filter color
static const float YELLOW_COLOR = 2.50;
static const float RED_COLOR = 0.65;
static const float BLUE_COLOR = 0.96;
static const float BLACK_COLOR = 3.0;

static const float LINE_SURFACE = 2.00;
//Motor and wheel constants
static const float COUNTS_PER_REV = 318;
static const float WHEEL_DIAMETER = 3;
static const float PI = 3.14159265358979323846;
static const float COUNTS_PER_INCH = COUNTS_PER_REV/(PI*WHEEL_DIAMETER);
static const float COUNTS_PER_DEGREE = 215.0/90.0;
static const float ARM_DEGREE_PER_INCH = 0;

//Servo Constants
static const float CARD_MIN = 510;
static const float CARD_MAX = 2389;
static const float MAGNET_MIN = 508;
static const float MAGNET_MAX = 2430;

#include "Optosensor.h"
#include "Util.h"
#include "Tasks.h"

int main(void){
    //Necessary initialization code
    RPS.InitializeTouchMenu();
    calibrateServos();
    LCD.Clear();

    //Writing to file
    //SD.OpenLog();
    //SD.Printf("STRING", data);
    //SD.CloseLog();

    //Line following test
    /*calibrateOpto(buttons);
    followLine(1);
    while(!buttons.RightPressed());
    followLine(1);
    while(!buttons.LeftPressed());
    followLine(1);
    while(!buttons.RightPressed());
    followLine(-1);
    while(!buttons.LeftPressed());
    followLine(-1);
    while(!buttons.RightPressed());
    followLine(-1);
    while(!buttons.LeftPressed());*/

    //Get faceAngle working
    //int angle = 0;
    //while(!buttons.LeftPressed()){
    //    LCD.Write("Facing to ");
    //    LCD.Write(angle);
    //    faceAngle(angle);
    //    faceAngle(angle);
    //    faceAngle(angle);
    //    while(!buttons.RightPressed());
    //    angle = angle + 10;
    //}
    while(!buttons.RightPressed()){
        LCD.WriteLine(CdS.Value());
    }

    /////PERFORMANCE TEST 2/////

    LCD.WriteLine("Start wait");
    startWait();
    startToRampAlign();
    //approcahDumbbell();
    //grabDumbbell();
    //approachRamp();

    LCD.WriteLine("Move 6");
    moveNoRPS(6, 25);
    ascendRamp();
    faceNorth();

    //push a button
    moveNoRPS(8, 25);
    faceNorth();
    moveNoRPS(8.5, 25);
    moveNoRPS(2, 25);
    moveNoRPS(.5, 35);
    faceNorth();

    Sleep(2000);

    //go to switches
    moveNoRPS(12, -25);
    faceNorth();
    faceAngle(90);
    moveNoRPS(17, 25);
    Sleep(3000);
    //face lever 1
    turn(-87, 20);
    Sleep(3000);
    //Position in front of
    moveNoRPS(4, 25);
    Sleep(1000);
    cardArm.SetDegree(15.0);
    Sleep(1000);
    //pulling the lever
    moveNoRPS(1.5, -20);
    //lift arm
    cardArm.SetDegree(60.0);

    //reverse
    moveNoRPS(6, -25);
    turn(-90, 20);
    moveNoRPS(4.75, 25);
    //fdace lever 2
    turn(90, 20);
    cardArm.SetDegree(15.0);
    Sleep(1000);
    moveNoRPS(5.5, 25);


    //do switches

    Sleep(10000);
    /////PROPER TASK ORDERING/////
    //Get to the light
    LCD.WriteLine("TEST 1: Move 9");
    moveNoRPS(9, 25);
    //This places line under the poeky do
    followLine(1);
    LCD.Clear();

    //Light reading
    //LCD.WriteLine("r is red, b is blue");
    //LCD.WriteLine("k is black, y is yellow");
    //LCD.WriteLine(readLight(CdS));
    LCD.WriteLine("TEST 1: Done");
    moveNoRPS(3, 25);
    moveNoRPS(-3, 25);
    //followLine(-1);
    //turn 90 to face switches
    //drop dumbbell
    //drive forward to switch
    //Extend arm an push
    //reverse to pull it back
    //turn 90 right
    //drive forward a bit
    //turn 90 left
    //drive forward

    //moveNoRPS(6, 25);
    //DO LEVERS

    return 0;
}

