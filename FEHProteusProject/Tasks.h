#ifndef TASKS_H
#define TASKS_H

#endif // TASKS_H

void startWait(){
    while(readLight(midOpt) != 'r');
}

void ascendRamp(){
    //Move forward
    //Straighten out robot
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
