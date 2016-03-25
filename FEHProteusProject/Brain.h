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
