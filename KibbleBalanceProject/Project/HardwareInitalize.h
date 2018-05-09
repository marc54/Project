/*
 * HardwareInitalize.h
 *
 *  Created on: March 15th, 2018
 *      Author: Marc Pfeiffer
 */

#ifndef HARDWAREINITALIZE_H_
#define HARDWAREINITALIZE_H_

// This function initializes the clock.
void initializeClock() {
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
}
void Timer0IntHandler(void) {
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

// This function initializes the interrupt.
void initializeInterrupt(){
    IntMasterEnable();
}

// This function initializes the GPIO.
void initializeGPIO(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    
}
// This function initializes the PWM.
void initializePWM(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2);
}


// This function initializes the UART.
void initializeUART(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);
}


// This function initializes the Timer.
void initializeTimer(){
    uint32_t period = (SysCtlClockGet() / 1000) / 1;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, period - 1);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

void startUp(){
    // Initialize the Hardware.
    initializeClock();
    initializeInterrupt();
    initializeGPIO();
    initializeUART();
    initializeTimer();
    initializePWM();
}


#endif /* HARDWAREINITALIZE_H_ */
