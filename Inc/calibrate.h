#ifndef __CALIBRATE_H_
#define __CALIBRATE_H_
#include "main.h"


void add_point( int t_paper, int t_pwm ) ;
int get_value(int now_pwm);
void delete_by_index(int index);
void data_init(void) ;
void data_save(void);
void data_clear(void);

extern uint32_t paper_table[100]  ;
extern uint32_t pwm_table[100];
extern uint32_t length_table;
 
#endif
