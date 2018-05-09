/*
 * IO.c
 *
 *  Created on: Apr 27, 2018
 *      Author: Marc Pfeiffer
 */

#include "sineWaveGenHeader.h"

//OutputFun - Handles output messages with identifiers
void OutputFun(char* ident, char* str){

    UARTprintf("%s%s%s%s", ident, " ", str, "\n");

}
int typeRadius(){
    bool wait = true;
    char hold[20], choice;
    int i = 0 , radius;

        OutputFun("bbb000","*********************************");

        while(wait){
            OutputFun("bbb001","Please select an arbitrary radius: ");
            do{
                choice = UARTgetc();
                if(choice!= 13){
                    if((choice>=48 && choice <= 57) ){

                        hold[i] = choice;
                        i++;
                    }
                    else{
                        OutputFun("bbb002","Invalid Entry: Start again!");
                        i=0;
                        memset(hold,0,sizeof(hold));
                    }
                }
            }while(choice != 13);
            wait = false;
            sscanf(hold, "%d", &radius);
        }
    return radius;
}

int typeFrequency(){
    bool wait = true;
    char hold[20], choice;
    int i = 0 , Frequency;

        OutputFun("bbb003","*********************************");

        while(wait){
            OutputFun("bbb004","Please select an arbitrary Frequency: ");
            do{
                choice = UARTgetc();
                if(choice!= 13){
                    if((choice>=48 && choice <= 57) ){

                        hold[i] = choice;
                        i++;
                    }
                    else{
                        OutputFun("bbb005","Invalid Entry: Start again!");
                        i=0;
                        memset(hold,0,sizeof(hold));
                    }
                }
            }while(choice != 13);
            wait = false;
            sscanf(hold, "%d", &Frequency);
        }
    return Frequency;
}

