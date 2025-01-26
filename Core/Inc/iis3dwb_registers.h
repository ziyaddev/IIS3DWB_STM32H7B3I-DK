/*
 * iis3dwb_registers.h
 *
 *  Created on: Jan 24, 2025
 *      Author: ziyad
 */

#ifndef INC_IIS3DWB_REGISTERS_H_
#define INC_IIS3DWB_REGISTERS_H_

/* Device Identification (Who am I) */
#define IIS3DWB_ID						0x7B
#define IIS3DWB_WHOAMI					0x0F

/* Control registers */
#define IIS3DWB_CTRL1_XL				0x10
#define IIS3DWB_CTRL2_G					0x11
#define IIS3DWB_CTRL3_C					0x12
#define IIS3DWB_CTRL4_C					0x13
#define IIS3DWB_CTRL5_C					0x14
#define IIS3DWB_CTRL6_C					0x15
#define IIS3DWB_CTRL7_G					0x16
#define IIS3DWB_CTRL8_XL				0x17
#define IIS3DWB_CTRL9_XL				0x18
#define IIS3DWB_CTRL10_C				0x19

/* Status registers */
#define IIS3DWB_STATUS_REG				0x1E
#define IIS3DWB_STATUS_SPIAUX			0x1E

/* Temperature data */
#define IIS3DWB_OUT_TEMP_L				0x20
#define IIS3DWB_OUT_TEMP_H				0x21

/* Gyroscope output registers */
#define IIS3DWB_OUTX_L_G				0x22
#define IIS3DWB_OUTX_H_G				0x23
#define IIS3DWB_OUTY_L_G				0x24
#define IIS3DWB_OUTY_H_G				0x25
#define IIS3DWB_OUTZ_L_G				0x26
#define IIS3DWB_OUTZ_H_G				0x27

/* Accelerometer output registers */
#define IIS3DWB_OUTX_L_XL				0x28
#define IIS3DWB_OUTX_H_XL				0x29
#define IIS3DWB_OUTY_L_XL				0x2A
#define IIS3DWB_OUTY_H_XL				0x2B
#define IIS3DWB_OUTZ_L_XL				0x2C
#define IIS3DWB_OUTZ_H_XL				0x2D

/* FIFO and interrupt registers */
#define IIS3DWB_FIFO_CTRL1				0x07
#define IIS3DWB_FIFO_CTRL2				0x08
#define IIS3DWB_FIFO_CTRL3				0x09
#define IIS3DWB_FIFO_CTRL4				0x0A
#define IIS3DWB_COUNTER_BDR_REG1		0x0B
#define IIS3DWB_COUNTER_BDR_REG2		0x0C
#define IIS3DWB_INT1_CTRL				0x0D
#define IIS3DWB_INT2_CTRL				0x0E
#define IIS3DWB_FIFO_STATUS1			0x3A
#define IIS3DWB_FIFO_STATUS2			0x3B
#define IIS3DWB_FIFO_DATA_OUT_TAG		0x78
#define IIS3DWB_FIFO_DATA_OUT_X_L		0x79
#define IIS3DWB_FIFO_DATA_OUT_X_H		0x7A
#define IIS3DWB_FIFO_DATA_OUT_Y_L		0x7B
#define IIS3DWB_FIFO_DATA_OUT_Y_H		0x7C
#define IIS3DWB_FIFO_DATA_OUT_Z_L		0x7D
#define IIS3DWB_FIFO_DATA_OUT_Z_H		0x7E

/* Other registers */
#define IIS3DWB_TIMESTAMP0				0x40
#define IIS3DWB_TIMESTAMP1				0x41
#define IIS3DWB_TIMESTAMP2				0x42
#define IIS3DWB_TIMESTAMP3				0x43

/* Register bit masks and values */
#define IIS3DWB_BDU_MASK				0x40
#define IIS3DWB_FS_XL_MASK				0x0C
#define IIS3DWB_ODR_XL_MASK				0xF0
#define IIS3DWB_FIFO_MODE_MASK			0x07

/* Output Data Rate values */
#define IIS3DWB_XL_ODR_26k7Hz			0xA0  /* 26.667 kHz */
#define IIS3DWB_XL_ODR_OFF				0x00  /* Power down */

/* Full scale selection */
#define IIS3DWB_2g						0x00
#define IIS3DWB_4g						0x04
#define IIS3DWB_8g						0x08
#define IIS3DWB_16g						0x0C

/* FIFO modes */
#define IIS3DWB_BYPASS_MODE				0x00
#define IIS3DWB_FIFO_MODE				0x01
#define IIS3DWB_STREAM_MODE				0x02
#define IIS3DWB_STREAM_TO_FIFO_MODE		0x03
#define IIS3DWB_BYPASS_TO_STREAM_MODE	0x04
#define IIS3DWB_CONTINUOUS_MODE			0x06

#endif /* INC_IIS3DWB_REGISTERS_H_ */
