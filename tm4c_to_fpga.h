#ifndef _tm4c_to_fpga_h_
#define _tm4c_to_fpga_h_
#include "driverlib/uart.h" // for Ti defined UART functions

#define BAUD_RATE 115200

//
// Configures UART peripheral as well as GPIO pins for transmit and receive.
//
void initUART(uint32_t UARTbase) {
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
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    
    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    ROM_UARTConfigSetExpClk(UART0_BASE, g_ui32SysClock, BAUD_RATE,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
    ROM_UARTConfigSetExpClk(UART7_BASE, g_ui32SysClock, BAUD_RATE,
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
    UARTCharPut(fpgaId, data));

}
//
// Reads data from FPGA and organizes it into 64 bit registry
//
uint64_t readFPGAData(uint32_t fpgaId) {
    uint8_t numberIterations;
    numberIterations = 0;
    
    //
    // Check for characters. Spin here until a character is placed
    // into the receive FIFO.
    //
    while(!UARTCharsAvail(fpgaId))
    {
    }
 
    //
    // Get the character(s) in the receive FIFO.
    //
    while(UARTCharGetNonBlocking(fpgaId))
    {
    }
}

//
// Disable the UART.
//
//UARTDisable(UARTbase);