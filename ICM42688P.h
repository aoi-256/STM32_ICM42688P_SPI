/*
 * ICM42688P.h
 *
 *  Created on: Mar 6, 2025
 *      Author: Sezakiaoi
 */

#ifndef SRC_ICM42688P_H_
#define SRC_ICM42688P_H_

#include "ICM42688P_HAL.h"
#include <cstdint>

class ICM42688P: private ICM42688P_HAL{


	public:

		enum class GYRO_MODE: uint8_t{

			OFF = 0x00,
			Standby = 0x01,
			LowNoize = 0x03
		};

		enum class GYRO_SCALE: uint8_t{

			Dps2000 = 0x00,
			Dps1000 = 0x01,
			Dps0500 = 0x02,
			Dps0250 = 0x03,
			Dps0125 = 0x04,
			Dps0062 = 0x05,
			Dps0031 = 0x06,
			Dps0015 = 0x07
		};

		enum class GYRO_ODR: uint8_t{

			ODR32000hz = 0x01,
			ODR16000hz = 0x02,
			ODR08000hz = 0x03,
			ODR04000hz = 0x04,
			ODR02000hz = 0x05,
			ODR01000hz = 0x06,
			ODR00200hz = 0x07,
			ODR00100hz = 0x08,
			ODR00050hz = 0x09,
			ODR00025hz = 0x0A,
			ODR00012hz = 0x0B,
			ODR00500hz = 0x0F
		};

		enum class GYRO_DLPF: uint8_t{

			ODR02 = 0x00,
			ODR04 = 0x01,
			ODR05 = 0x02,
			ODR08 = 0x03,
			ODR10 = 0x04,
			ODR16 = 0x05,
			ODR20 = 0x06,
			ODR40 = 0x07,
		};

		enum class ACCEL_Mode: uint8_t{

			OFF = 0x00,
			LowPower = 0x02,
			LowNoize = 0x03
		};

		enum class ACCEL_SCALE: uint8_t{

			SCALE16g = 0x00,
			SCALE08g = 0x01,
			SCALE04g = 0x02,
			SCALE02g = 0x03
		};

		enum class ACCEL_ODR: uint8_t{

			ODR32000hz = 0x01,
			ODR16000hz = 0x02,
			ODR08000hz = 0x03,
			ODR04000hz = 0x04,
			ODR02000hz = 0x05,
			ODR01000hz = 0x06,
			ODR00200hz = 0x07,
			ODR00100hz = 0x08,
			ODR00050hz = 0x09,
			ODR00025hz = 0x0A,
			ODR00012hz = 0x0B,
			ODR00006hz = 0x0C,
			ODR00003hz = 0x0D,
			ODR00001hz = 0x0E,
			ODR00500hz = 0x0F
		};

		enum class ACCEL_DLPF: uint8_t{

			ODR02 = 0x00,
			ODR04 = 0x01,
			ODR05 = 0x02,
			ODR08 = 0x03,
			ODR10 = 0x04,
			ODR16 = 0x05,
			ODR20 = 0x06,
			ODR40 = 0x07,
		};

		ICM42688P(SPI_HandleTypeDef* SpiPin, GPIO_TypeDef* CsPinType, uint16_t CsPinNum);
		uint8_t Connection();
		uint8_t GetRawData(int16_t AccelBuffer[3], int16_t GyroBuffer[3]);
		uint8_t GetData(float AccelBuffer[3], float GyroBuffer[3]);
		uint8_t AccelConfig(ICM42688P::ACCEL_Mode, ICM42688P::ACCEL_SCALE, ICM42688P::ACCEL_ODR, ICM42688P::ACCEL_DLPF);
		uint8_t GyroConfig(ICM42688P::GYRO_MODE Mode, ICM42688P::GYRO_SCALE Scale, ICM42688P::GYRO_ODR ODR, ICM42688P::GYRO_DLPF DLPF);
		uint8_t Calibration(uint16_t Count);
		void SelectBank(uint8_t Bank);

	private:

		uint8_t RawData[12] = {};
		int16_t AccelOffset[3] = {};
		int16_t GyroOffset[3] = {};
		float AccelScaleValue = 0.0;
		float GyroScaleValue  = 0.0;
		float G = 9.80665;
};

#endif /* SRC_ICM42688P_H_ */
