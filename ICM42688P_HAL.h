/*
 * ICM42688P_HAL.h
 *
 *  Created on: Mar 6, 2025
 *      Author: Sezakiaoi
 */

#ifndef SRC_ICM42688P_HAL_H_
#define SRC_ICM42688P_HAL_H_

#include <cstdint>
#include <spi.h>

class ICM42688P_HAL {

	public:

		enum class BANK0: uint8_t{

			ACCEL_DATA_X1 = 0x1F,
			PWR_MGMT0 = 0x4E,
			GYRO_CONFIG0 = 0x4F,
			ACCEL_CONFIG0 = 0x50,
			GYRO_CONFIG1 = 0x51,
			GYRO_ACCEL_CONFIG0 = 0x52,
			WHO_AM_I = 0x75,
			REG_BANK_SEL = 0x76
		};

		ICM42688P_HAL(SPI_HandleTypeDef* SpiPin, GPIO_TypeDef* CsPinType, uint16_t CsPinNum);

		//BANK0
		HAL_StatusTypeDef Write(ICM42688P_HAL::BANK0, uint8_t* Command, uint8_t Len);
		HAL_StatusTypeDef Read(ICM42688P_HAL::BANK0, uint8_t* Receive_buffer, uint8_t Len);

	private:

		SPI_HandleTypeDef* SpiPin;
		GPIO_TypeDef* CsPinType;
		uint16_t CsPinNum = 0x00;
};

#endif /* SRC_ICM42688P_HAL_H_ */
