#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h> // for gpio.h
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h" // for Ti defined UART functions

#define BAUD_RATE 115200
#define NUM_OUTPUT_CHARS_CAMERA 8

//
// Configures UART peripheral as well as GPIO pins for transmit and receive.
//
void initUART(uint32_t UARTbase, uint32_t clockRate) {
    // enable UART peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    
    // enable GPIO ports a and c
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {
    }
        
    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    
    GPIOPinConfigure(GPIO_PC4_U7RX);
    GPIOPinConfigure(GPIO_PC5_U7TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    
    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    UARTConfigSetExpClk(UART0_BASE, clockRate, BAUD_RATE,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
    UARTConfigSetExpClk(UART7_BASE, clockRate, BAUD_RATE,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
}

//
// Sends byte of data to selected fpga via UART?
//
void UARTSendByte(uint32_t fpgaId, uint8_t data) {
    //
    // Put a character in the output buffer.
    //
    UARTCharPut(fpgaId, data);
}

//
// Reads data from FPGA and organizes it into 64 bit registry
//
uint64_t readFPGAData(uint32_t fpgaId) {
    uint8_t numberIterations;
    uint8_t singleChar;
    uint64_t cameraOutputChars;
    numberIterations = 0;
    cameraOutputChars = 0;
    singleChar = 0;
    
    while (numberIterations < sizeof(singleChar) * 8) {
        if (!UARTCharsAvail(fpgaId)) {
            // Get ASCII charactor from camera and put into cameraOutputChars
            singleChar = UARTCharGetNonBlocking(fpgaId);
            cameraOutputChars = singleChar;
            // Leftshift variable the size of a single char from camera.
            cameraOutputChars <<= sizeof(singleChar) * 8;
            numberIterations++;
        }
    }
    return cameraOutputChars;
}
