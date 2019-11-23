#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h> // for gpio.h
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h" // for Ti defined UART functions
#include "fpga_to_tm4c.h" // for EagleSat II defined uart functions

// to-do: make code more modular

// UART7_BASE is for receiving pixel data
// UART7_BASE is for sending fpga commands
// UART0_BASE is for serial terminal

int main(void) {
    uint32_t g_ui32SysClock;
    int32_t char_received;
    double pixel_data;
    uint8_t quickBuffer[NUM_OUTPUT_CHARS_CAMERA];
    uint8_t charReadBuffer[NUM_OUTPUT_CHARS_CAMERA];
    for (int i = 0; i < NUM_OUTPUT_CHARS_CAMERA; i++)
        quickBuffer[i] = 'a';
    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                           SYSCTL_OSC_MAIN |
                                            SYSCTL_USE_PLL |
                                        SYSCTL_CFG_VCO_480), 120000000);
    initUART(UART0_BASE, g_ui32SysClock);
    
    // has built in while(1) loop for menu processing
    //UARTMenu();
    
    while (1) {
        // for commanding camera FPGA
        UARTCharPut(UART7_BASE, 'a');
        pixel_data = UARTCharGet(UART7_BASE); // is data packet coming at one time?
        UARTCharPut(UART0_BASE, pixel_data);
    }
}