/*
 * gy_521.c
 *
 *  Created on: Jun 19, 2024
 *      Author: GreatTomato
 */

#include "gy_521.h"


#define REG_SMPRT_DIV 0x19
#define REG_CONFIG 0x1A
#define REG_GYRO_CONFIG 0x1B
#define REG_ACCEL_CONFIG 0x1C
#define REG_FIFO_EN 0x23
#define REG_ACCEL_XOUT_H 0x3B
#define REG_GYRO_XOUT_H 0x43
#define REG_USER_CTRL 0x6A
#define REG_PWR_MGMT_1 0x6B
#define REG_WHO_AM_I 0x75
//#define REG_WHO_AM_I_ 104
#define MPU6050_ADDR 0xD2
const uint16_t i2c_timeout = 1000;

HAL_StatusTypeDef ret;
uint8_t ok = 1;



uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx)
{
	uint8_t wai_check; //who am i check
	uint8_t data;
 	HAL_StatusTypeDef sts = HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, REG_WHO_AM_I,1,&wai_check,1,i2c_timeout);
	if (wai_check == 104){

		/*data = 0b01000000; //- | FIFO_EN | I2C_MST_EN | I2C_IF_DIS | - | FIFO_RESET | I2C_MST_RESET | SIG_COND_RESET
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_USER_CTRL, 1, &data, 1, i2c_timeout);*/

		data = 0;
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_PWR_MGMT_1, 1, &data, 1, i2c_timeout);

		data = 0;
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_SMPRT_DIV, 1, &data, 1, i2c_timeout);

		data = 0;	//FSYNC DLPF
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_CONFIG, 1, &data, 1, i2c_timeout);

		data = 0b00010000; //1000 deg/s
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_GYRO_CONFIG, 1, &data, 1, i2c_timeout);

		data = 0b00010000; //8g
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_ACCEL_CONFIG, 1, &data, 1, i2c_timeout);

		data = 0b01111000;
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_FIFO_EN, 1, &data, 1, i2c_timeout);
		return 0;
	}
	return 1;
}

	void MPU6050_Read_Accel(I2C_HandleTypeDef *I2Cx, MPU6050_accel_vectors_t *DataStruct)
		{
			uint8_t recive_Bytes[6];
			HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, REG_ACCEL_XOUT_H, 1, recive_Bytes, 6, i2c_timeout);
			DataStruct->X = ((int16_t)(recive_Bytes[0] << 8 | recive_Bytes[1]))/4096.0;
			DataStruct->Y = ((int16_t)(recive_Bytes[2] << 8 | recive_Bytes[3]))/4096.0;
			DataStruct->Z = ((int16_t)(recive_Bytes[4] << 8 | recive_Bytes[5]))/4096.0;
			//LBS sensitivity taken from datasheet on page with Registers 59 to 64 – Accelerometer Measurements for 8g
		}
	void MPU6050_Read_Gyro(I2C_HandleTypeDef *I2Cx, MPU6050_gyro_vectors_t *DataStruct)
		{
			uint8_t recive_Bytes[6];
			HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, REG_GYRO_XOUT_H, 1, recive_Bytes, 6, i2c_timeout);
			DataStruct->X = ((int16_t)(recive_Bytes[0] << 8 | recive_Bytes[1]))/131.0;
			DataStruct->Y = ((int16_t)(recive_Bytes[2] << 8 | recive_Bytes[3]))/131.0;
			DataStruct->Z = ((int16_t)(recive_Bytes[4] << 8 | recive_Bytes[5]))/131.0;
			//LBS sensitivity taken from datasheet on page with Registers 67 to 72 – Gyroscope Measurements for 250 deg/s
		}

