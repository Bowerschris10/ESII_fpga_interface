#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h> // for gpio.h
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h" // for Ti defined UART functions


//#define BAUD_RATE 111111 // camera baud rate
#define BAUD_RATE 115200 // pi baud rate
#define NUM_OUTPUT_CHARS_CAMERA 11

//
// Configures UART peripheral as well as GPIO pins for transmit and receive.
// Configures TX and RX for both FPGA and Raspberry PI.
//
void initUART(uint32_t UARTbase, uint32_t clockRate) {
    // enable UART peripheral
    // serial console for debugging
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // pin for read/write to FPGA
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
    // pin for read/write to raspberry pi
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);

    // enable GPIO ports a and c
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0) &
          !SysCtlPeripheralReady(SYSCTL_PERIPH_UART7) &
          !SysCtlPeripheralReady(SYSCTL_PERIPH_UART6))
    {
    }
        
    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    
    GPIOPinConfigure(GPIO_PC4_U7RX);
    GPIOPinConfigure(GPIO_PC5_U7TX);
    
//    GPIOPinConfigure(GPIO_PC6_U6RX);
//    GPIOPinConfigure(GPIO_PC7_U6TX);
    
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 |
                                     GPIO_PIN_6 | GPIO_PIN_7);
            
    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    UARTConfigSetExpClk(UART7_BASE, clockRate, BAUD_RATE,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
    /*
    UARTConfigSetExpClk(UART6_BASE, clockRate, BAUD_RATE,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
    */
    UARTConfigSetExpClk(UART0_BASE, clockRate, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
    UARTEnable(UART7_BASE);
//    UARTEnable(UART6_BASE);
    UARTEnable(UART0_BASE);
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
// Reads data from FPGA and prints to UART0 (serial terminal)
//
char readFPGAData(uint32_t fpgaId) {
    uint8_t numberIterations;
    uint8_t singleChar;
    uint64_t cameraOutputChars;
    numberIterations = 0;
    cameraOutputChars = 0;
    singleChar = 0;
    
    singleChar = UARTCharGetNonBlocking(fpgaId);
    /*
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
    */
    return singleChar;
}

//
// Sends a string to console UART
//
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count) {

    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}

//
// Displays a menu to the serial console. Processes menu inputs
//
void UARTMenu() {
    char command;
    // issue printing entire string when running. Can print when stepping thru
    // UARTSend
    // UARTSend("EagleSat II FPGA Command Interface\n", 64); 
    UARTSend("enter command >> ", 17);
    while (1) {
        command = UARTCharGet(UART0_BASE);
        if (command == 's') { // send 'a' character to FPGA via UART6
            UARTCharPut(UART6_BASE, 'a');
            UARTCharPut(UART0_BASE, '\n');
            UARTCharPut(UART0_BASE, 'a');
        } else if (command == 'l') { // listen to FPGA
            UARTCharPut(UART0_BASE, 'l');
            UARTCharPut(UART0_BASE, '\n');                        
            UARTCharPut(UART0_BASE, UARTCharGet(UART7_BASE));
        }
    }
}