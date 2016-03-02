#ifndef TASKS_H
#define TASKS_H

 // TASKS_H

void startWait(){
    while(readLight(CdS) != 'r');
}

void ascendRamp(){
    //Move forward
    move(10, 75);
    //Straighten out robot
    float data[3];
    getRPSData(data);
    if(data[2] > 4 && data[2] < 361){
        turn(-data[2], 10);
    }
}

void pushButtons(){
    //Move to buttons
    //Read light
    char color = readLight(midOpt);
    //Move based on color
    if(color == 'r'){

    }else if(color == 'b'){

    }else if(color == 'n'){

    }else{

    }
    //reverse to get on line

}

void approachRamp(){
    //Move to the ramp
    //Center robot and line up properly
}
#endif
