#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h> // for gpio.h
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h" // for Ti defined UART functions
#include "fpga_to_tm4c.h" // for EagleSat II defined functions


int main(void) {
    uint32_t g_ui32SysClock;
    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                           SYSCTL_OSC_MAIN |
                                            SYSCTL_USE_PLL |
                                        SYSCTL_CFG_VCO_480), 120000000);
    
    initUART(UART0_BASE, g_ui32SysClock);
    
    while (1);
}