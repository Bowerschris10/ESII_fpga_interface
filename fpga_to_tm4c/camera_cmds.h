#ifndef camera_cmds_h
    #define camera_cmds_h
#endif

void InitI2C0(void);

//void I2CSend(uint8_t slave_addr,uint8_t reg1, uint8_t reg2, uint8_t data1, uint8_t data2);

void I2CSend(uint8_t slave_addr,uint16_t reg, uint16_t data);

void UART7IntHandler(void);

void I2CSendSingle(uint8_t slave_addr,uint16_t reg, uint8_t data);

uint32_t I2CReceive(uint32_t slave_addr, uint16_t reg);

void initCamera(void);

