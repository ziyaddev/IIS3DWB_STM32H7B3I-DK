#include "iis3dwb.h"

static HAL_StatusTypeDef IIS3DWB_WriteReg(IIS3DWB_Handle_t *dev, uint8_t reg, uint8_t value)
{
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
    uint8_t data[2] = {reg & 0x7F, value};
    HAL_StatusTypeDef status = HAL_SPI_Transmit(dev->hspi, data, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
    return status;
}

static HAL_StatusTypeDef IIS3DWB_ReadRegs(IIS3DWB_Handle_t *dev, uint8_t reg, uint8_t *data, uint16_t len)
{
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
    uint8_t addr = reg | 0x80;
    HAL_SPI_Transmit(dev->hspi, &addr, 1, HAL_MAX_DELAY);
    HAL_StatusTypeDef status = HAL_SPI_Receive(dev->hspi, data, len, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
    return status;
}

//static HAL_StatusTypeDef IIS3DWB_ReadRegsTransReicv(IIS3DWB_Handle_t *dev, uint8_t reg, uint8_t *data, uint16_t len)
//{
//    uint8_t addr = reg | 0x80;
//    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
//    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(dev->hspi, &addr, data, len, HAL_MAX_DELAY);
////    HAL_SPI_Transmit(dev->hspi, &addr, 1, HAL_MAX_DELAY);
////    HAL_StatusTypeDef status = HAL_SPI_Receive(dev->hspi, data, len, HAL_MAX_DELAY);
//    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
//    return status;
//}


HAL_StatusTypeDef IIS3DWB_Init(IIS3DWB_Handle_t *dev)
{
    // Reset the device
    IIS3DWB_WriteReg(dev, IIS3DWB_CTRL3_C, 0x01);
	// Wait 100ms to let the device download its calibration coeff's
    HAL_Delay(100);

    // enable 3-axis mode
    IIS3DWB_WriteReg(dev, IIS3DWB_CTRL6_C, 0x00);

    // Enable accelerometer, Configure pour 26.667 kHz, ±2g
    IIS3DWB_WriteReg(dev, IIS3DWB_CTRL1_XL, 0xA0);

    // Initialize FFT structure
    arm_rfft_fast_init_f32(&dev->fft_handler, FFT_SIZE);

    return HAL_OK;
}

HAL_StatusTypeDef IIS3DWB_ReadAccel(IIS3DWB_Handle_t *dev, float *x, float *y, float *z)
{
    uint8_t data[6];
    uint8_t acc_data_status = 0;

    while ((acc_data_status & 0x01) != 0x01)
    {
    	IIS3DWB_ReadRegs(dev, IIS3DWB_STATUS_REG, &acc_data_status, 1);
    }

    HAL_StatusTypeDef status = IIS3DWB_ReadRegs(dev, IIS3DWB_OUTX_L_XL, data, 6);
    
    if (status == HAL_OK) {
        int16_t raw_x = (data[1] << 8) | data[0];
        int16_t raw_y = (data[3] << 8) | data[2];
        int16_t raw_z = (data[5] << 8) | data[4];
        
        // Conversion en g (±2g range)
        *x = (float)raw_x * 0.061f / 1000.0f;
        *y = (float)raw_y * 0.061f / 1000.0f;
        *z = (float)raw_z * 0.061f / 1000.0f;
    }
    
    return status;
}

void IIS3DWB_ProcessFFT(IIS3DWB_Handle_t *dev)
{
    // Appliquer la fenêtre de Hanning
    for(int i = 0; i < FFT_SIZE; i++) {
        float32_t multiplier = 0.5f * (1.0f - arm_cos_f32(2.0f * PI * i / FFT_SIZE));
        dev->fft_buffer[i] *= multiplier;
    }
    
    // Calculer la FFT
    float32_t temp[FFT_SIZE];
    arm_rfft_fast_f32(&dev->fft_handler, dev->fft_buffer, temp, 0);
    
    // Calculer les magnitudes
    for(int i = 0; i < FFT_SIZE/2; i++) {
        float32_t real = temp[2*i];
        float32_t imag = temp[2*i+1];
        dev->fft_output[i] = sqrtf(real*real + imag*imag);
    }
}

void IIS3DWB_PrintFFTResults(IIS3DWB_Handle_t *dev, UART_HandleTypeDef *huart)
{
	char buffer[50];
	int len;

	len = sprintf(buffer, "FFT Results : \r\n");
	HAL_UART_Transmit(huart, (uint8_t*)buffer, len, HAL_MAX_DELAY);

	for(int i = 0; i < 20; i++) {
		float frequency = i * (SAMPLE_FREQ / (float)FFT_SIZE);
		len = sprintf(buffer, "Freq %.1f Hz : Magnitude %.3f\r\n",
					 frequency, dev->fft_output[i]);
		HAL_UART_Transmit(huart, (uint8_t*)buffer, len, HAL_MAX_DELAY);
	}

	len = sprintf(buffer, "\r\n");
	HAL_UART_Transmit(huart, (uint8_t*)buffer, len, HAL_MAX_DELAY);
}

// SPI1 pinout :
// SCK  -> PA5 (N5) -> Pin 1 of the U20 chip on the bottom layer
// MISO -> PB4 (B5) -> R39 resistor on the top layer
// Pin 14 -> MOSI -> PB5 (E7) -> Pin 13 of the U20 chip on the bottom layer
// CS   -> PA4 (L6) -> Arduino connector CN20 pin 1 (Solder SB45 pad to enable)
