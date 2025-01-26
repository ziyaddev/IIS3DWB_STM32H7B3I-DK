#ifndef IIS3DWB_H
#define IIS3DWB_H

#include "main.h"
#include "arm_math.h"
#include <stdio.h>
#include "iis3dwb_registers.h"

// Configuration
#define FFT_SIZE                 1024
#define SAMPLE_FREQ             26667  // 26.667 kHz

typedef struct {
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
    float32_t fft_buffer[FFT_SIZE];
    float32_t fft_output[FFT_SIZE/2];
    arm_rfft_fast_instance_f32 fft_handler;
} IIS3DWB_Handle_t;

HAL_StatusTypeDef IIS3DWB_Init(IIS3DWB_Handle_t *dev);
HAL_StatusTypeDef IIS3DWB_ReadAccel(IIS3DWB_Handle_t *dev, float *x, float *y, float *z);
void IIS3DWB_ProcessFFT(IIS3DWB_Handle_t *dev);
void IIS3DWB_PrintFFTResults(IIS3DWB_Handle_t *dev, UART_HandleTypeDef *huart);

#endif
