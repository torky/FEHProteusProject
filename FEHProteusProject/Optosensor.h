#ifndef OPTOSENSOR_H
#define OPTOSENSOR_H

#endif // OPTOSENSOR_H

void calibrateOpto(ButtonBoard buttons){
    //Read and display sensor data
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    LCD.WriteLine("Waiting");
    while(!button.LeftPressed()){
        LCD.Write("Left: ");
        LCD.WriteLine(leftOpt.Value());
        LCD.Write("Right: ");
        LCD.WriteLine(rightOpt.Value());
        LCD.Write("Mid: ");
        LCD.WriteLine(midOpt.Value());
        Sleep(2000);
        LCD.Clear();
    }
}

void followLine(){
    LCD.WriteLine("GO!");
    float l, r, m;
    while(true){
        l = leftOpt.Value();
        r = rightOpt.Value();
        m = midOpt.Value();

        left.SetPercent(15);
        right.SetPercent(15);
        //THIS STRUCTURE IS NOT THE MOST EFFICIENT BUT IT IS CLEAR
        //If the middle is on at all, keep going
        if(m > LINE_VALUE){

        }else if(r < LINE_VALUE){
            left.SetPercent(20);
        }else if(l < LINE_VALUE){
            right.SetPercent(20);
        }else{
            left.SetPercent(0);
            right.SetPercent(0);
        }
    }

}

char readLight(AnalogInputPin opto){
    float color = opto.Value();
    char ret;
    if(color <= RED_COLOR){
        ret = 'r';
    }else if(color <= BLUE_COLOR){
        ret = 'b';
    }else{
        ret = 'n';
    }
    return ret;
}

