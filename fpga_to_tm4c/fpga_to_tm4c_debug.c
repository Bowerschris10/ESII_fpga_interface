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

// UART7_BASE is for receive
// UART6_BASE is for send
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
        // write test buffer to serial terminal
        //UARTSend(*quickBuffer[0], 8);
        // put char recieved from FPGA into serial terminal
        //UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART7_BASE));
        // put character 'a' into Raspberry Pi, (pyserial read) serial ternimal
        
        // for commanding camera FPGA
        UARTCharPut(UART7_BASE, 'a');
        pixel_data = UARTCharGet(UART7_BASE); // is data packet coming at one time?
        UARTCharPut(UART0_BASE, pixel_data);
        
        /*
        // for UART0 testing
        char_received = UARTCharGet(UART0_BASE);
        UARTCharPut(UART0_BASE, char_received);
        UARTCharPut(UART0_BASE, char_received);
        */
        
        // for putty use
        //UARTCharPut(UART0_BASE, 'a');
//        UARTCharPutNonBlocking(UART7_BASE, 'a');
        // send char 'a' to FPGA
        //UARTCharPutNonBlocking(UART6_BASE, 'a');
        // send char recieved from serial termial to FPGA
        //UARTCharPutNonBlocking(UART6_BASE,
        //                       UARTmenu(UARTCharGetNonBlocking(UART0_BASE)));
        
        /*
        for (int i = 0; i < NUM_OUTPUT_CHARS_CAMERA; i++)
            if (!UARTCharsAvail(fpgaId))
                charReadBuffer[i] = UARTCharGetNonBlocking(UART7_BASE);
        */
        //blink();
    }
}