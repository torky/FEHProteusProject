#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <math.h>
#include <FEHRPS.h>

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
static const float RED_COLOR = 0.5;
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
    //RPS.InitializeTouchMenu();
    LCD.Clear();

    //LCD.WriteLine("facing north");
    //while(!buttons.RightPressed());{
      //faceNorth();
//}
    //Sleep(2000);
    //LCD.WriteLine("TEST 1: Start");
    //LCD.WriteLine("TEST 1: Read for r");
    //while(readLight(CdS) != 'r'){
    //    LCD.WriteLine(CdS.Value());
    //}
    //Sleep(2000);

    while(!buttons.RightPressed()){
        LCD.WriteLine(CdS.Value());
    }
    //moveNoRPS(40, 25);
    //turn(85, 25);
    //Sleep(5000);
    //move(25, 25);
    //turn(45, 25);

    while(!buttons.RightPressed());


    /////TEST 1/////
    //approachRamp()
    LCD.WriteLine("TEST 1: Start wait");
    startWait();
    LCD.WriteLine("TEST 1: Move 16");
    moveNoRPS(16, 25);
    Sleep(2000);

    LCD.WriteLine("TEST 1: Turn 44");
    turn(44, 25);
    Sleep(1000);
    LCD.WriteLine("TEST 1: Move 10");
    moveNoRPS(10, 25);
    LCD.WriteLine("TEST 1: Turn 90");
    turn(-90, 25);
    Sleep(1000);
    //reverse and grab dumbbell
    LCD.WriteLine("TEST 1: Move 6");
    moveNoRPS(6, 25);
    Sleep(2000);
    LCD.Clear();

    //Go up ramp
    LCD.WriteLine("TEST 1: Move 11");
    moveNoRPS(11, 25);
    LCD.WriteLine("TEST 1: Go over hump");
    moveNoRPS(9, 50);
    LCD.WriteLine("TEST 1: Move 25");
    moveNoRPS(35, 25);
    LCD.Clear();
    LCD.WriteLine("r is red, b is blue");
    LCD.WriteLine("k is black, y is yellow");
    LCD.WriteLine(readLight(CdS));
    LCD.WriteLine("TEST 1: Done");

    while(!buttons.RightPressed());

    LCD.WriteLine("TEST 1.5: Fucking book it");
    moveNoRPS(20, 40);

    while(!buttons.RightPressed());

    /////TEST 2/////
    LCD.Clear();
    Sleep(2000);
    LCD.WriteLine("TEST 2: Start");
    LCD.WriteLine("TEST 2: Read for r");
    while(readLight(CdS) != 'r'){
        LCD.WriteLine(CdS.Value());
    }
    Sleep(2000);

    LCD.WriteLine("TEST 2: Start");
    LCD.WriteLine("TEST 2: Move 23");
    moveNoRPS(23, 25);
    Sleep(2000);

    LCD.WriteLine("TEST 2: Turn 87");
    turn(-90, 25);
    //LCD.WriteLine("TEST 2: Face north");
    //faceNorth();
    LCD.WriteLine("TEST 2: Move 25");
    moveNoRPS(25, 25);
    //LCD.WriteLine("TEST 2: Face North");
    //faceNorth();
    Sleep(2000);

    LCD.WriteLine("TEST 2: Go up ramp");
    moveNoRPS(10, 25);
    LCD.WriteLine("TEST 2: Go over hump");
    moveNoRPS(5, 40);
    LCD.WriteLine("TEST 2: Move 21.5");
    moveNoRPS(21.5, 25);
    LCD.WriteLine("TEST 2: Done");

    return 0;
}

