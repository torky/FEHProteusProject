#ifndef BRAIN_H
#define BRAIN_H

static const int LIFT_DUMBBELL = 0;
static const int SCAN_BUTTON_COLOR = 1;
static const int HIT_BUTTON = 2;
static const int HOLD_BUTTON_FOR_5 = 3;
static const int LEVER_RED = 4;
static const int LEVER_WHITE = 5;
static const int LEVER_BLUE = 6;
static const int DEPOSIT_DUMBELL = 7;
static const int LAUNCH_BUTTON = 8;

static const float startPoint[2] = {8.3, 13.2};
static const float finishPoint[2] = {86.4, 7.4};
static const float dumbbellStart[2] = {27.2, 16.3};
static const float belowRamp[2] = {27.7, 26};
static const float aboveRamp[2] = {31, 42.5};
static const float fuelLight[2] = {26.5, 65.5};
static const float dumbbellEnd[2] = {5.3, 47.3};
static const float redLever[2] = {4, 40.4};
static const float whiteLever[2] = {9, 40.4};
static const float blueLever[2] = {14, 40.4};

bool tasksCompleted[9];

int points = 0;
float time = 0;

float xLocation;
float yLocation;
float heading;

float aboveRampPointX;
float aboveRampPointY;

float belowRampPointX;
float belowRampPointY;

void determineTime(int task, int startX, int startY){

}

void orderTasks(){

}

void chooseTask(){

}

/*
void executeTask(int task){
    switch(task){
    case LIFT_DUMBBELL:

    case SCAN_BUTTON_COLOR:

    case HIT_BUTTON:

    case HOLD_BUTTON_FOR_5:

    case LEVER_RED:

    case LEVER_WHITE:

    case LEVER_BLUE:

    case DEPOSIT_DUMBELL:

    case LAUNCH_BUTTON:

    }
}*/

#endif // BRAIN_H
