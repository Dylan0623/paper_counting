#include "show.h"
#include "main.h"
#include "OLED_I2C.h"
#include "keyboard.h"
#include "calibrate.h"
#include "tim.h"

int welcome() {

    int keyvalue;

    OLED_ShowCN(0, 0, 0);
    OLED_ShowCN(16, 0, 1);
    OLED_ShowCN(32, 0, 2);
    OLED_ShowCN(48, 0, 3);
    OLED_ShowCN(64, 0, 4);
    OLED_ShowCN(80, 0, 5);
    OLED_ShowCN(96, 0, 6);
    OLED_ShowCN(112, 0, 7);
    OLED_ShowCN(32, 6, 8);
    OLED_ShowCN(48, 6, 9);
    OLED_ShowCN(64, 6, 10);
    OLED_ShowCN(80, 6, 11);//“纸张计数显示装置欢迎使用”

    while(1) {

        if(HAL_GPIO_ReadPin(key_GPIO_Port, key_Pin) == GPIO_PIN_RESET) {
            return 4;
        }//PA8按下时state = 4

        HAL_Delay(100);
        if(flag) {
            OLED_CLS();
            OLED_ShowBigCN(0, 2, 8);
            OLED_ShowBigCN(32, 2, 9);
            OLED_ShowBigCN(64, 2, 10);
            OLED_ShowBigCN(96, 2, 11);//“极板短路”
            while(flag == 1) {
                HAL_Delay(100);
            };
            OLED_CLS();
            return 0;
        }//检测极板是否短路，短路时flag为1
 
        keyvalue = key_scan();

        if(keyvalue != 0 && keyvalue % 4 == 0)

            return keyvalue / 4 - 1;//功能按键，0~3

    }
}

int calibrate() {
    int keyvalue;
    unsigned char temp[3] ;
    unsigned char pwm[9];
    int length = 0 ;
    temp[0] = 0;
    OLED_ShowCN(0, 0, 12);
    OLED_ShowCN(16, 0, 13);
    OLED_ShowCN(32, 0, 14);
    OLED_ShowCN(48, 0, 15);
    OLED_ShowCN(64, 0, 16);
    OLED_ShowCN(80, 0, 17);//“当前测量值：”

    OLED_ShowCN(0, 4, 18);
    OLED_ShowCN(16, 4, 19);
    OLED_ShowCN(32, 4, 20);
    OLED_ShowCN(48, 4, 21);
    OLED_ShowCN(64, 4, 22);
    OLED_ShowCN(80, 4, 17);//“输入纸张数：”

    pwm[6] = 'H';
    pwm[7] = 'z';
    pwm[8] = 0;

    while(1) {

        if(HAL_GPIO_ReadPin(key_GPIO_Port, key_Pin) == GPIO_PIN_RESET) {
            return 4;
        }
        pwm[0] = pwm_value / 100000 + '0';
        pwm[1] = pwm_value % 100000 / 10000 + '0';
        pwm[2] = pwm_value % 10000 / 1000 + '0';
        pwm[3] = pwm_value % 1000 / 100 + '0';
        pwm[4] = pwm_value % 100 / 10 + '0';
        pwm[5] = pwm_value % 10 + '0';

        if(flag) {
            OLED_CLS();
            OLED_ShowBigCN(0, 2, 8);
            OLED_ShowBigCN(32, 2, 9);
            OLED_ShowBigCN(64, 2, 10);
            OLED_ShowBigCN(96, 2, 11);//“极板短路”
            while(flag == 1) {
                HAL_Delay(100);
            };
            OLED_CLS();
            return 1;
        }

        keyvalue = key_scan();

        if( length != 2 && ( keyvalue == 1 || keyvalue == 2 || keyvalue == 3 || keyvalue == 5 || keyvalue == 6 || keyvalue == 7 || keyvalue == 9 || keyvalue == 10 || keyvalue == 11 || keyvalue == 14) ) {
            temp[length++] = ((keyvalue / 4) * 3 + keyvalue % 4) % 11 + '0';
            OLED_ShowCN(0, 6, 23);
            OLED_ShowCN(16, 6, 23);
            OLED_ShowCN(32, 6, 23);
            OLED_ShowCN(48, 6, 23);
            OLED_ShowCN(64, 6, 23);
            OLED_ShowCN(80, 6, 23);
        }
        if(keyvalue == 15 && length != 0) {
            temp[ --length] = 0;
            OLED_ShowCN(0, 6, 23);
            OLED_ShowCN(16, 6, 23);
            OLED_ShowCN(32, 6, 23);
            OLED_ShowCN(48, 6, 23);
            OLED_ShowCN(64, 6, 23);
            OLED_ShowCN(80, 6, 23);
        }//按下第15个按键，temp的第length-1个数置0

        if(keyvalue == 13 && length != 0) {

            if(length == 1) {
                add_point((temp[0] - '0') * 10, pwm_value );
            } else {
                add_point((temp[0] - '0') * 100 + (temp[1] - '0') * 10, pwm_value );
            }

            OLED_CLS();
            OLED_ShowBigCN(0, 2, 0);
            OLED_ShowBigCN(32, 2, 1);
            OLED_ShowBigCN(64, 2, 2);
            OLED_ShowBigCN(96, 2, 3);//添加成功
            HAL_Delay(100);
            return 1;
        }//按下第13个按键，将纸张数和频率同时存入pwm_table和paper_pwm数组中
        if(keyvalue != 0 &&  keyvalue % 4 == 0)

            return keyvalue / 4 - 1;
        OLED_ShowStr(0, 2, pwm, 2);
        OLED_ShowStr(0, 6, temp, 2);
    }
}


int measure() {

    int keyvalue, paper = 0;
    unsigned char res[5], pwm[9];

    OLED_ShowCN(0, 4, 37);
    OLED_ShowCN(16, 4, 38);
    OLED_ShowCN(32, 4, 39);
    OLED_ShowCN(48, 4, 40);
    OLED_ShowCN(64, 4, 36);
    OLED_ShowCN(80, 4, 17);//“最终判断值：”

    pwm[6] = 'H';
    pwm[7] = 'z';
    pwm[8] = 0;

    while(1) {

        if(HAL_GPIO_ReadPin(key_GPIO_Port, key_Pin) == GPIO_PIN_RESET) {
            return 4;
        }
        pwm[0] = pwm_value / 100000 + '0';
        pwm[1] = pwm_value % 100000 / 10000 + '0';
        pwm[2] = pwm_value % 10000 / 1000 + '0';
        pwm[3] = pwm_value % 1000 / 100 + '0';
        pwm[4] = pwm_value % 100 / 10 + '0';
        pwm[5] = pwm_value % 10 + '0';

        if(flag) {
            OLED_CLS();
            OLED_ShowBigCN(0, 2, 8);
            OLED_ShowBigCN(32, 2, 9);
            OLED_ShowBigCN(64, 2, 10);
            OLED_ShowBigCN(96, 2, 11);
            while(flag == 1) {
                HAL_Delay(100);
            };
            OLED_CLS();
            return 2;
        }

        keyvalue = key_scan();

        if(keyvalue != 0 && keyvalue != 16 &&  keyvalue % 4 == 0)

            return keyvalue / 4 - 1;

        if(keyvalue == 16) {
            HAL_Delay(2500);
            paper = get_value((int)pwm_value);
            paper = (paper < 10) ? 10 : paper;
            paper = (paper > 499) ? 499 : paper;
            HAL_TIM_Base_Stop_IT(&htim1);
            HAL_GPIO_WritePin(BEER_GPIO_Port, BEER_Pin, GPIO_PIN_SET);
            HAL_Delay(500);
            HAL_GPIO_WritePin(BEER_GPIO_Port, BEER_Pin, GPIO_PIN_RESET);
            HAL_TIM_Base_Start_IT(&htim1);
        }
        res[0] = paper / 100 + '0';
        res[1] = paper % 100 / 10 + '0';
        res[2] = '.';
        res[3] = paper % 10 + '0';
        res[4] = 0;
        OLED_ShowStr(0, 2, res, 2);
        OLED_ShowStr(0, 0, pwm, 2);

        if(paper % 10 >= 5) {
            res[0] = (paper + 10) / 100 + '0';
            res[1] = (paper + 10) % 100 / 10 + '0';
        }
        res[2] = 0;
        OLED_ShowStr(0, 6, res, 2);
    }
}


int change_value() {

    int keyvalue, page = 0, choose = 0;

    unsigned	char data[4][17];

    for(int i = 0 ; i < 4 ; i++) {
        data[i][1] = ' ';
        data[i][4] = '.';
        data[i][6] = '-';
        data[i][7] = '>';
        data[i][14] = 'H';
        data[i][15] = 'z';
        data[i][16] = 0;
    }

    for(int i = 0 ; i < 4 ; i++) {
        if(i == choose) data[i][0] = '*';
        else data[i][0] = ' ';
        data[i][2] = paper_table[page * 4 + i] / 100 + '0';
        data[i][3] = paper_table[page * 4 + i] % 100 / 10 + '0';
        data[i][5] = paper_table[page * 4 + i] % 10 + '0';
        data[i][8] = pwm_table[page * 4 + i] / 100000 + '0';
        data[i][9] = pwm_table[page * 4 + i] % 100000 / 10000 + '0';
        data[i][10] = pwm_table[page * 4 + i] % 10000 / 1000 + '0';
        data[i][11] = pwm_table[page * 4 + i] % 1000 / 100 + '0';
        data[i][12] = pwm_table[page * 4 + i] % 100 / 10 + '0';
        data[i][13] = pwm_table[page * 4 + i] % 10 + '0';
    }//date一行对应一个纸张数和频率：* 23.4->125370Hz

    while(1) {

        if(HAL_GPIO_ReadPin(key_GPIO_Port, key_Pin) == GPIO_PIN_RESET) {
            return 4;
        }
        if(flag) {
            OLED_CLS();
            OLED_ShowBigCN(0, 2, 8);
            OLED_ShowBigCN(32, 2, 9);
            OLED_ShowBigCN(64, 2, 10);
            OLED_ShowBigCN(96, 2, 11);
            while(flag == 1) {
                HAL_Delay(100);
            };
            OLED_CLS();
            return 3;
        }

        keyvalue = key_scan();

        if(keyvalue == 1 || keyvalue == 2 || keyvalue == 3) choose = keyvalue - 1;
        if(keyvalue == 5 ) choose = 3;

        for(int i = 0 ; i < 4 ; i++) {
            if(i == choose) data[i][0] = '*';
            else data[i][0] = ' ';
        }//选择第几行

        if(keyvalue == 10) {
            if(page  < length_table / 4 ) {
                page ++;
                for(int i = 0 ; i < 4 ; i++) {
                    data[i][2] = paper_table[page * 4 + i] / 100 + '0';
                    data[i][3] = paper_table[page * 4 + i] % 100 / 10 + '0';
                    data[i][5] = paper_table[page * 4 + i] % 10 + '0';
                    data[i][8] = pwm_table[page * 4 + i] / 100000 + '0';
                    data[i][9] = pwm_table[page * 4 + i] % 100000 / 10000 + '0';
                    data[i][10] = pwm_table[page * 4 + i] % 10000 / 1000 + '0';
                    data[i][11] = pwm_table[page * 4 + i] % 1000 / 100 + '0';
                    data[i][12] = pwm_table[page * 4 + i] % 100 / 10 + '0';
                    data[i][13] = pwm_table[page * 4 + i] % 10 + '0';
                }
            }
        }//将table的四个纸张数和四个频率数对应地存放到data数组里面，然后显示在OLED上
        if(keyvalue == 14) {
            if(page > 0) {
                page --;
                for(int i = 0 ; i < 4 ; i++) {
                    data[i][2] = paper_table[page * 4 + i] / 100 + '0';
                    data[i][3] = paper_table[page * 4 + i] % 100 / 10 + '0';
                    data[i][5] = paper_table[page * 4 + i] % 10 + '0';
                    data[i][8] = pwm_table[page * 4 + i] / 100000 + '0';
                    data[i][9] = pwm_table[page * 4 + i] % 100000 / 10000 + '0';
                    data[i][10] = pwm_table[page * 4 + i] % 10000 / 1000 + '0';
                    data[i][11] = pwm_table[page * 4 + i] % 1000 / 100 + '0';
                    data[i][12] = pwm_table[page * 4 + i] % 100 / 10 + '0';
                    data[i][13] = pwm_table[page * 4 + i] % 10 + '0';
                }
            }
        }
        if(keyvalue == 13) {
            OLED_CLS();
            OLED_ShowBigCN(0, 2, 6);
            OLED_ShowBigCN(32, 2, 7);
            OLED_ShowBigCN(64, 2, 2);
            OLED_ShowBigCN(96, 2, 3);//“保存成功”
            data_save();
            OLED_CLS();
            return 3;
        }

        if(keyvalue == 16) {
            OLED_CLS();
            OLED_ShowBigCN(0, 2, 12);
            OLED_ShowBigCN(32, 2, 13);
            OLED_ShowBigCN(64, 2, 2);
            OLED_ShowBigCN(96, 2, 3);//“清除成功”
            HAL_Delay(500);
            data_clear();//将数组里面的数据全部清除
            OLED_CLS();
            return 3;
        }
        if(keyvalue == 15) {
            OLED_CLS();
            OLED_ShowBigCN(0, 2, 4);
            OLED_ShowBigCN(32, 2, 5);
            OLED_ShowBigCN(64, 2, 2);
            OLED_ShowBigCN(96, 2, 3);//“删除成功”
            HAL_Delay(100);
            delete_by_index(page * 4 + choose);//删除pwm_table,paper_table数组里面的某个数据，然后重新排序
            OLED_CLS();
            return 3;
        }


        if(keyvalue == 4 || keyvalue == 8 || keyvalue == 12)
            return keyvalue / 4 - 1;

        OLED_ShowStr(0, 0, data[0], 2);
        OLED_ShowStr(0, 2, data[1], 2);
        OLED_ShowStr(0, 4, data[2], 2);
        OLED_ShowStr(0, 6, data[3], 2);
    }
}


int finlly(void) {

    int paper;
    unsigned char res[3];
    res[2] = 0;
    OLED_CLS();
    HAL_Delay(2500);
    paper = get_value((int)pwm_value);
    paper = (paper < 10) ? 10 : paper;
    paper = (paper > 499) ? 499 : paper;
    HAL_TIM_Base_Stop_IT(&htim1);
    HAL_GPIO_WritePin(BEER_GPIO_Port, BEER_Pin, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(BEER_GPIO_Port, BEER_Pin, GPIO_PIN_RESET);
    HAL_TIM_Base_Start_IT(&htim1);

    while(1) {

        if(flag) {
            OLED_CLS();
            OLED_ShowBigCN(0, 2, 8);
            OLED_ShowBigCN(32, 2, 9);
            OLED_ShowBigCN(64, 2, 10);
            OLED_ShowBigCN(96, 2, 11);
            while(flag == 1) {
                HAL_Delay(100);
            };
            OLED_CLS();
        }

        if(HAL_GPIO_ReadPin(key_GPIO_Port, key_Pin) == GPIO_PIN_RESET) {
            OLED_CLS();
            HAL_Delay(2500);
            paper = get_value((int)pwm_value);
            paper = (paper < 10) ? 10 : paper;
            paper = (paper > 499) ? 499 : paper;
            HAL_TIM_Base_Stop_IT(&htim1);
            HAL_GPIO_WritePin(BEER_GPIO_Port, BEER_Pin, GPIO_PIN_SET);
            HAL_Delay(500);
            HAL_GPIO_WritePin(BEER_GPIO_Port, BEER_Pin, GPIO_PIN_RESET);
            HAL_TIM_Base_Start_IT(&htim1);
        }
        if(paper % 10 >= 5) {
            OLED_ShowBigNb(32, 0, (paper + 10) / 100);
            OLED_ShowBigNb(64, 0, (paper + 10) % 100 / 10);
        } else {
            OLED_ShowBigNb(32, 0, paper  / 100);
            OLED_ShowBigNb(64, 0, paper  % 100 / 10);
        }
    }
}

