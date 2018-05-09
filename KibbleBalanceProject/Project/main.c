/*
*	Created By: Marc Pfeiffer
*	Email: marc.pfeiffer54@gmail.com
*	Semester: Spring 2018
*
*/
#include "KibbleWattBalanceHeader.h"
#include "HardwareInitalize.h"
#include "IO.h"
#include "pwm.h"

int main(void) {

    // Initialize the Hardware
    startUp();
    
    char choice = 'a';
    bool wait  = true;
    
    UARTprintf("\n\n************************************\n");
    OutputFun("aaa000","Welcome to the Kibble Watt Balance.\n");

    while(choice != 'E'){
        wait = true;
        while(wait){
            OutputFun("aaa009","Please select a laser:");
            OutputFun("aaa010","Laser 1 --- A");
            OutputFun("aaa011","Laser 2 --- B");
            OutputFun("aaa012","Back    --- E");
            choice = UARTgetc();
            choice = toupper(choice);
            wait = CheckChoice(choice);
        }
    }
}

