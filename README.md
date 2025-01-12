# IIS3DWB_STM32H7B3I-DK

# Vibration Analysis with IIS3DWB and STM32H7B3I-DK

Real-time vibration analysis system using the IIS3DWB high-performance accelerometer and STM32H7B3I-DK development board. This project implements Fast Fourier Transform (FFT) for frequency domain analysis of vibration data.

## Features

- High-speed data acquisition (26.667 kHz sampling rate)
- Real-time FFT processing using ARM CMSIS-DSP
- DMA-optimized SPI communication
- Configurable frequency analysis parameters
- Hardware platform: STM32H7B3I-DK development board
- Sensor: IIS3DWB MEMS accelerometer

## Hardware Setup

### Required Components
- STM32H7B3I-DK development board
- IIS3DWB accelerometer module
- Connecting wires

### Connections
| IIS3DWB Pin | STM32H7B3I-DK Pin |
|-------------|-------------------|
| SCK         | SPI1_SCK         |
| MISO        | SPI1_MISO        |
| MOSI        | SPI1_MOSI        |
| CS          | User defined GPIO |
| VDD         | 3.3V             |
| GND         | GND              |

## Software Requirements

- STM32CubeIDE 1.13.0 or later
- CMSIS-DSP library
- STM32H7 HAL drivers

## Project Configuration

### SPI Configuration
- Mode: Full-Duplex Master
- Data Size: 8 bits
- First Bit: MSB First
- Prescaler: 8 (8 MBits/s)
- Clock Polarity (CPOL): Low
- Clock Phase (CPHA): 1 Edge

### DMA Settings
- SPI1_TX: DMA1 Stream 0
- SPI1_RX: DMA1 Stream 1
- Priority: High
- Data Width: Byte
- Memory Increment: Enabled

## Data Processing

The project implements the following processing chain:
1. High-speed data acquisition from IIS3DWB
2. DMA transfer to memory
3. Hanning window application
4. Real FFT computation
5. Magnitude calculation

FFT results provide frequency content analysis from 0 to 13.3 kHz (Nyquist frequency).

## Acknowledgments

- STMicroelectronics for their excellent development tools
- ARM for the CMSIS-DSP library
- All contributors to this project
