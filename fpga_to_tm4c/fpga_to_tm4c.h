#ifndef _tm4c_to_fpga_h_
    #define _tm4c_to_fpga_h_
#endif
#define BAUD_RATE 115200
#define NUM_OUTPUT_CHARS_CAMERA 11

// Configures UART peripheral as well as GPIO pins for transmit and receive.
void initUART(uint32_t UARTbase, uint32_t clockRate);

// Sends byte of data to selected fpga via UART?
void UARTSendByte(uint32_t fpgaId, uint8_t data);

// Reads data from FPGA and organizes it into 64 bit registry
uint64_t readFPGAData(uint32_t fpgaId);

// Sends a string of data to be printed to Serial Console
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);

// Sends a control menu to the Serial Console
void UARTMenu();