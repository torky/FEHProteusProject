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

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder rightEnc(FEHIO::P2_0);
DigitalEncoder leftEnc(FEHIO::P2_1);

FEHMotor leftMotor(FEHMotor::Motor0, 12.0);
FEHMotor rightMotor(FEHMotor::Motor1, 12.0);

FEHServo cardArm(FEHServo::Servo0);
FEHServo magnetArm(FEHServo::Servo1);

//Need optosensor height and filter color
static const float LINE_COLOR = 1.75;
static const float RED_COLOR = 1.75;
static const float BLUE_COLOR = 1.75;
//Motor and wheel constants
static const float COUNTS_PER_REV = 100;
static const float WHEEL_DIAMETER = 3;
static const float PI = 3.14159265358979323846;
static const float COUNTS_PER_INCH = COUNTS_PER_REV/(PI*WHEEL_DIAMETER);

#include "Optosensor.h"
#include "Util.h"
#include "Tasks.h"

int main(void){
    /*
    //Shaft Encoding program

    int motor_percent = 25; //Input power level here
    int expected_counts = 243; //Input theoretical counts here

    int fourteen_inches = 615;
    int left_counts = 215;
    int ten = 439;
    int right_counts = 215;
    int four = 176;


    //Initialize the screen
    LCD.Clear( FEHLCD::Scarlet );
    LCD.SetFontColor( FEHLCD::Gray );

    //turn right
    LCD.WriteLine("Shaft Encoder Lab Test");
    LCD.WriteLine("Press middle button to turn right");
    while(!buttons.MiddlePressed()); //Wait for middle button to be pressed
    while(buttons.MiddlePressed()); //Wait for middle button to be unpressed

    move_forward(25, fourteen_inches);
    turn_left(25, left_counts);
    move_forward(25, ten);
    turn_right(25, right_counts);
    move_forward(25, four);



    while(!buttons.MiddlePressed()); //Wait for middle button to be pressed
    while(buttons.MiddlePressed()); //Wait for middle button to be unpressed

    Sleep(2.0); //Wait for counts to stabilize
    //Print out data
    LCD.Write("Theoretical Counts: ");
    LCD.WriteLine(expected_counts);
    LCD.Write("Motor Percent: ");
    LCD.WriteLine(motor_percent);
    LCD.Write("Actual LE Counts: ");
    LCD.WriteLine(left_encoder.Counts());
    LCD.Write("Actual RE Counts: ");
    LCD.WriteLine(right_encoder.Counts());

    //25%
    LCD.WriteLine("Shaft Encoder Lab Test");
    LCD.WriteLine("Press middle button");
    while(!buttons.MiddlePressed()); //Wait for middle button to be pressed
    while(buttons.MiddlePressed()); //Wait for middle button to be unpressed

    move_forward(motor_percent, expected_counts); //see function

    Sleep(2.0); //Wait for counts to stabilize
    //Print out data
    LCD.Write("Theoretical Counts: ");
    LCD.WriteLine(expected_counts);
    LCD.Write("Motor Percent: ");
    LCD.WriteLine(motor_percent);
    LCD.Write("Actual LE Counts: ");
    LCD.WriteLine(left_encoder.Counts());
    LCD.Write("Actual RE Counts: ");
    LCD.WriteLine(right_encoder.Counts());

    //40 percent
    motor_percent = 40;
    LCD.WriteLine("Shaft Encoder Lab Test");
    LCD.WriteLine("Press middle button");
    while(!buttons.MiddlePressed()); //Wait for middle button to be pressed
    while(buttons.MiddlePressed()); //Wait for middle button to be unpressed

    move_forward(motor_percent, expected_counts); //see function

    Sleep(2.0); //Wait for counts to stabilize
    //Print out data
    LCD.Write("Theoretical Counts: ");
    LCD.WriteLine(expected_counts);
    LCD.Write("Motor Percent: ");
    LCD.WriteLine(motor_percent);
    LCD.Write("Actual LE Counts: ");
    LCD.WriteLine(left_encoder.Counts());
    LCD.Write("Actual RE Counts: ");
    LCD.WriteLine(right_encoder.Counts());

    //60%
    motor_percent = 60;

    LCD.WriteLine("Shaft Encoder Lab Test");
    LCD.WriteLine("Press middle button");
    while(!buttons.MiddlePressed()); //Wait for middle button to be pressed
    while(buttons.MiddlePressed()); //Wait for middle button to be unpressed

    move_forward(motor_percent, expected_counts); //see function

    Sleep(2.0); //Wait for counts to stabilize
    //Print out data
    LCD.Write("Theoretical Counts: ");
    LCD.WriteLine(expected_counts);
    LCD.Write("Motor Percent: ");
    LCD.WriteLine(motor_percent);
    LCD.Write("Actual LE Counts: ");
    LCD.WriteLine(left_encoder.Counts());
    LCD.Write("Actual RE Counts: ");
    LCD.WriteLine(right_encoder.Counts());
    */

    //Must call this method first
    LCD.WriteLine("Starting");
    RPS.InitializeTouchMenu();

    //Method used to determine what colors are
    //calibrateOpto(buttons);

    //Test the moving
    //move(10, 40);
    //Show the color you are reading in
    //while(!buttons.MiddlePressed()){
    //    LCD.WriteLine(readLight(midOpt));
    //}
    LCD.WriteLine("getting data");
    bool lever[3];
    float loc[3];
    while(!buttons.RightPressed()){
        getLeverData(lever);
        getRPSData(loc);
        LCD.WriteLine("Loc data");
        LCD.WriteLine("x");
        LCD.WriteLine(loc[0]);
        LCD.WriteLine("y");
        LCD.WriteLine(loc[1]);
        LCD.WriteLine("bearing");
        LCD.WriteLine(loc[2]);

        LCD.WriteLine("Lever data");
        LCD.WriteLine("1");
        LCD.WriteLine(lever[0]);
        LCD.WriteLine("2");
        LCD.WriteLine(lever[1]);
        LCD.WriteLine("3");
        LCD.WriteLine(lever[2]);
        Sleep(1000);
        LCD.Clear();
    }
    //followLine();

    //Bump switches turning and stuff
    /*
    LCD.WriteLine("FF");
    left.SetPercent(30);
    right.SetPercent(30);
    while((bumpFR.Value())||(bumpFR.Value())){}
    LCD.WriteLine("Turn 1");
    left.Stop();
    //left.SetPercent(30);
    right.SetPercent(-30);
    while((bumpBR.Value())||(bumpBR.Value())){}
    LCD.WriteLine("FF again");
    left.SetPercent(30);
    right.SetPercent(30);
    while((bumpFR.Value())||(bumpFR.Value())){}

    left.SetPercent(-30);
    right.Stop();
    while((bumpBR.Value())||(bumpBR.Value())){}
    left.SetPercent(30);
    right.SetPercent(30);
    while((bumpFR.Value())||(bumpFR.Value())){}
    right.Stop();
    left.Stop();
    //Swap the motors that go backwards
    //drive forward full
    //servo.TouchCalibrate();
    //servo.SetMin(500);
    //servo.SetMax(2238);

    //while( true ){
        //servo.SetDegree(180.0/3.265*cds.Value());
    //}
    */


    return 0;
}

