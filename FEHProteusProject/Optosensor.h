#ifndef OPTOSENSOR_H
#define OPTOSENSOR_H
void calibrateOpto(ButtonBoard buttons){
    //Read and display sensor data
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    LCD.WriteLine("Waiting");
    while(!buttons.LeftPressed()){
        LCD.Write("Left: ");
        LCD.WriteLine(leftOpt.Value());
        LCD.Write("Mid: ");
        LCD.WriteLine(midOpt.Value());
        LCD.Write("Right: ");
        LCD.WriteLine(rightOpt.Value());
        Sleep(1000);
        LCD.Clear();
    }
}
void calibrateCdS(ButtonBoard buttons){
    //Read and display sensor data
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    LCD.WriteLine("Waiting");
    while(!buttons.LeftPressed()){
        LCD.Write("Value: ");
        LCD.WriteLine(CdS.Value());
        Sleep(2000);
        LCD.Clear();
    }
}

void followLine(int direction){
    //For direction, 1 is forward, -1 is backward
    LCD.WriteLine("GO!");
    float l, r, m;
    bool onLine = true;
    LCD.WriteLine("Entering loop");
    while(onLine){
        l = leftOpt.Value();
        r = rightOpt.Value();
        m = midOpt.Value();

        leftMotor.SetPercent(direction*20);
        rightMotor.SetPercent(direction*20);
        //If the middle is on at all, keep going
        if(m < LINE_SURFACE){
            LCD.WriteLine("mid getting reading");
        }else if(r < LINE_SURFACE){
            leftMotor.SetPercent(direction*30);
            LCD.WriteLine("Turning left");
        }else if(l < LINE_SURFACE){
            rightMotor.SetPercent(direction*30);
            LCD.WriteLine("Turning right");
        }else{
            LCD.WriteLine("exiting");
            leftMotor.SetPercent(0);
            rightMotor.SetPercent(0);
            onLine = false;
        }
    }
}

char readLight(AnalogInputPin cell){
    float color = cell.Value();
    char ret;
    if(color <= RED_COLOR){
        ret = 'r';
    }else if(color <= BLUE_COLOR){
        ret = 'b';
    }else if(color <= YELLOW_COLOR){
        ret = 'y';
    }else{
        ret = 'k';
    }
    return ret;
}


#endif // OPTOSENSOR_H

