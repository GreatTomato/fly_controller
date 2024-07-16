/*
 * gy_521.h
 *
 *  Created on: Jun 19, 2024
 *      Author: GreatTomato
 */
#include "stm32f4xx_hal.h"

#ifndef GT_GY_291_H_
#define GT_GY_291_H_
#endif

#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	double X;
	double Y;
	double Z;
} ADXL345_gyro_vectors_t;

typedef struct
{
	double X;
	double Y;
	double Z;
} ADXL345_accel_vectors_t;

uint8_t ADXL345_Init(I2C_HandleTypeDef *I2Cx);

void ADXL345_Read_Accel(I2C_HandleTypeDef *I2Cx, ADXL345_accel_vectors_t *DataStruct);
void ADXL345_Read_Gyro(I2C_HandleTypeDef *I2Cx, ADXL345_gyro_vectors_t *DataStruct);