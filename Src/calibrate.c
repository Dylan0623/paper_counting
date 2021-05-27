#include "calibrate.h"
#define BaseAddress  ((uint32_t)0x08000000)


uint32_t paper_table[100] = {0} ;
uint32_t pwm_table[100] = {0};
uint32_t length_table = 0;


void data_init() {
    for(int i = 0; i < 100; i++) {
        paper_table[i] =  *(__IO uint32_t*) (BaseAddress +  4 * i);
    }

    for(int i = 0; i < 100; i++) {
        pwm_table[i] =  *(__IO uint32_t*) (BaseAddress + 400 + 4 * i);
    }
    while(paper_table[length_table] != 0) {
        length_table++;
    }
}

void data_clear() {
    for(int i = 0; i < 100; i++) {
        paper_table[i] = (uint32_t) 0;
    }

    for(int i = 0; i < 100; i++) {
        pwm_table[i] = (uint32_t) 0;
    }
    length_table = 0;
}

void data_save() {
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef f;

    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = 0x08000000;
    f.NbPages = 1;
    //设置PageError
    uint32_t PageError = 0;
    //调用擦除函数
    HAL_FLASHEx_Erase(&f, &PageError);
    //3、对FLASH烧写

    for(int i = 0; i < 100; i++) {

        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (BaseAddress +  4 * i),  paper_table[i]);
    }

    for(int i = 0; i < 100; i++) {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (BaseAddress + 400 +  4 * i),  pwm_table[i]);
    }
    //4、锁住FLASH
    HAL_FLASH_Lock();
}


void inner_sort() {
    int i = 0, j = length_table - 1;
    for( i = 0 ; i < length_table - 1 ; i++)
        for( j = length_table - 1 ; j > i ; j --) {
            if(paper_table[i] > paper_table[j]) {
                paper_table[i] = paper_table[i] ^ paper_table[j];
                paper_table[j] = paper_table[i] ^ paper_table[j];
                paper_table[i] = paper_table[i] ^ paper_table[j];
                pwm_table[i] = pwm_table[j] ^  pwm_table[i];
                pwm_table[j] = pwm_table[j] ^  pwm_table[i];
                pwm_table[i] = pwm_table[j] ^  pwm_table[i];
            }
        }
}

void add_point( int t_paper, int t_pwm ) {
    if(length_table != 499) {
        paper_table[length_table] = t_paper;
        pwm_table[length_table++] = t_pwm;
        inner_sort();
    }
}

int get_value(int now_pwm) {
    if(length_table < 2) return 0;

    for(int i = 0; i < length_table - 1 ; i++) {
        if( (now_pwm <= pwm_table[i + 1]) && (now_pwm > pwm_table[i]) ) {
            return paper_table[i] + ( now_pwm - pwm_table[i] ) * ( paper_table[i + 1] - paper_table[i] ) / (pwm_table[i + 1] - pwm_table[i]);
        }
    }
    if(now_pwm < pwm_table[0]) return paper_table[0] - (  pwm_table[0] - now_pwm) * ( paper_table[1] - paper_table[0] ) / (pwm_table[1] - pwm_table[0]);
    else return paper_table[length_table - 1] + (  now_pwm - pwm_table[length_table - 1]   ) * ( paper_table[length_table - 1] - paper_table[length_table - 2] ) / (pwm_table[length_table - 1] - pwm_table[length_table - 2]);
}

void delete_by_index(int index) {
    if(index == 0 && length_table == 1) {
        paper_table[index] = 0;
        pwm_table[index] = 0;
        length_table = 0;

    } else {
        paper_table[index] = 0;
        pwm_table[index] = 0;
        paper_table[index] = paper_table[index] ^ paper_table[length_table - 1];
        paper_table[length_table - 1] = paper_table[index] ^ paper_table[length_table - 1];
        paper_table[index] = paper_table[index] ^ paper_table[length_table - 1];
        pwm_table[index] = pwm_table[length_table - 1] ^  pwm_table[index];
        pwm_table[length_table - 1] = pwm_table[length_table - 1] ^  pwm_table[index];
        pwm_table[index] = pwm_table[length_table - 1] ^  pwm_table[index];
        length_table--;
        inner_sort();

    }

}













