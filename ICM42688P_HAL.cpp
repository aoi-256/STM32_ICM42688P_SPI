/*
 * ICM42688P_HAL.cpp
 *
 *  Created on: Mar 6, 2025
 *      Author: Sezakiaoi
 */

#include "ICM42688P_HAL.h"

/* @brief I2cのピンデータの受け取り
 *
 * @param I2C_HandleTypeDef* 使用するピンの情報
 *
 * @return None
 */
ICM42688P_HAL::ICM42688P_HAL(SPI_HandleTypeDef* SpiPin, GPIO_TypeDef* CsPinType, uint16_t CsPinNum) {

	this->SpiPin = SpiPin;
	this->CsPinType = CsPinType;
	this->CsPinNum = CsPinNum;
}

/* @brief ICM42688Pへの書き込み
 *
 * ICM42688Pの特定のレジスタに指定した値を書き込みます
 *
 * @param ICM42688P_HAL::BANK0 レジスタアドレス
 * @param Command 書き込むデータのポインタ
 * @param Len 書き込むデータのサイズ
 *
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef ICM42688P_HAL::Write(ICM42688P_HAL::BANK0 REGISTER_ADDR, uint8_t* Command, uint8_t Len){

	uint8_t TxBuffer[2] = {};
	HAL_StatusTypeDef Status;

	for(uint8_t i=0; i<Len; i++){

	TxBuffer[0] = ((uint8_t)REGISTER_ADDR + i) | 0x00;
	TxBuffer[1] = Command[i];

	HAL_GPIO_WritePin(CsPinType, CsPinNum, GPIO_PIN_RESET);

	Status = HAL_SPI_Transmit(SpiPin, TxBuffer, 2, 1000);

    HAL_GPIO_WritePin(CsPinType, CsPinNum, GPIO_PIN_SET);

	}

	return Status;
}

/* @brief ICM42688Pへの読み取り
 *
 * ICM42688Pの特定のレジスタの値を読み取ります
 *
 * @param ICM42688P_HAL::BANK0 レジスタアドレス
 * @param Command 読み取ったデータの保存先
 * @param Len 読み取るデータのサイズ
 *
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef ICM42688P_HAL::Read(ICM42688P_HAL::BANK0 REGISTER_ADDR, uint8_t* Buffer, uint8_t Len){

	uint8_t TxBuffer[2] = {};
	uint8_t RxBuffer[2] = {};
	HAL_StatusTypeDef Status;

	for(uint8_t i=0; i<Len; i++){

		TxBuffer[0] = (uint8_t(REGISTER_ADDR) + i) | 0x80;
		TxBuffer[1] = 0x00;

		HAL_GPIO_WritePin(CsPinType, CsPinNum, GPIO_PIN_RESET);

		Status = HAL_SPI_TransmitReceive(SpiPin, TxBuffer, RxBuffer, 2, 100);

		HAL_GPIO_WritePin(CsPinType, CsPinNum, GPIO_PIN_SET);

		Buffer[i] = RxBuffer[1];
	}

	return Status;
}

