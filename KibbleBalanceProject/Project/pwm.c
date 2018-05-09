/*
 * pwm.c
 *
 *  Created on: Apr 12, 2018
 *      Author: Marc Pfeiffer
 *
 *  This program requires a minimum  stack of 1024, otherwise
 *  code will not run:
 *  1) sprintf() will hang
 */
#include "KibbleWattBalanceHeader.h"
#include "pwm.h"
#include "IO.h"

struct ConfigPWM pwmA;                                                                 // This configures the PWM generator 0, using PD0.
struct ConfigPWM pwmB;                                                                 // This configures the PWM generator 1, using PD1.
struct ConfigPWM* Laser;                                                               // This points to the desired PWM generator.

// Initializes PWM
void laserStartUP(void){
    initializeConfigPWM(&pwmA, 'A');
    initializeConfigPWM(&pwmB, 'B');
}
//Constructor for initialize
void initializeConfigPWM(struct ConfigPWM* gen, char identity){
    gen->dutyCycle = 0;
    gen->frequency = 700;
    gen->id = identity;
}


bool CheckChoice( char c){
    laserStartUP();
    bool wait;
    switch(c){
    case 'A':
        OutputFun("\n\naaa013","Laser 1 selected:\n\n");
        Laser = &pwmA;
        pwmMenu();
        wait = false;
        break;
    case 'B':
        OutputFun("\n\naaa014","Laser 2 selected:\n\n");
        Laser = &pwmB;
        pwmMenu();
        wait = false;
        break;
    case 'E':
        OutputFun("\n\naaa015","Main Menu\n");

        wait = false;
        break;
    default:
        OutputFun("\n\naaa016", "Invalid Entry, Please try again!");
        wait = true;
        break;
    }
    return wait;
}


void pwmMenu(){
    char choice = 'a';
    char buffer[50];
    char format1[] = "Frequency set to : %d Hz\n";
    char format2[] = "Duty Cycle is set to : %d \n";
    while(choice != 'B'){
        bool wait = true;
        while(wait){


            int freq = (int)Laser->frequency;
            sprintf(buffer,format1,freq);
            OutputFun("aaa017", buffer);
            memset(buffer,0,sizeof(buffer));

            int dutyC = (int)Laser->dutyCycle;
            sprintf(buffer,format2,Laser->dutyCycle);
            OutputFun("aaa018",buffer);
            memset(buffer,0,sizeof(buffer));



            OutputFun("aaa019" , "Which would you like to change?\n");
            OutputFun("aaa020","Frequency     --- F");
            OutputFun("aaa021","Duty Cycle    --- D");
            OutputFun("aaa022","Back          --- B");

            choice = UARTgetc();
            choice = toupper(choice);

            switch(choice){
            case 'F':
                OutputFun("\n\naaa023", "Please enter new frequency amount:\n");
                command_Freq();
                wait = false;
                break;
            case 'D':
                OutputFun("\n\naaa024", "Please enter new duty cycle amount:\n");
                wait = false;
                command_Duty();
                break;
            case 'B':
                OutputFun("\n\naaa025", "Nothing was changed.");
                wait = false;
                break;
            default:
                OutputFun("\n\naaa026", "Invalid Entry, Please try again!");
                wait = true;
                break;
            }
        }
    }
}


void command_Freq(){
    char choice;
    char hold[10];
    bool wait = true;
    int32_t freq = 0;
    int i = 0;
    wait = true;


    while(wait){
        OutputFun("aaa027","Enter the frequency you wish to set the pins to (in Hertz, Greater than or equal to 1 )");
        do{
            choice = UARTgetc();
            if(choice!= 13){
                if((choice>=48 && choice <= 57) ){
                    if(choice == 48 && i == 0 ){
                        OutputFun("aaa028","Invalid Entry!");
                    }
                    else{
                        hold[i] = choice;
                        i++;
                    }

                }
                else{
                    OutputFun("aaa029","Invalid Entry!");
                    i=0;
                    memset(hold,0,sizeof(hold));
                }
            }
        }while(choice != 13);
        wait = false;

        sscanf(hold, "%d", &freq);


    }
    Laser->frequency = freq;
    PinGenConfig();

}



// This function controls the Duty Cycle.
void command_Duty(){
    char choice;
    char hold[10];
    bool wait = true;
    int duty = 0;
    int i = 0;
    do{
        wait = true;
        while(wait){

            OutputFun("aaa031","Enter the Duty Cycle you want to set the pins to (between 0 - 100)");
            do{
                choice = UARTgetc();
                if(choice!= 13){
                    if((choice>=48 && choice <= 57) ){

                        hold[i] = choice;
                        i++;


                    }
                    else{
                        OutputFun("aaa032","Invalid Entry!");
                        i=0;
                        memset(hold,0,sizeof(hold));
                    }
                }
            }while(choice != 13);


            wait = false;
            //UARTprintf("%c",hold);
            sscanf(hold, "%d", &duty);
            // duty = atoi(hold);

            if(duty<0 || duty>100){
                OutputFun("aaa033", "Invalid Entry! Input out of range");
            }
            else{
                Laser->dutyCycle = duty;
                //OutputFun("aaa034", strcat("DutyCylce is now set to ",(char*)duty));
                //UARTprintf("%d\n", duty);
                //UARTprintf(Laser->dutyCycle);
            }
        }
    } while(duty<0 || duty>100);



    PinGenConfig();
}


// This function configures the pins and the generators.
void PinGenConfig(){


    volatile uint32_t ui32PWMClock;
    volatile uint32_t ui32Load;
    volatile uint32_t ui32width;

    ui32PWMClock = SysCtlClockGet();
    ui32Load= (ui32PWMClock / (Laser->frequency)) - 1;
    ui32width= ((Laser->dutyCycle) * ui32Load) / 100;
    //width = width ? width : 1;

    if(Laser->id == 'A'){
        if(Laser->dutyCycle != 0){
            PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui32width);
            PWMGenEnable(PWM1_BASE, PWM_GEN_2);
            PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
        }
        else{
            PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, false);

        }
    }






    if(Laser->id == 'B'){

        if(Laser->dutyCycle != 0){
                   PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
                   PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);
                   PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, ui32width);
                   PWMGenEnable(PWM1_BASE, PWM_GEN_3);
                   PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
               }
               else{
                   PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, false);

               }

    }

}

