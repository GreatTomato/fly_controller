/*
 * gy_521.h
 *
 *  Created on: Jun 19, 2024
 *      Author: GreatTomato
 */
#include "stm32f4xx_hal.h"

#ifndef GT_GY_521_H_
#define GT_GY_521_H_
#endif

#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	float X;
	float Y;
	float Z;
} MPU6050_gyro_vectors_t;

typedef struct
{
	float X;
	float Y;
	float Z;
} MPU6050_accel_vectors_t;

uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx);

void MPU6050_Read_Accel(I2C_HandleTypeDef *I2Cx, MPU6050_accel_vectors_t *DataStruct);
void MPU6050_Read_Gyro(I2C_HandleTypeDef *I2Cx, MPU6050_gyro_vectors_t *DataStruct);
