/*
 * IO.h
 *
 *  Created on: March 15th, 2018
 *      Author: Marc Pfeiffer
 */

#ifndef IO_H_
#define IO_H_
#include "pwm.h"

//OutputFun - Handles output messages with identifiers
void OutputFun(char* , char* );

//InputFun - Handles input
char InputFun();

char menuChoice(char);

#endif /* IO_H_ */
