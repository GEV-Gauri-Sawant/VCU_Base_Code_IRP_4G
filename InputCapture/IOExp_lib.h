


//#define I2C_SLAVE_ADDRESS 0x42
#define INPUT_REG_PORT0 0x00
#define INPUT_REG_PORT1	0x01
#define OUTPUT_REG_PORT0 0x02
#define OUTPUT_REG_PORT1 0x03
#define CONFIG_REG_PORT0 0x06
#define CONFIG_REG_PORT1 0x07

#define PIN_LOW  false
#define PIN_HIGH true

/* This test case configures Port 0 of IO Expander as output
 * and Port 1 as input and check the signals transmission from Port 0 on Port 1 */
void IOExp_Test_FullPORT(void);


/* Configures pin input and output for corresponding ports as provided in port0 and port1 parameter */
/* IOExp_address is the device address, e.g. 0x40 */
void IOExp_Configure(I2C_MASTER_t *handle, uint8_t IOExp_address, uint8_t port0, uint8_t port1);


/* Internal function to set a pin high or low for specified IO expander
 * return: true,  operation is successful
 * 		   false, operation not successful */
bool IOExp_SetPIN_UPDATE(I2C_MASTER_t *handle, uint8_t IOExp_Address, uint8_t port, uint8_t pin, bool pin_level);


/* Function to set a pin high for specified IO expander
 * return: true,  operation is successful
 * 		   false, operation not successful */
bool IOExp_SetPIN_HIGH(I2C_MASTER_t *handle, uint8_t IOExp_Address, uint8_t port, uint8_t pin);


/* Function to set a pin low for specified IO expander
 * return: true,  operation is successful
 * 		   false, operation not successful */
bool IOExp_SetPIN_LOW(I2C_MASTER_t *handle, uint8_t IOExp_Address, uint8_t port, uint8_t pin);

/* Function to read a pin level for specified IO expander
 * return: true,  pin is HIGH
 * 		   false, pin is LOW */
//bool IOExp_ReadPIN_LEVEL(uint8_t IOExp_Address, uint8_t port, uint8_t pin);
uint8_t* IOExp_ReadPIN_LEVEL(I2C_MASTER_t *handle, uint8_t IOExp_Address, uint8_t port);




