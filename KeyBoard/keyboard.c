#include "keyboard.h"
#include "main.h"


uint8_t key_scan() { 

    uint8_t key_value = 0;
    HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C4_GPIO_Port, C4_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
    if(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {
        HAL_Delay(5);
        if(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {
            while(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {}
            return 1;
        }
    }
    if(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {
        HAL_Delay(5);
        if(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {
            while(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {}
            return 2;
        }
    }
    if(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {
        HAL_Delay(5);
        if(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {
            while(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {}
            return 3;
        }
    }
    if(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {
        HAL_Delay(5);
        if(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {
            while(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {}
            return 4;
        }
    }



    HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C4_GPIO_Port, C4_Pin, GPIO_PIN_RESET);


    HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
    if(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {

        HAL_Delay(5);
        if(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {
            while(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {}
            return 5;
        }
    }
    if(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {

        HAL_Delay(5);
        if(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {
            while(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {}
            return 6;
        }
    }
    if(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {

        HAL_Delay(5);
        if(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {
            while(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {}
            return 7;
        }
    }
    if(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {
        HAL_Delay(5);
        if(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {
            while(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {}
            return 8;
        }
    }


    HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C4_GPIO_Port, C4_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
    if(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {

        while(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {}
        return 9;
    }
    if(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {

        while(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {}
        return 10;
    }
    if(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {

        while(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {}
        return 11;
    }
    if(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {

        while(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {}
        return 12;
    }

    HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C4_GPIO_Port, C4_Pin, GPIO_PIN_RESET);



    HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);
    if(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {

        while(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin) == GPIO_PIN_SET) {}
        return 13;
    }
    if(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {

        while(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin) == GPIO_PIN_SET) {}
        return 14;
    }
    if(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {

        while(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) == GPIO_PIN_SET) {}
        return 15;
    }
    if(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {
        while(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin) == GPIO_PIN_SET) {}
        return 16;
    }

    return key_value;
}
