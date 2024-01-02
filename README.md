# STM32 HAL Example for Pervasive Displays EPDs
 
STM32 CubeHAL example for [this driver](https://github.com/Estylos/EPD_SmallSized_Driver_HAL) used to control small-sized EPDs from [Pervasive Displays Inc](https://www.pervasivedisplays.com/) ( 1.54", 2.06", 2.13", 2.66", 2.71", 2.87", 2.90", 3.70", 4.17", 4.37") with internal driving (iTC).

This example is largely inspired by the example supplied with the [manufacturer's driver](https://github.com/PervasiveDisplays/EPD_Driver_GF_small/). 

This project is based on a [NUCLEO-F303K8](https://www.st.com/en/evaluation-tools/nucleo-f303k8.html), but can be adapted to any STM32 with at least one SPI peripheral and 4 GPIOs. Peripheral configuration has been done with STM32CubeMX, only the main.c file is realtive to the example.

The default wiring in the example is as follows: 

| EXT3-1 Pin      | STM32F303 Pin |
|-----------------|---------------|
| SCK             | PA5           |
| BUSY            | PA0           |
| D/C             | PA1           |
| RST             | PA3           |
| MOSI            | PA7           |
| ECSM (Panel CS) | PA4           |

Depending on the STM32 you're using, you may need to update the example, in particular by creating a new project and a new .ioc file with your configuration.

CubeMX allows you to create user labels for each GPIO (pin and port), making it easy to initialize the ePaperDisplay_t screen structure.

The constants that can be changed relative to your screen  (type, size and PSR) are located in the driver's epd_screen.h file. The constant `#define SCREEN 266` at the top of the main.c file is only used to load the correct demo buffers and should not be used in production.

## Related projects and documentation
- [PDI Wiki](https://docs.pervasivedisplays.com/) 
- [EPD_Driver_GF_small](https://github.com/PervasiveDisplays/EPD_Driver_GF_small/) : Officiel driver from PDI using the Arduino framework for PS/KS-type small-sized 1.54", 2.13", 2.66", 2.71", 2.87", 2.92", 3.70", 4.17" and 4.37" screens

## Disclaimer

This project is in no way affiliated with Pervasive Displays Inc.
All images are the property of their respective authors and companies.