#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <math.h>
#include <FEHRPS.h>
#include <FEHSD.h>

//Sensor declarations
AnalogInputPin leftOpt(FEHIO::P0_2);
AnalogInputPin midOpt(FEHIO::P0_1);
AnalogInputPin rightOpt(FEHIO::P0_0);

AnalogInputPin CdS(FEHIO::P0_3);

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder rightEnc(FEHIO::P2_1);
DigitalEncoder leftEnc(FEHIO::P2_0);

FEHMotor leftMotor(FEHMotor::Motor1, 12.0);
FEHMotor rightMotor(FEHMotor::Motor0, 12.0);

FEHServo cardArm(FEHServo::Servo0);
FEHServo magnetArm(FEHServo::Servo1);

//Need optosensor height and filter color
static const float YELLOW_COLOR = 2.50;
static const float RED_COLOR = 0.65;
static const float BLUE_COLOR = 0.96;
static const float BLACK_COLOR = 3.0;

static const float LINE_SURFACE = 3.0;
//Motor and wheel constants
static const float COUNTS_PER_REV = 318;
static const float WHEEL_DIAMETER = 3;
static const float PI = 3.14159265358979323846;
static const float COUNTS_PER_INCH = COUNTS_PER_REV/(PI*WHEEL_DIAMETER);
static const float COUNTS_PER_DEGREE = 215.0/90.0;

#include "Optosensor.h"
#include "Util.h"
#include "Tasks.h"

int main(void){

    //Must call this method first
    RPS.InitializeTouchMenu();
    LCD.Clear();

    //Writing to file
    //SD.OpenLog();
    //SD.Printf("STRING", data);
    //SD.CloseLog();

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

    /////PERFORMANCE TEST 1/////
    //approachRamp()
    LCD.WriteLine("TEST 1: Start wait");
    startWait();
    LCD.WriteLine("TEST 1: Move 16");
    moveNoRPS(16, 25);

    LCD.WriteLine("TEST 1: Turn 44");
    turn(44, 25);
    LCD.WriteLine("TEST 1: Move 10");
    moveNoRPS(10, 25);
    LCD.WriteLine("TEST 1: Turn 90");
    turn(-90, 25);
    //reverse and grab dumbbell
    LCD.WriteLine("TEST 1: Move 7");
    moveNoRPS(6, 25);
    Sleep(2000);
    faceNorth();
    //CHECK POSITIONING HERE
    LCD.Clear();

    //Go up ramp
    LCD.WriteLine("TEST 1: Move 9");
    moveNoRPS(10, 35);
    //Nubs over the lip
    Sleep(2000);
    LCD.WriteLine("TEST 1: Go over hump");
    //9 inches to power over
    moveNoRPS(9, 55);
    moveNoRPS(1, 25);
    faceNorth();
    Sleep(500);
    faceNorth();
    Sleep(500);
    faceNorth();
    Sleep(10000);
    //Get to the light - fix me
    LCD.WriteLine("TEST 1: Move 9");
    moveNoRPS(9, 25);
    //This places line under the poeky do
    //followLine(1);
    //read light
    LCD.Clear();
    LCD.WriteLine("r is red, b is blue");
    LCD.WriteLine("k is black, y is yellow");
    LCD.WriteLine(readLight(CdS));
    LCD.WriteLine("TEST 1: Done");

    //followLine(-1);

    //moveNoRPS(6, 25);
    //DO LEVERS

    return 0;
}

