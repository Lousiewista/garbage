#ifndef __PWM_H
#define __PWM_H

void pwm_write(int pwm_pin);
void pwm_stop(int pwm_pin);

#define PWM_GARBAGE             7 
#define PWM_RECOVERABLE_GARBAGE 5

#endif