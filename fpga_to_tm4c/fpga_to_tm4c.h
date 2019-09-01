#ifndef _tm4c_to_fpga_h_
    #define _tm4c_to_fpga_h_
#endif
#define BAUD_RATE 115200

// Configures UART peripheral as well as GPIO pins for transmit and receive.
void initUART(uint32_t UARTbase, uint32_t clockRate);

// Sends byte of data to selected fpga via UART?
void UARTSendByte(uint32_t fpgaId, uint8_t data);

// Reads data from FPGA and organizes it into 64 bit registry
uint64_t readFPGAData(uint32_t fpgaId);

// Debug version of above functions used for testing
// Will send copy of recieved and sent data to serial console
void initUART_DEBUG(uint32_t UARTbase);
void UARTSendByte_DEBUG(uint32_t fpgaId, uint8_t data);
uint64_t readFPGAData_DEBUG(uint32_t fpgaId);