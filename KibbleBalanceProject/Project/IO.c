/*
 * IO.c
 *
 *  Created on: Apr 16, 2018
 *      Author: Marc Pfeiffer
 */

#include "IO.h"


void OutputFun(char* ident, char* str){
    UARTprintf("%s%s%s%s", ident, " ", str, "\n");
}
char InputFun(){
    return UARTgetc();
}



