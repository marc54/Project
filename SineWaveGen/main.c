#include "sineWaveGenHeader.h"
#include "HardwareInitalize.h"
#include "IO.h"

#define PI 3.14159265358979323846264338327950288419716939937510
#define INTERVAL 65


volatile float sineWave[(INTERVAL-1)*4];
int indexer = 0;
int *indexChange;
int frequency;
int *frequencyChange;



int main(void){

    startUp();

    float deltaDegree = 90.0/(INTERVAL-1), angle = 0.0;
    int index, radius;
    char buffer[50];


    radius = typeRadius();
    frequency = typeFrequency();
    sprintf(buffer,"The first %d values are as follows:\n", INTERVAL);
    OutputFun("bbb006", buffer);
    memset(buffer,0,sizeof(buffer));

    for( index = 0 ; index < INTERVAL ; index++){
        sineWave[index] = sinf(angle*(PI/180))*radius;
        angle += deltaDegree;
        sprintf(buffer,": Value %02d -> %0f", (index+1) ,sineWave[index]+radius);
        OutputFun("bbb007", buffer);
    }

    // creates the rest of the sine wave
    for(index = 1 ; index <INTERVAL ; index++){
        sineWave[INTERVAL-1+index] = sineWave[INTERVAL-1-index];
        sineWave[2*(INTERVAL-1)+index] = -(sineWave[index]);
        sineWave[3*(INTERVAL-1)+index] = -sineWave[INTERVAL-1-index];
    }

    //raises the sine wave above the line y= 0 so all values can be greater or equal to zero
    for(index = 0 ; index <256; index++){
        sineWave[index] += radius;
    }
    initializeTimer();
    while(1){

    }
}
void Timer0IntHandler(void) {
    frequencyChange = &frequency;
    indexChange = &indexer;
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    volatile uint32_t ui32PWMClock  = SysCtlClockGet();
    volatile uint32_t ui32Load = (ui32PWMClock / (frequency)) - 1;
    volatile uint32_t ui32width =((sineWave[*indexChange]) * ui32Load)/1000;
    if(*indexChange < 255){
        if(ui32width !=0){
            PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
            PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, ui32width);
            PWMGenEnable(PWM1_BASE, PWM_GEN_3);
            PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
        }
        else{
            PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
        }

        *indexChange = *indexChange +1;
    }
    else{
        *indexChange = 0;
        PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, ui32width);
        PWMGenEnable(PWM1_BASE, PWM_GEN_3);
        PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
        *indexChange = *indexChange +1;
    }

}




