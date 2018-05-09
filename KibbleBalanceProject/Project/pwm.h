/*
 * pwm.h
 *
 *  Created on: March 15th, 2018
 *      Author: Marc Pfeiffer
 */

#ifndef PWM_H_
#define PWM_H_
#include "KibbleWattBalanceHeader.h"

//struct definition
struct ConfigPWM{
      volatile uint32_t frequency;
      volatile uint32_t dutyCycle;
      char id;
};

//calls initailizer
void laserStartUP(void);

//initializes laser pwm
void initializeConfigPWM(struct ConfigPWM*, char);

//checks laser choice
bool CheckChoice(char);

//checks laser pwm settings and asks for change
void pwmMenu();

//change frequency
void command_Freq();

//changes dutycycle
void command_Duty();

//changes pwm values
void PinGenConfig();


#endif /* PWM_H_ */
